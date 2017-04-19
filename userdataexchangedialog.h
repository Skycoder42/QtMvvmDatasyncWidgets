#ifndef USERDATAEXCHANGEDIALOG_H
#define USERDATAEXCHANGEDIALOG_H

#include <QDialog>
#include <userdataexchangecontrol.h>
#include <qobjectproxymodel.h>

namespace Ui {
class UserDataExchangeDialog;
}

class UserDataExchangeDialog : public QDialog
{
	Q_OBJECT

public:
	Q_INVOKABLE UserDataExchangeDialog(Control *mControl, QWidget *parent = nullptr);
	~UserDataExchangeDialog();

private slots:
	void on_applyButton_clicked();

	void on_treeView_activated(const QModelIndex &index);

private:
	UserDataExchangeControl *control;
	Ui::UserDataExchangeDialog *ui;
	QObjectProxyModel *proxyModel;
};

#endif // USERDATAEXCHANGEDIALOG_H
