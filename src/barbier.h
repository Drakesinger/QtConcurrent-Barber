#ifndef BARBIER_H
#define BARBIER_H

#include <QObject>
#include <QThread>
class QSemaphore;
class Client;

class Barbier : public QThread
{
    Q_OBJECT
public:
    Barbier(QObject *parent = 0);
    QSemaphore* getSemaphore();
    QSemaphore *sem;

    void run() Q_DECL_OVERRIDE;
signals:
    void finiCoupe(Client* c);

public slots:
    void dormir();
    void couperCheveux(Client* c);
    void appelerClientSuivant(Client *c);

private:

};

#endif // BARBIER_H
