#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

signals:
    void operate();

public slots:
    void doFinish();

};

#endif // CONTROLLER_H
