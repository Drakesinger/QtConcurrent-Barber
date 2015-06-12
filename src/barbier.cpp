#include "barbier.h"
#include "salon.h"
#include "client.h"
#include <QSemaphore>
#include <QDebug>


Barbier::Barbier(QObject *parent) :
    QThread(parent)
{
    semBarberReady= new QSemaphore(1);

    //connect(this, SIGNAL(finiCoupe(Client*)),(Salon*) this->parent(), SLOT(barbierFiniCoupe(Client*)));
}

QSemaphore* Barbier::getSemaphore()
{
    return semBarberReady;
}

void Barbier::run()
{
    while(true)
    dormir();
}

void Barbier::dormir()
{
    //qDebug() << "Barber sleeping";
}

void Barbier::appelerClientSuivant(Client* c)
{
    semBarberReady->acquire();
    couperCheveux(c);
}
void Barbier::couperCheveux(Client *c)
{
    //this->wait(5000);
    this->sleep(2);
    semBarberReady->release();
    emit finiCoupe(c);
}


