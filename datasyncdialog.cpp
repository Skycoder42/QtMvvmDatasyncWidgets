#include "datasyncdialog.h"
#include "ui_datasyncdialog.h"
#include <widgetpresenter.h>
#include <dialogmaster.h>
#include <QStandardPaths>
#include <coremessage.h>
#include <qtmvvmbinding.h>
#include <QMenu>
#include "userdataexchangedialog.h"
#include "changeremotedialog.h"

DatasyncDialog::DatasyncDialog(Control *mControl, QWidget *parent) :
	QDialog(parent),
	control(static_cast<DatasyncControl*>(mControl)),
	ui(new Ui::DatasyncDialog)
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this, true);

	ui->syncButton->addActions({
								   ui->action_Sync,
								   ui->action_Resync
							   });
	ui->syncButton->setDefaultAction(ui->action_Sync);

	auto exchangeMenu = new QMenu(ui->exportButton);
	exchangeMenu->addAction(ui->action_Network_exchange);
	exchangeMenu->addSeparator();
	exchangeMenu->addAction(ui->action_Export_to_file);
	exchangeMenu->addAction(ui->action_Import_from_file);
	if(control->canReset()) {
		exchangeMenu->addSeparator();
		exchangeMenu->addAction(ui->action_Change_Remote_Server);
		exchangeMenu->addAction(ui->action_Reset_Identity);
	}
	ui->exportButton->setMenu(exchangeMenu);

	QtMvvmBinding::bind(control, "syncEnabled",
						ui->syncCheckBox, "checked");

	connect(control, &DatasyncControl::statusStringChanged,
			this, &DatasyncDialog::updateStatus);
	connect(control, &DatasyncControl::showProgressChanged,
			this, &DatasyncDialog::updateProgressVisible);
	connect(control, &DatasyncControl::syncProgressChanged,
			this, &DatasyncDialog::updateProgress);
	connect(control, &DatasyncControl::authErrorChanged,
			this, &DatasyncDialog::updateError);

	connect(ui->action_Sync, &QAction::triggered,
			control, &DatasyncControl::sync);
	connect(ui->action_Resync, &QAction::triggered,
			control, &DatasyncControl::resync);
	connect(ui->action_Network_exchange, &QAction::triggered,
			control, &DatasyncControl::initExchange);
	connect(ui->action_Change_Remote_Server, &QAction::triggered,
			control, &DatasyncControl::changeRemote);
	connect(ui->action_Reset_Identity, &QAction::triggered,
			control, &DatasyncControl::resetIdentity);

	updateStatus();
	updateProgress();
	updateProgressVisible();
	updateError();
}

DatasyncDialog::~DatasyncDialog()
{
	delete ui;
}

void DatasyncDialog::registerWidgets()
{
	WidgetPresenter::registerWidget<DatasyncDialog>();
	WidgetPresenter::registerWidget<UserDataExchangeDialog>();
	WidgetPresenter::registerWidget<ChangeRemoteDialog>();
}

void DatasyncDialog::updateStatus()
{
	ui->statusLabel->setText(control->statusString());
}

void DatasyncDialog::updateProgressVisible()
{
	ui->stackedWidget->setCurrentIndex(control->showProgress() ? 0 : 1);
}

void DatasyncDialog::updateProgress()
{
	ui->progressBar->setValue(control->syncProgress() * 1000);
}

void DatasyncDialog::updateError()
{
	ui->errorLabel->setText(control->authError());
}

void DatasyncDialog::on_action_Export_to_file_triggered()
{
	auto path = DialogMaster::getSaveFileName(this,
											  tr("Export user data"),
											  QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
											  tr("Datasync Export File (*.dse);;All Files (*)"));
	if(!path.isNull()) {
		auto exportFile = new QFile(path);
		if(exportFile->open(QIODevice::WriteOnly))
			control->exportUserData(exportFile);
		else {
			CoreMessage::critical(tr("User data export"), tr("Failed to create file with error: %1").arg(exportFile->errorString()));
			delete exportFile;
		}
	}
}

void DatasyncDialog::on_action_Import_from_file_triggered()
{
	auto path = DialogMaster::getOpenFileName(this,
											  tr("Import user data"),
											  QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
											  tr("Datasync Export File (*.dse);;All Files (*)"));
	if(!path.isNull()) {
		auto importFile = new QFile(path);
		if(importFile->open(QIODevice::ReadOnly))
			control->importUserData(importFile);
		else {
			CoreMessage::critical(tr("User data import"), tr("Failed to read file with error: %1").arg(importFile->errorString()));
			delete importFile;
		}
	}
}
