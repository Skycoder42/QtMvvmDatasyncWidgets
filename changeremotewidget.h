#ifndef CHANGEREMOTEWIDGET_H
#define CHANGEREMOTEWIDGET_H

#include <QVariantMap>
#include <QWidget>

namespace Ui {
class ChangeRemoteWidget;
}

class ChangeRemoteWidget : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged USER true)

public:
	explicit ChangeRemoteWidget(QWidget *parent = nullptr);
	~ChangeRemoteWidget();

	QVariantMap data() const;

public slots:
	void setData(QVariantMap data);

signals:
	void dataChanged(QVariantMap data);

private:
	Ui::ChangeRemoteWidget *ui;
	QVariantMap _data;
};

#endif // CHANGEREMOTEWIDGET_H
