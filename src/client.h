#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QThread>

class Client : public QThread
{
    Q_OBJECT
public:
    Client(QObject *parent = 0);

protected:
    void run();

signals:
    void clientArriive();
    void clientParti();

public slots:
    void arriverSalon();
    void partirSalon();
    void attendreSonTour();
    void avancerDansFileAttente();
    void prendreChaise();
};

#endif // CLIENT_H
