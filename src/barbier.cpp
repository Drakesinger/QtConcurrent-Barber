#include "barbier.h"
#include "salon.h"
#include "client.h"
#include <QSemaphore>
#include <QDebug>


Barbier::Barbier(QObject *parent) :
    QThread(parent)
{
    sem= new QSemaphore(1);

    connect(this, SIGNAL(finiCoupe(Client*)),(Salon*) this->parent(), SLOT(barbierFiniCoupe(Client*)));
}

QSemaphore* Barbier::getSemaphore()
{
    return sem;
}

void Barbier::run()
{
    dormir();
}

void Barbier::dormir()
{

}

void Barbier::appelerClientSuivant(Client* c)
{
    sem->acquire();
    couperCheveux(c);
}
void Barbier::couperCheveux(Client *c)
{
    this->wait(5000);
    sem->release();
    emit finiCoupe(c);
}


