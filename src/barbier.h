#ifndef BARBIER_H
#define BARBIER_H

#include <QObject>
#include <QThread>
class QSemaphore;


class Barbier : public QThread
{
    Q_OBJECT
public:
    Barbier(QObject *parent = 0);
    QSemaphore getSemaphore();

protected:
    void run();
signals:
    void finiCoupe();

public slots:
    void dormir();
    void couperCheveux(Client c);
    void appelerClientSuivant(Client c);

private:
    QSemaphore *sem;
};

#endif // BARBIER_H
