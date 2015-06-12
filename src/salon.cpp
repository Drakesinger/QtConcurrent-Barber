#include "salon.h"
#include "client.h"
#include "barbier.h"

#include <QSemaphore>
#include <QDebug>

Salon::Salon(QWidget *parent):QWidget(parent)
{
    setWindowTitle(tr("Barbier"));
    barbier= new Barbier(this);
    semaphoreSalon= new QSemaphore(5);
    fileAttente=  new QQueue<Client*>();

    btnAjouterClient= new QPushButton(tr("Ajouter client"),this);
    textEdit= new QTextEdit(this);
    textEdit->setReadOnly(true);

    layout();

    barbier->run();
    connect(btnAjouterClient, SIGNAL(clicked()), this, SLOT(creerClient()));
}

void Salon::clientArrive(Client* c)
{
    textEdit->setText(textEdit->toPlainText() + "client arrivé\n");

    if(semaphoreSalon->available()!=0)
    {
        if(barbier->getSemaphore()->available())
        {
            textEdit->setText(textEdit->toPlainText() + "barbier appelle prochain client\n");
            barbier->appelerClientSuivant(c);
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
        c->partirSalon();;
    }

}

void Salon::barbierFiniCoupe(Client *c)
{
    textEdit->setText(textEdit->toPlainText() + "barbier a fini coupe\n");
    textEdit->setText(textEdit->toPlainText() + "client part\n\n");
    c->partirSalon();
    semaphoreSalon->release();
    if(!fileAttente->isEmpty())
    {
        textEdit->setText(textEdit->toPlainText() + "barbier appelle prochain client\n");
        barbier->appelerClientSuivant(fileAttente->dequeue());
    }
    else
    {
        textEdit->setText(textEdit->toPlainText() + "barbier va dormir\n");
        barbier->dormir();
    }
}

void Salon::creerClient()
{
    Client c(this);
    c.run();
}


void Salon::layout()
{
    QVBoxLayout *vBox= new QVBoxLayout(this);
    vBox->addWidget(textEdit);
    vBox->addWidget(btnAjouterClient);
}
