#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] >>"

#define WORKING_FOLDER  "AutoTouchApp"
#define WORKING_PATH    "/storage/emulated/0/AutoTouchApp/"

#endif // APPDEFINES_H
