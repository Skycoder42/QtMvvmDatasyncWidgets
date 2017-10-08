#include "changeremotewidget.h"
#include "ui_changeremotewidget.h"

ChangeRemoteWidget::ChangeRemoteWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChangeRemoteWidget)
{
	ui->setupUi(this);
}

ChangeRemoteWidget::~ChangeRemoteWidget()
{
	delete ui;
}

QVariantMap ChangeRemoteWidget::data() const
{
	return _data;
}

void ChangeRemoteWidget::setData(QVariantMap data)
{
	if (_data == data)
		return;

	_data = data;
	emit dataChanged(_data);
}
