#include "datasyncdialog.h"
#include "ui_datasyncdialog.h"
#include <widgetpresenter.h>
#include <dialogmaster.h>
#include <QStandardPaths>
#include <coremessage.h>
#include "userdataexchangedialog.h"

DatasyncDialog::DatasyncDialog(Control *mControl, QWidget *parent) :
	QDialog(parent),
	control(static_cast<DatasyncControl*>(mControl)),
	ui(new Ui::DatasyncDialog)
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this, true);

	auto seperator = new QAction(this);
	seperator->setSeparator(true);
	ui->exportButton->addActions({
									 ui->action_Network_exchange,
									 seperator,
									 ui->action_Export_to_file,
									 ui->action_Import_from_file
								 });

	connect(control, &DatasyncControl::syncEnabledChanged,
			ui->syncCheckBox, &QCheckBox::setChecked);
	connect(ui->syncCheckBox, &QCheckBox::clicked,
			control, &DatasyncControl::setSyncEnabled);
	connect(control, &DatasyncControl::statusStringChanged,
			this, &DatasyncDialog::updateStatus);
	connect(control, &DatasyncControl::showProgressChanged,
			this, &DatasyncDialog::updateProgressVisible);
	connect(control, &DatasyncControl::syncProgressChanged,
			this, &DatasyncDialog::updateProgress);
	connect(ui->action_Network_exchange, &QAction::triggered,
			control, &DatasyncControl::initExchange);
	ui->syncCheckBox->setChecked(control->syncEnabled());
	updateStatus();
	updateProgress();
	updateProgressVisible();

	connect(ui->syncButton, &QPushButton::clicked,
			control, &DatasyncControl::sync);
	connect(ui->resyncButton, &QPushButton::clicked,
			control, &DatasyncControl::resync);
}

DatasyncDialog::~DatasyncDialog()
{
	delete ui;
}

void DatasyncDialog::registerWidgets()
{
	WidgetPresenter::registerWidget<DatasyncDialog>();
	WidgetPresenter::registerWidget<UserDataExchangeDialog>();
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
