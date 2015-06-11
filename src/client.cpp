#include "client.h"
#include "salon.h"
#include <QDebug>

Client::Client(QObject *parent) :
    QThread(parent)
{

    run();

    connect(this, SIGNAL(clientArrive(Client c)), (Salon*) this->parent(), SLOT(clientArrive(Client c)));
    connect(this, SIGNAL(clientParti()), this, SLOT(deleteLater()));
}

void Client::run()
{
    qDebug()<<"client.run()"<<endl;
    arriverSalon();
}

void Client::arriverSalon()
{
    //Animation...
    qDebug()<<"client.arriverSalon()"<<endl;
    emit clientArrive(this);;
}

void Client::partirSalon()
{
    qDebug()<<"client.partirSalon()"<<endl;

    //Animation...

    emit clientParti();
}

void Client::attendreSonTour()
{
    qDebug()<<"client.attendreSonTour()"<<endl;


}

void Client::avancerDansFileAttente()
{
    qDebug()<<"client.avancerDansFileAttente()"<<endl;
    //Animation...


}

void Client::prendreChaise()
{
    qDebug()<<"client.prendreChaise()"<<endl;
    //Animation...

}
