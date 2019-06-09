#ifndef CHECKCURRSRCTHREAD_H
#define CHECKCURRSRCTHREAD_H

#include <QObject>
#include <AppDefines.h>
#include <QTimer>
#include "ADBCommand.h"
#include <QMutex>

class CheckCurrSrcThread : public QObject
{
    Q_OBJECT
public:
    explicit CheckCurrSrcThread(QObject *parent = nullptr);
    ~CheckCurrSrcThread();

private:
    int findScreen() const;

private:
    QTimer* m_updateCurrSrcTimer;

signals:
    void resultReady(const QString &result);

public slots:
    void doWork(const QString &parameter);
    void onUpdateCurrentScreen();
};

#endif // CHECKCURRSRCTHREAD_H
