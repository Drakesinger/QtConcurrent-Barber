#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QThread>

class Client : public QThread
{
    Q_OBJECT
public:
    Client(QObject *parent = 0);

    void run() Q_DECL_OVERRIDE;

signals:
    void clientArrive(Client* c);
    void clientParti();

public slots:
    void arriverSalon();
    void partirSalon(Client* c);
};

#endif // CLIENT_H
