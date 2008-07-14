#ifndef __RFE_MAINWINDOW_H__
#define __RFE_MAINWINDOW_H__

#include <QMainWindow>

#include "RFE_Widget.h"

namespace RFE
{

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
	void setupMenuBar();
	void setupStatusBar();

	RFE::Widget *rfe_widget;

public:
	MainWindow(QWidget *parent = 0);
};

} // namespace RFE

#endif // __RESOURCEFILEEDITOR_MAINWINDOW_H__
