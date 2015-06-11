#include "salon.h"
#include "client.h"
#include "barbier.h"

#include <QtWidgets>
#include <QSemaphore>
#include <QQueue>
#include <QDebug>

Salon::Salon(QWidget *parent) :
    QGraphicsView(parent)
{
    barbier= new Barbier(this);
    sem= new Semaphore(5);
    fileAttente=  new QQueue<Client>();
}

void Salon::clientArrive(Client c)
{
    qDebug()<<"salon.clientArrivé"<<endl;

    if(sem->tryAcquire())
    {
        if(barbier->getSemaphore().tryAcquire())
        {
            barbier->couperCheveux(c);
        }
        else
        {
            fileAttente->enqueue(c);
            mettreAJourFile();
        }
    }
    else
    {
        c.partirSalon();;
    }

}

void Salon::mettreAJourFile()
{
    qDebug()<<"salon.mettreAJourFile()"<<endl;

    //Animation...
}
