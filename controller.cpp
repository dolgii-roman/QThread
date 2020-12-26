#include "controller.h"
#include <QDebug>
#include <QTimer>
#include "worker.h"
#include <QThread>

Controller::Controller(QObject *parent) :
    QObject(parent) {
    Worker *worker = new Worker;
    worker->moveToThread( &workerThread );

    QTimer::singleShot( 100, worker, SLOT(doWork()) );
    connect( &workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()) );
    connect( worker, SIGNAL(ready()), this, SLOT(doFinish()) );
    workerThread.start();
}

Controller::~Controller() {
    workerThread.quit();
    workerThread.wait();
}

void Controller::doFinish() {
    qDebug() << "Finish " << QThread::currentThreadId();
}
