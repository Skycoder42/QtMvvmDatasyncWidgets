#include "datasyncdialog.h"
#include "ui_datasyncdialog.h"
#include <dialogmaster.h>

DatasyncDialog::DatasyncDialog(Control *mControl, QWidget *parent) :
	QDialog(parent),
	control(static_cast<DatasyncControl*>(mControl)),
	ui(new Ui::DatasyncDialog)
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this);

	connect(control, &DatasyncControl::statusStringChanged,
			this, &DatasyncDialog::updateStatus);
	connect(control, &DatasyncControl::showProgressChanged,
			this, &DatasyncDialog::updateProgressVisible);
	connect(control, &DatasyncControl::syncProgressChanged,
			this, &DatasyncDialog::updateProgress);
	updateStatus();
	updateProgress();
	updateProgressVisible();
}

DatasyncDialog::~DatasyncDialog()
{
	delete ui;
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
