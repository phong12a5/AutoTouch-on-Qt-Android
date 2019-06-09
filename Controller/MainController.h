#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "ShellOperation.h"
#include "JavaCommunication.h"
#include "Processing/ImageProcessing.h"
#include "ThreadController.h"
#include "AppEnums.h"

class MainController : public QObject
{
    Q_OBJECT

private:
    explicit MainController(QObject *parent = nullptr);

public:
    static MainController* instance();
    void initController();

    void requestLikeNewFeeds();
#if 0
    bool requestAddConfirmFrined();
    bool requestAddFriendByUID();
#endif

public:
    int currentScreen() const;
    void setCurrentScreen(const int data);

    int requestedAction();
    void setRequestedAction(int data);

private:
    void startCheckCurrentScreen();

private:
    static MainController* m_instance;
    ShellOperation m_shellOperation;
    JavaCommunication m_javaCom;
    ThreadController multiThreadController;

    int m_currentScreen;
    int m_requestedAction;

signals:
    void currentScreenChanged();
    void requestedActionChanged();

public slots:
    void onChangeScreen();

};

#endif // MAINCONTROLLER_H
