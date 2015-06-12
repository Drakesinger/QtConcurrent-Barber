#include "client.h"
#include "salon.h"
#include <QDebug>

Client::Client(QObject *parent) :
    QThread(parent)
{
    connect(this, SIGNAL(clientParti()), this, SIGNAL(finished()));
    connect(this, SIGNAL(finished()), this,SLOT(deleteLater()));
}

void Client::run()
{
    arriverSalon();
}

void Client::arriverSalon()
{
    emit clientArrive(this);;
}

void Client::partirSalon(Client* c)
{
    emit clientParti();
}

