#ifndef CHANGEREMOTEDIALOG_H
#define CHANGEREMOTEDIALOG_H

#include <QAbstractButton>
#include <QDialog>
#include <changeremotecontrol.h>

namespace Ui {
class ChangeRemoteDialog;
}

class ChangeRemoteDialog : public QDialog
{
	Q_OBJECT

public:
	Q_INVOKABLE ChangeRemoteDialog(Control *mControl = nullptr, QWidget *parent = nullptr);
	~ChangeRemoteDialog();

public slots:
	void accept() override;

private slots:
	void on_buttonBox_clicked(QAbstractButton *button);
	void on_urlLineEdit_textEdited();

private:
	ChangeRemoteControl *_control;
	Ui::ChangeRemoteDialog *ui;
};

#endif // CHANGEREMOTEDIALOG_H
