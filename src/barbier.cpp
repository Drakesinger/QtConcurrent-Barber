#include "barbier.h"
#include "salon.h"
#include "client.h"
#include <QSemaphore>


Barbier::Barbier(QObject *parent) :
    QThread(parent)
{
    sem= new QSemaphore(1);

    run();
    connect(this, SIGNAL(finiCoupe()),(Salon*) this->parent(), SLOT(barbierFiniCoupe()));
}

QSemaphore Barbier::getSemaphore()
{
    return sem;
}

void Barbier::run()
{
    qDebug()<<"barbier.run()"<<endl;
    dormir();
}

void Barbier::dormir()
{
    qDebug()<<"barbier.dormir()"<<endl;
    //Animation...

}

void Barbier::couperCheveux(Client c)
{
    qDebug()<<"barbier.couperCheveux()"<<endl;

    //Animation...

    sem->release();
    emit finiCoupe();
}

void Barbier::appelerClientSuivant()
{
    qDebug()<<"barbier.appelerClientSuivant()"<<endl;
    //Animation...

    sem->acquire();
    couperCheveux();
}
