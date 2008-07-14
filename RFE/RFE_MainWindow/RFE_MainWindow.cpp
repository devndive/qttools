#include "RFE_MainWindow.h"

#include <QtGui>

namespace RFE
{

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
	rfe_widget = new RFE::Widget(this);
	setCentralWidget(rfe_widget);

	setWindowTitle(tr("RFE - Resource File Editor"));
	setupMenuBar();
	setupStatusBar();
}

void MainWindow::setupMenuBar()
{
	QMenuBar *myMenuBar = new QMenuBar(this);

	QMenu *fileMenu = myMenuBar->addMenu(tr("&Datei"));
	QMenu *itemMenu = myMenuBar->addMenu(tr("&Einträge"));

	fileMenu->addAction(QIcon(":/icons/save.png"), tr("Speichern"), rfe_widget, SLOT(saveResourceFile()), QKeySequence(tr("Ctrl+S")));
	fileMenu->addAction(QIcon(":/icons/load.png"), tr("Öffnen"), rfe_widget, SLOT(loadResourceFile()), QKeySequence(tr("Ctrl+O")));
	fileMenu->addSeparator();
	fileMenu->addAction(QIcon(":/icons/exit.png"), tr("Beenden"), qApp, SLOT(quit()), QKeySequence(tr("Ctrl+B")));

	itemMenu->addAction(QIcon(":/icons/group_add.png"), tr("Neue Gruppe"), rfe_widget, SLOT(addNewGroup()), QKeySequence(tr("Ctrl+G")));
	itemMenu->addAction(QIcon(":/icons/add.png"), tr("Neuer Eintrag"), rfe_widget, SLOT(addNewItem()), QKeySequence(tr("Ctrl+E")));
	itemMenu->addAction(QIcon(":/icons/rem.png"), tr("Zeile löschen"), rfe_widget, SLOT(onRemove()), QKeySequence(tr("Ctrl+R")));

	setMenuBar(myMenuBar);
}

void MainWindow::setupStatusBar()
{
}

} // namepsace RFE
