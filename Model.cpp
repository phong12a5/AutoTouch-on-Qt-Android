#include "Model.h"
#include <QWidgetList>
#include <QtWidgets/qwidget.h>
//#include <QAndroidJniObject>
#include <QWindow>

Model::Model(QObject *parent) : QObject(parent)
{

}

Model::Model(QQuickView *view)
{
    if(view){
        m_view = view;
    }
    qDebug() << "Created Model";
    timer.setInterval(3000);
    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()),this, SLOT(onTimeout()));
    timer.start();
}

void Model::onTimeout()
{
    qDebug() << "onTimeout";
    QImage image = m_view->grabWindow();
    qDebug() << "image: " << image.size();

    if(count <= 100){
        count++;
    }else{
        count = 0;
    }
    QProcess::startDetached("su", QStringList()<< "-c" << "/system/bin/screencap" << "-p" << QString("/storage/emulated/0/screen%1.png").arg(count));
}
