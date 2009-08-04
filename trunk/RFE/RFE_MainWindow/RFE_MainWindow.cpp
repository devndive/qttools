#include "RFE_MainWindow.h"

#include <QtGui>

namespace RFE
{

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
	rfe_widget = new RFE::Widget(this);
	setCentralWidget(rfe_widget);

	setWindowTitle("RFE - Resource File Editor");
	setupMenuBar();
	setupStatusBar();
}

void MainWindow::setupMenuBar()
{
	QMenuBar *myMenuBar = new QMenuBar(this);

	QMenu *fileMenu = myMenuBar->addMenu(tr("&File"));
	QMenu *itemMenu = myMenuBar->addMenu(tr("&Entries"));

	fileMenu->addAction(QIcon(":/icons/save.png"), tr("Save"), rfe_widget, SLOT(saveResourceFile()), QKeySequence::Save);
	fileMenu->addAction(QIcon(":/icons/load.png"), tr("Open"), rfe_widget, SLOT(loadResourceFile()), QKeySequence::Open);
	fileMenu->addSeparator();
	fileMenu->addAction(QIcon(":/icons/exit.png"), tr("Quit"), qApp, SLOT(quit()), QKeySequence(tr("Ctrl+Q")));

	itemMenu->addAction(QIcon(":/icons/group_add.png"), tr("add Group"), rfe_widget, SLOT(addNewGroup()), QKeySequence(tr("Ctrl+G")));
	itemMenu->addAction(QIcon(":/icons/add.png"), tr("add Entry"), rfe_widget, SLOT(addNewItem()), QKeySequence(tr("Ctrl+E")));
	itemMenu->addAction(QIcon(":/icons/rem.png"), tr("delete Entry"), rfe_widget, SLOT(onRemove()), QKeySequence::Delete);

	setMenuBar(myMenuBar);
}

void MainWindow::setupStatusBar()
{
}

} // namepsace RFE
