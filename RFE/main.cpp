#include <QApplication>

#include "RFE_MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	RFE::MainWindow mainWindow;
	mainWindow.show();
	
	return( app.exec() );
}
