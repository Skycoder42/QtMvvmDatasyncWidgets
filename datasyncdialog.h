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

	static void registerWidgets();

private slots:
	void updateStatus();
	void updateProgressVisible();
	void updateProgress();
	void updateError();

	void on_action_Export_to_file_triggered();
	void on_action_Import_from_file_triggered();

private:
	DatasyncControl *control;
	Ui::DatasyncDialog *ui;
};

#endif // DATASYNCDIALOG_H
