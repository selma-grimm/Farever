#include "MainWindow.h"
#include <QApplication>

#define SECOND_DESKTOP 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
#if SECOND_DESKTOP
	if(QApplication::desktop()->screenCount()>1)
	{
		QRect rect = QApplication::desktop()->screenGeometry(1);
		w.move(rect.topLeft());
	}
#endif

    return a.exec();
}
