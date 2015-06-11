#include "client.h"
#include "salon.h"
#include <QDebug>

Client::Client(QObject *parent) :
    QThread(parent)
{

    run();

    connect(this, SIGNAL(clientArriive(this)), Salon, SLOT(clientArrive(this)));
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
    emit clientArriive(this);;
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
