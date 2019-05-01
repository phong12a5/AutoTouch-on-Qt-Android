#include <QGuiApplication>
#include <QQmlApplicationEngine>
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



/// Function Headers
void MatchingMethod( int, void* );


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    ShellOperation shellOperation;
    shellOperation.initWorkSpace();
    shellOperation.makeDir("ScreenShot/");
    shellOperation.openApplication("com.facebook.katana","com.facebook.katana.LoginActivity");


    QTest::qSleep(3000);
    QList<QPoint> pos = ImageProcessing::findImageOnImage("/sdcard/DCIM/like.png",shellOperation.screenShot("Screen.png"));
    LOG << "Matching Positions: " << pos;

    if(pos.count() > 0)
        shellOperation.callTapEvent(pos.at(0).x(),pos.at(0).y());
//    Model model(view);

    return app.exec();
}

