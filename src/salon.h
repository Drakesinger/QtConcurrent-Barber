#ifndef SALON_H
#define SALON_H

#include <QtWidgets>
class Barbier;
class QSemaphore;
class Client;
#include <QQueue>

class Salon : public QWidget
{
    Q_OBJECT
public:
    Salon(QWidget *parent = 0);

signals:
    void clientPartDuSalon(Client*);
    void clientEstAppelle(Client*);
    void barbierDort();
public slots:
    void clientArrive(Client *c);
    void barbierFiniCoupe(Client* c);
private slots:
    void creerClient();
private:
    void layout();

    Barbier *barbier;
    QSemaphore *semaphoreSalon;
    QQueue<Client*> *fileAttente;

    QPushButton *btnAjouterClient;
    QTextEdit *textEdit;
};

#endif // SALON_H
