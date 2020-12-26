#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = 0)
        :QThread( parent ), m_bStopped( false ), m_bPause( false ) {}

    ~WorkerThread() {
        stop(); // Qt 5.x: requestInterruption();
        quit();
        wait();
    }

    void pause() {
        // works as toggled way
        QMutexLocker locker( &m_mutex );
        m_bPause = !m_bPause;
        if ( !m_bPause ) {
            // wakeAll
            m_pauseCondition.wakeAll();
        }
    }

    void stop() {
        QMutexLocker locker( &m_mutex );
        m_bStopped = true;
        if ( m_bPause ) {
            // wake pause condition if the thread is waiting
            m_bPause = false;
            m_pauseCondition.wakeAll();
        }
    }

signals:
    void resultReady( int value );

protected:
    virtual void run() Q_DECL_OVERRIDE {
        int nValue = 0;
        {
            QMutexLocker locker( &m_mutex );
            // reset the state
            m_bStopped = false;
            m_bPause = false;
        }

        // Qt 5.x: while ( !isInterruptionRequested() && nValue <= 100 )
        while ( nValue <= 100 ) {
            msleep( 50 );
            resultReady( nValue );
            nValue ++;

            {
                QMutexLocker locker( &m_mutex );
                if ( m_bStopped ) {
                    break;
                }
            }

            {
                QMutexLocker locker(&m_mutex);
                if (m_bPause) {
                    m_pauseCondition.wait( &m_mutex );
                    if ( m_bStopped ) {
                        break;
                    }
                }
            }
        }
    }

private:
    bool m_bStopped;
    bool m_bPause;
    QMutex m_mutex;
    QWaitCondition m_pauseCondition;
};

#endif // WORKERTHREAD_H
