#ifndef DATASYNCDIALOG_H
#define DATASYNCDIALOG_H

#include <QDialog>
#include <datasynccontrol.h>

namespace Ui {
class DatasyncDialog;
}

class DatasyncDialog : public QDialog
{
	Q_OBJECT

public:
	Q_INVOKABLE DatasyncDialog(Control *mControl, QWidget *parent = nullptr);
	~DatasyncDialog();

private slots:
	void updateStatus();
	void updateProgressVisible();
	void updateProgress();

private:
	DatasyncControl *control;
	Ui::DatasyncDialog *ui;
};

#endif // DATASYNCDIALOG_H
