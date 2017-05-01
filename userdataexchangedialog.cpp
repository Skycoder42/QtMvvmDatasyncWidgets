#include "userdataexchangedialog.h"
#include "ui_userdataexchangedialog.h"
#include <QSortFilterProxyModel>
#include <dialogmaster.h>

UserDataExchangeDialog::UserDataExchangeDialog(Control *mControl, QWidget *parent) :
	QDialog(parent),
	control(static_cast<UserDataExchangeControl*>(mControl)),
	ui(new Ui::UserDataExchangeDialog),
	proxyModel(new QObjectProxyModel({tr("Device Name"), tr("Address")}, this))
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this);

	connect(control, &UserDataExchangeControl::portChanged,
			ui->portSpinBox, &QSpinBox::setValue);
	connect(control, &UserDataExchangeControl::deviceNameChanged,
			ui->deviceNameLineEdit, &QLineEdit::setText);
	connect(ui->deviceNameLineEdit, &QLineEdit::editingFinished,
			control, [=](){
		control->setDeviceName(ui->deviceNameLineEdit->text());
	});
	ui->portSpinBox->setValue(control->port());
	ui->deviceNameLineEdit->setText(control->deviceName());

	proxyModel->setSourceModel(control->model());
	proxyModel->addMapping(0, Qt::DisplayRole, "name");
	proxyModel->addMapping(1, Qt::DisplayRole, "address");

	auto sort = new QSortFilterProxyModel(this);
	sort->setSourceModel(proxyModel);

	ui->treeView->setModel(sort);
}

UserDataExchangeDialog::~UserDataExchangeDialog()
{
	delete ui;
}

void UserDataExchangeDialog::on_applyButton_clicked()
{
	control->setPort((quint16)ui->portSpinBox->value());
}

void UserDataExchangeDialog::on_treeView_activated(const QModelIndex &index)
{
	if(index.isValid()) {
		auto rIndex = proxyModel->mapToSource(index);
		if(rIndex.isValid())
			control->exportTo(index.row());
	}
}
