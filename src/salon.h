#ifndef SALON_H
#define SALON_H

#include <QGraphicsView>
class Barbier;
class QSemaphore;
class QQueue;

class Salon : public QGraphicsView
{
    Q_OBJECT
public:
    Salon(QWidget *parent = 0);

signals:

public slots:
    void clientArrive(Client c);
    void barbierFiniCoupe();
private:
    void mettreAJourFile();


    Barbier *barbier;
    QSemaphore *sem;
    QQueue<Client> *fileAttente;
};

#endif // SALON_H
