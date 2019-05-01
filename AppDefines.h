#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QTest>

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] >>"

#define WORKING_FOLDER  "AutoTouchApp"
#define WORKING_PATH    "/storage/emulated/0/AutoTouchApp/"
#define delay(milescond)    QTest::qSleep(milescond)

#endif // APPDEFINES_H
