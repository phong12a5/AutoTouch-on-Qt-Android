#include "MainController.h"

MainController* MainController::m_instance = nullptr;

MainController::MainController(QObject *parent) : QObject(parent)
{
    m_currentScreen = AppEnums::HMI_START_UP_SCREEN;
    m_requestedAction = AppEnums::HMI_CASE_NONE_REQUEST;
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
    LOG;
    // Do nothing;
    connect(this,SIGNAL(currentScreenChanged()),this,SLOT(onChangeScreen()));
}

void MainController::requestLikeNewFeeds()
{
    LOG;
    // Request to show Facebook lite
    m_javaCom.openApplication("com.facebook.lite","com.facebook.lite.MainActivity");

    // Set requested action to Like new feeds
    this->setRequestedAction(AppEnums::HMI_CASE_LIKE_NEW_FEED);

    // Start new thread to check current screen
    this->startCheckCurrentScreen();

//    for(int count = 0; count < 10; count ++){
//        QString scrImg = m_shellOperation.screenShot("screen.png");
//        QList<QPoint> pointList = ImageProcessing::findImageOnImage(LIKE_ICON_LITE,scrImg);
//        if(pointList.isEmpty()){
//            count --;
//        }else{
//            for(int i = 0; i < pointList.count(); ++i){
//                LOG << "Matching point: " << pointList.at(i);
//                m_shellOperation.callTapEvent(pointList.at(i).x(),pointList.at(i).y());
//                delay(1000);
//                retVal = true;
//            }
//        }
//        m_shellOperation.callScrollEvent(QPoint(500,1300),QPoint(500,600));
//    }
}

int MainController::currentScreen() const
{
    return m_currentScreen;
}

void MainController::setCurrentScreen(const int data)
{
    if(m_currentScreen != data){
        m_currentScreen = data;
        emit currentScreenChanged();
    }
}

int MainController::requestedAction()
{
    return m_requestedAction;
}

void MainController::setRequestedAction(int data)
{
    if(m_requestedAction != data) {
        m_requestedAction = data;
        emit requestedActionChanged();
    }
}

#if 0
bool MainController::requestAddConfirmFrined()
{
    LOG;
    bool retVal = false;
    m_javaCom.openApplication("com.facebook.katana","com.facebook.katana.LoginActivity");
    delay(2000);
    QList<QPoint> profileIconPointList = ImageProcessing::findImageOnImage(PROFILE_ICON,m_shellOperation.screenShot("screen.png"));
    LOG << "profileIconPointList: " << profileIconPointList;
    LOG << "Finding profile icon ...";
    if(profileIconPointList.isEmpty()){
        LOG << "Couldn't found profile icon";
    }else{
        m_shellOperation.callTapEvent(profileIconPointList.at(0).x(),profileIconPointList.at(0).y());
        delay(2000);
        QList<QPoint> friendIconPointList = ImageProcessing::findImageOnImage(FRIEND_ICON,m_shellOperation.screenShot("screen.png"));
        LOG << "friendIconPointList: " << friendIconPointList;
        if(friendIconPointList.isEmpty()){
            LOG << "Couldn't found friend icon";
        }else{
            m_shellOperation.callTapEvent(friendIconPointList.at(0).x(),friendIconPointList.at(0).y());
            delay(1000);
            QList<QPoint> requestsIconPointList = ImageProcessing::findImageOnImage(REQUEST_ICON,m_shellOperation.screenShot("screen.png"));
            LOG << "requestsIconPointList: " << requestsIconPointList;
            if(requestsIconPointList.isEmpty()){
                LOG << "Couldn't found request icon";
            }else{
                m_shellOperation.callTapEvent(requestsIconPointList.at(0).x(),requestsIconPointList.at(0).y());
                delay(1000);
                for(int i = 0; i < 5; i++){
                    QList<QPoint> confirmIconPoint = ImageProcessing::findImageOnImage(CONFIRM_ICON,m_shellOperation.screenShot("screen.png"));
                    LOG << "confirmIconPointList: " << confirmIconPoint;
                    if(confirmIconPoint.isEmpty()){
                        LOG << "Couldn't found confirm icon";
                        break;
                    }else{
                        m_shellOperation.callTapEvent(confirmIconPoint.at(0).x(),confirmIconPoint.at(0).y());
                        delay(1000);
                    }
                }

                QList<QPoint> searchIconPoint = ImageProcessing::findImageOnImage(SEARCH_ICON,m_shellOperation.screenShot("screen.png"));
                LOG << "searchIconPoint: " << searchIconPoint;
                if(searchIconPoint.isEmpty()){
                    LOG << "Couldn't found search icon";
                }else{
                    m_shellOperation.callTapEvent(searchIconPoint.at(0).x(),searchIconPoint.at(0).y());
                    delay(1000);

                    QList<QPoint> suggestionIconPoint = ImageProcessing::findImageOnImage(SUGGEST_ICON,m_shellOperation.screenShot("screen.png"));
                    LOG << "suggestionIconPoint: " << suggestionIconPoint;
                    if(suggestionIconPoint.isEmpty()){
                        LOG << "Couldn't found suggestion icon";
                    }else{
                        m_shellOperation.callTapEvent(suggestionIconPoint.at(0).x(),suggestionIconPoint.at(0).y());
                        delay(1000);

                        for(int i = 0; i < 5; i++){
                            QList<QPoint> addFriendPoint = ImageProcessing::findImageOnImage(ADDFRIEND_ICON,m_shellOperation.screenShot("screen.png"));
                            LOG << "addFriendPoint: " << addFriendPoint;
                            if(addFriendPoint.isEmpty()){
                                LOG << "Couldn't found confirm icon";
                                break;
                            }else{
                                m_shellOperation.callTapEvent(addFriendPoint.at(0).x(),addFriendPoint.at(0).y());
                                delay(1000);
                            }
                        }
                    }
                }
            }
        }
    }
    return retVal;
}

bool MainController::requestAddFriendByUID()
{
    LOG;
    bool retVal = false;
    return retVal;
}
#endif

void MainController::startCheckCurrentScreen()
{
    LOG;
    multiThreadController.startNewThreads();
    emit multiThreadController.operate("Start new thread");
}

void MainController::onChangeScreen()
{
    switch (currentScreen()) {
    case AppEnums::HMI_START_UP_SCREEN:
        LOG << "HMI_START_UP_SCREEN";
        break;
    case AppEnums::HMI_NEW_FEED_SCREEN:
        LOG << "HMI_NEW_FEED_SCREEN";
        break;
    default:
        break;
    }
}
