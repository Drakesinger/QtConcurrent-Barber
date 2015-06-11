#include "barbier.h"
#include "salon.h"
#include "client.h"
#include <QSemaphore>
#include <QDebug>


Barbier::Barbier(QObject *parent) :
    QThread(parent)
{
    sem= new QSemaphore(1);

    run();
    connect(this, SIGNAL(finiCoupe(Client* c)),(Salon*) this->parent(), SLOT(barbierFiniCoupe(Client* c)));
}

QSemaphore* Barbier::getSemaphore()
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

void Barbier::appelerClientSuivant(Client* c)
{
    qDebug()<<"barbier.appelerClientSuivant()"<<endl;
    //Animation...

    sem->acquire();
    couperCheveux(c);
}
void Barbier::couperCheveux(Client *c)
{
    qDebug()<<"barbier.couperCheveux()"<<endl;

    //Animation...

    sem->release();
    emit finiCoupe(c);
}


