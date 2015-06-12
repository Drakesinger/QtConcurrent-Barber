#include "salon.h"
#include "client.h"
#include "barbier.h"

#include <QSemaphore>
#include <QDebug>

Salon::Salon(QWidget *parent):QWidget(parent)
{
    setWindowTitle(tr("Barbier"));

    barbier = new Barbier(/*this*/);
    semaphoreSalon = new QSemaphore(5);
    fileAttente =  new QQueue<Client*>();

    btnAjouterClient= new QPushButton(tr("Ajouter client"),this);
    textEdit= new QTextEdit(this);
    textEdit->setReadOnly(true);

    layout();
    connect(this,SIGNAL(barbierDort()),barbier,SLOT(dormir()));
    connect(barbier, SIGNAL(finiCoupe(Client*)), this, SLOT(barbierFiniCoupe(Client*)));
    connect(this, SIGNAL(clientEstAppelle(Client*)),barbier,SLOT(appelerClientSuivant(Client*)));
    connect(btnAjouterClient, SIGNAL(clicked()), this, SLOT(creerClient()));

//    for (int var = 0; var < 2; ++var) {
//        creerClient();
//    }

    barbier->start();
}

void Salon::clientArrive(Client* c)
{
    textEdit->setText(textEdit->toPlainText() + "client arrivé\n");

    if(semaphoreSalon->available()!=0)
    {
        if(barbier->getSemaphore()->available())
        {
            textEdit->setText(textEdit->toPlainText() + "barbier appelle prochain client\n");
            emit clientEstAppelle(c);
        }
        else
        {
            textEdit->setText(textEdit->toPlainText() + "barbier occupé\n\tclient va dans file d'attente\n");
            semaphoreSalon->acquire();
            fileAttente->enqueue(c);
        }
    }
    else
    {
        textEdit->setText(textEdit->toPlainText() + "file d'attente pleine\n\t client part\n");
        emit clientPartDuSalon(c);
    }

}

void Salon::barbierFiniCoupe(Client *c)
{
    textEdit->setText(textEdit->toPlainText() + "barbier a fini coupe\n");
    textEdit->setText(textEdit->toPlainText() + "client part\n\n");
    emit clientPartDuSalon(c);
    semaphoreSalon->release();
    if(!fileAttente->isEmpty())
    {
        textEdit->setText(textEdit->toPlainText() + "barbier appelle prochain client\n");
        emit clientEstAppelle(fileAttente->dequeue());
    }
    else
    {
        textEdit->setText(textEdit->toPlainText() + "barbier va dormir\n");
        emit barbierDort();
    }
}

void Salon::creerClient()
{
    Client* c = new Client(/*this*/);

    connect(c, SIGNAL(clientArrive(Client*)), this, SLOT(clientArrive(Client*)));
    connect(this,SIGNAL(clientPartDuSalon(Client*)),c,SLOT(partirSalon(Client*)));

    c->start();
}


void Salon::layout()
{
    QVBoxLayout *vBox= new QVBoxLayout(this);
    vBox->addWidget(textEdit);
    vBox->addWidget(btnAjouterClient);
}
