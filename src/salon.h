#ifndef SALON_H
#define SALON_H

#include <QGraphicsView>
class Barbier;
class QSemaphore;
class Client;
#include <QQueue>

class Salon : public QGraphicsView
{
    Q_OBJECT
public:
    Salon(QWidget *parent = 0);

signals:

public slots:
    void clientArrive(Client c);
    void barbierFiniCoupe(Client c);
private:
    void mettreAJourFile();


    Barbier *barbier;
    QSemaphore *semaphoreSalon;
    QQueue<Client> *fileAttente;
};

#endif // SALON_H
