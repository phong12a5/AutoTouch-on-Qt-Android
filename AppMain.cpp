#include "AppMain.h"

#define MODEL Model::instance()
#define MAIN_CONTROLLER MainController::instance()

AppMain::AppMain(QObject *parent) : QObject(parent)
{
    m_view = nullptr;
}

void AppMain::initApplication(QQuickView *view)
{
    LOG;
    if(view == nullptr){
        LOG << "View is NULL >> EXIT";
        return;
    }

    // Init Main controller
    MAIN_CONTROLLER->initController();

    //Setting App Engine
    m_view = view;

    //Set context property
    m_view->rootContext()->setContextProperty("APP_MODEL",MODEL);

    //Register Enum class
    qmlRegisterType<AppEnums>("AppEnums", 1, 0, "AppEnums");

    // Set screen size
    MODEL->setHeightDisplay(m_view->screen()->availableSize().height());
    MODEL->setWidthDisplay(m_view->screen()->availableSize().width());

    //Connect  signal - slot
    this->connectSignalSlot();
}

void AppMain::connectSignalSlot() const
{
    LOG;
    QObject::connect(MODEL,SIGNAL(requestTestCase(int)),this,SLOT(onRequestTestCase(int)));
}

void AppMain::onRequestTestCase(int testCase)
{
    LOG << "testCase: " << testCase;
    switch (testCase) {
    case AppEnums::HMI_CASE_LIKE_NEW_FEED:
        LOG << MAIN_CONTROLLER->requestLikeNewFeeds();
        break;
    case AppEnums::HMI_CASE_ADD_CONFIRM_FRIEND:
        LOG << MAIN_CONTROLLER->requestAddConfirmFrined();
        break;
    case AppEnums::HMI_CASE_ADD_FRIEND_BY_UID:
        LOG << MAIN_CONTROLLER->requestAddFriendByUID();
        break;
    default:
        break;
    }
}
