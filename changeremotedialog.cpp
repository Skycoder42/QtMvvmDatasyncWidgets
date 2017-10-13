#include "changeremotedialog.h"
#include "ui_changeremotedialog.h"
#include <QPushButton>
#include <qurlvalidator.h>
#include <dialogmaster.h>

ChangeRemoteDialog::ChangeRemoteDialog(Control *mControl, QWidget *parent) :
	QDialog(parent),
	_control(static_cast<ChangeRemoteControl*>(mControl)),
	ui(new Ui::ChangeRemoteDialog)
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this);

	ui->urlLineEdit->setValidator(new QUrlValidator({QStringLiteral("ws"), QStringLiteral("wss")}, this));
	ui->urlLineEdit->setText(_control->url().toString());
}

ChangeRemoteDialog::~ChangeRemoteDialog()
{
	delete ui;
}

void ChangeRemoteDialog::accept()
{
	_control->setUrl(QUrl(ui->urlLineEdit->text()));
	_control->setChangeSecret(ui->secretCheckBox->isChecked());
	_control->setServerSecret(ui->secretLineEdit->text());
	_control->setResetData(ui->clearDataCheckBox->isChecked());
	_control->accept();
	QDialog::accept();
}

void ChangeRemoteDialog::on_buttonBox_clicked(QAbstractButton *button)
{
	switch (ui->buttonBox->standardButton(button)) {
	case QDialogButtonBox::RestoreDefaults:
		_control->setResetData(ui->clearDataCheckBox->isChecked());
		_control->reset();
		QDialog::accept();
		break;
	default:
		break;
	}
}

void ChangeRemoteDialog::on_urlLineEdit_textEdited()
{
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->urlLineEdit->hasAcceptableInput());
}
