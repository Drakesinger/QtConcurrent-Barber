#include "salon.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salon s;
    s.show();

    return a.exec();
}
