#include <QGuiApplication>
#include <QDebug>
#include <QScreen>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include "Model.h"
#include <QQuickView>
#include <QProcess>
#include "Controller/ShellOperation.h"
#include "Processing/ImageProcessing.h"
#include <QTest>
#include "AppMain.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AppMain appMain;
    QQuickView *view = new QQuickView;
    appMain.initApplication(view);
    view->setSource(QStringLiteral("qrc:/main.qml"));
    view->show();


#ifdef ANDROID_KIT
//    ShellOperation shellOperation;
//    shellOperation.initWorkSpace();
//    shellOperation.makeDir("ScreenShot/");
//    shellOperation.openApplication("com.facebook.katana","com.facebook.katana.LoginActivity");


//    QTest::qSleep(3000);
//    QList<QPoint> pos = ImageProcessing::findImageOnImage("/sdcard/DCIM/like.png",shellOperation.screenShot("Screen.png"));
//    LOG << "Matching Positions: " << pos;

//    if(pos.count() > 0)
//        shellOperation.callTapEvent(pos.at(0).x(),pos.at(0).y());

#endif
//    Model model(view);

    return app.exec();
}

