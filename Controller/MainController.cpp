#include "MainController.h"

MainController* MainController::m_instance = nullptr;

MainController::MainController(QObject *parent) : QObject(parent)
{

}

MainController *MainController::instance()
{
    if(m_instance == nullptr){
        m_instance = new MainController();
    }
    return m_instance;
}

void MainController::initController()
{
    m_shellOperation.initShellCommand();
}

bool MainController::requestLikeNewFeeds()
{
    LOG;
    bool retVal = false;
    m_javaCom.openApplication("com.facebook.katana","com.facebook.katana.LoginActivity");
    QTest::qSleep(2000);
    for(int count = 0; count < 10; count ++){
        m_shellOperation.callScrollEvent(QPoint(500,1200),QPoint(500,300));
        QTest::qSleep(2000);
        QString scrImg = m_shellOperation.screenShot("screen.png");
        QList<QPoint> pointList = ImageProcessing::findImageOnImage("/sdcard/DCIM/like.png",scrImg);
        if(pointList.isEmpty()){
            count --;
            continue;
        }
        for(int i = 0; i < pointList.count(); ++i){
            LOG << "Matching point: " << pointList.at(i);
            m_shellOperation.callTapEvent(pointList.at(i).x(),pointList.at(i).y());
            QTest::qSleep(2000);
            retVal = true;
        }
    }
    return retVal;
}

bool MainController::requestAddConfirmFrined()
{
    LOG;
    bool retVal = false;
    return retVal;
}

bool MainController::requestAddFriendByUID()
{
    LOG;
    bool retVal = false;
    return retVal;
}
