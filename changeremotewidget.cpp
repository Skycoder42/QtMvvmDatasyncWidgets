#include "changeremotewidget.h"
#include "ui_changeremotewidget.h"
#include <qurlvalidator.h>

ChangeRemoteWidget::ChangeRemoteWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChangeRemoteWidget)
{
	ui->setupUi(this);

	ui->urlLineEdit->setValidator(new QUrlValidator({QStringLiteral("ws"), QStringLiteral("wss")}, this));
}

ChangeRemoteWidget::~ChangeRemoteWidget()
{
	delete ui;
}

QVariantMap ChangeRemoteWidget::data() const
{
	_data.insert(QStringLiteral("url"), ui->urlLineEdit->text());
	if(ui->secretCheckBox->isChecked())
		_data.insert(QStringLiteral("secret"), ui->secretLineEdit->text());
	else
		_data.remove(QStringLiteral("secret"));
	_data.insert(QStringLiteral("reset"), ui->clearDataCheckBox->isChecked());
	return _data;
}

void ChangeRemoteWidget::setData(QVariantMap data)
{
	_data = data;
	ui->urlLineEdit->setText(_data.value(QStringLiteral("url")).toString());
}
