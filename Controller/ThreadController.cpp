#include "ThreadController.h"
#include "AppMain.h"

ThreadController::ThreadController(QObject *parent) : QObject(parent)
{

}

ThreadController::~ThreadController()
{
    m_checkScreenThread.quit();
    m_checkScreenThread.wait();
}

void ThreadController::startNewThreads()
{
    LOG << "[ThreadController]";

    checkScreenWorker.moveToThread(&m_checkScreenThread);
    connect(&m_checkScreenThread, &QThread::finished, &checkScreenWorker, &QObject::deleteLater);
    connect(this, &ThreadController::operate, &checkScreenWorker, &CheckCurrSrcThread::doWork);
    m_checkScreenThread.start();
}
