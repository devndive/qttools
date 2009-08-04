#include <QApplication>

#include "RFE_MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QString locale = QLocale::system().name();
	QTranslator translator;
	translator.load(QString("translations/RFE_") + locale);
	app.installTranslator(&translator);

	RFE::MainWindow mainWindow;
	mainWindow.show();
	
	return( app.exec() );
}
