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
#include <QSysInfo>
#include <QNetworkInterface>


int main(int argc, char *argv[])
{
    LOG << "STARTING ....";
    LOG << "CURRENT DIR: " << QDir::currentPath();
    QGuiApplication app(argc, argv);



//    LOG <<	QSysInfo::bootUniqueId();
//    LOG <<	QSysInfo::buildAbi();
//    LOG <<	QSysInfo::buildCpuArchitecture();
//    LOG <<	QSysInfo::currentCpuArchitecture();
//    LOG <<	QSysInfo::kernelType();
//    LOG <<	QSysInfo::kernelVersion();
//    LOG <<	QSysInfo::machineHostName();
//    LOG <<	QSysInfo::machineUniqueId();
//    LOG <<	QSysInfo::prettyProductName();
//    LOG <<	QSysInfo::productType();
//    LOG <<	QSysInfo::productVersion();

//    for(auto interface: QNetworkInterface::allInterfaces())
//        LOG << interface.name() << interface.hardwareAddress();

    AppMain appMain;
    QQuickView *view = new QQuickView;
    appMain.initApplication(view);
    view->setSource(QStringLiteral("qrc:/main.qml"));
    view->show();

    return app.exec();
}

