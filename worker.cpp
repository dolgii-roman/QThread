#include "worker.h"
#include <QDebug>
#include <QThread>

Worker::Worker(QObject *parent) :
    QObject(parent) {
}

void Worker::doWork() {
    qDebug() << "Processing" << QThread::currentThreadId();
    emit ready();
}
