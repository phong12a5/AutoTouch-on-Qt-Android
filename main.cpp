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
    LOG << "STARTING ....";
    LOG << "CURRENT DIR: " << QDir::currentPath();
    QGuiApplication app(argc, argv);

    AppMain appMain;
    QQuickView *view = new QQuickView;
    appMain.initApplication(view);
    view->setSource(QStringLiteral("qrc:/main.qml"));
    view->show();

    return app.exec();
}

