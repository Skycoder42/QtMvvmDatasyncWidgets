#include "userdataexchangedialog.h"
#include "ui_userdataexchangedialog.h"
#include <dialogmaster.h>

UserDataExchangeDialog::UserDataExchangeDialog(Control *mControl, QWidget *parent) :
	QDialog(parent),
	control(static_cast<UserDataExchangeControl*>(mControl)),
	ui(new Ui::UserDataExchangeDialog)
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this);
}

UserDataExchangeDialog::~UserDataExchangeDialog()
{
	delete ui;
}
