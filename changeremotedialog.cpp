#include "changeremotedialog.h"
#include "ui_changeremotedialog.h"
#include <QPushButton>
#include <qurlvalidator.h>
#include <dialogmaster.h>
#include <qtmvvmbinding.h>

ChangeRemoteDialog::ChangeRemoteDialog(Control *mControl, QWidget *parent) :
	QDialog(parent),
	_control(static_cast<ChangeRemoteControl*>(mControl)),
	ui(new Ui::ChangeRemoteDialog)
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this);

	ui->urlLineEdit->setValidator(new QUrlValidator({QStringLiteral("ws"), QStringLiteral("wss")}, this));
	ui->urlLineEdit->setText(_control->url().toString());

	QtMvvmBinding::bind(_control, "changeSecret", ui->secretCheckBox, "checked");
	QtMvvmBinding::bind(_control, "serverSecret", ui->secretLineEdit, "text");
	QtMvvmBinding::bind(_control, "resetData", ui->clearDataCheckBox, "checked");

	connect(_control, &ChangeRemoteControl::urlChanged,
			this, [this](const QUrl &url) {
		ui->urlLineEdit->setText(url.toString());
	});
}

ChangeRemoteDialog::~ChangeRemoteDialog()
{
	delete ui;
}

void ChangeRemoteDialog::accept()
{
	_control->accept();
	QDialog::accept();
}

void ChangeRemoteDialog::on_buttonBox_clicked(QAbstractButton *button)
{
	switch (ui->buttonBox->standardButton(button)) {
	case QDialogButtonBox::RestoreDefaults:
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

void ChangeRemoteDialog::on_urlLineEdit_editingFinished()
{
	_control->setUrl(QUrl(ui->urlLineEdit->text()));
}
