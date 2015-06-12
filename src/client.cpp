#include "client.h"
#include "salon.h"
#include <QDebug>

Client::Client(QObject *parent) :
    QThread(parent)
{

    connect(this, SIGNAL(clientArrive(Client*)), (Salon*) this->parent(), SLOT(clientArrive(Client *)));
    connect(this, SIGNAL(clientParti()), this, SIGNAL(finished()));
    connect(this, SIGNAL(finished()), this,SLOT(deleteLater()));
}

void Client::arriverSalon()
{
    emit clientArrive(this);;
}

void Client::partirSalon()
{
    emit clientParti();
}

