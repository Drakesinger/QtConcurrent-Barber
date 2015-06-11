#include "salon.h"
#include "client.h"
#include "barbier.h"

#include <QtWidgets>
#include <QSemaphore>
#include <QDebug>

Salon::Salon(QWidget *parent) :
    QGraphicsView(parent)
{
    barbier= new Barbier(this);
    semaphoreSalon= new QSemaphore(5);
    fileAttente=  new QQueue<Client>();
}

void Salon::clientArrive(Client c)
{
    qDebug()<<"salon.clientArrivé"<<endl;

    if(semaphoreSalon->available()!=0)
    {
        if(barbier->getSemaphore().available())
        {
            barbier->appelerClientSuivant(c);
        }
        else
        {
            semaphoreSalon->acquire();
            fileAttente->enqueue(c);
            mettreAJourFile();
        }
    }
    else
    {
        c.partirSalon();;
    }

}

void Salon::barbierFiniCoupe(Client c)
{
    c.partirSalon();
    semaphoreSalon->release();
    if(!fileAttente->isEmpty())
    {
        barbier->appelerClientSuivant(fileAttente->dequeue());
    }
    else
    {
        barbier->dormir();
    }
}

void Salon::mettreAJourFile()
{
    qDebug()<<"salon.mettreAJourFile()"<<endl;

    //Animation...
}
