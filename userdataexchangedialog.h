#ifndef USERDATAEXCHANGEDIALOG_H
#define USERDATAEXCHANGEDIALOG_H

#include <QDialog>
#include <userdataexchangecontrol.h>

namespace Ui {
class UserDataExchangeDialog;
}

class UserDataExchangeDialog : public QDialog
{
	Q_OBJECT

public:
	Q_INVOKABLE UserDataExchangeDialog(Control *mControl, QWidget *parent = nullptr);
	~UserDataExchangeDialog();

private:
	UserDataExchangeControl *control;
	Ui::UserDataExchangeDialog *ui;
};

#endif // USERDATAEXCHANGEDIALOG_H
