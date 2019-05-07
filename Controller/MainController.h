#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "ShellOperation.h"
#include "JavaCommunication.h"
#include "Processing/ImageProcessing.h"

class MainController : public QObject
{
    Q_OBJECT

private:
    explicit MainController(QObject *parent = nullptr);

public:
    static MainController* instance();
    void initController();

    bool requestLikeNewFeeds();
    bool requestAddConfirmFrined();
    bool requestAddFriendByUID();

private:
    static MainController* m_instance;
    ShellOperation m_shellOperation;
    JavaCommunication m_javaCom;

signals:

public slots:
};

#endif // MAINCONTROLLER_H
