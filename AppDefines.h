#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QTest>

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] >>"

#define WORKING_FOLDER  "AutoTouchApp"
#define WORKING_PATH    "/storage/emulated/0/AutoTouchApp/"
#define delay(milescond)    QTest::qSleep(milescond)

#define PROFILE_ICON    "/sdcard/DCIM/profileIcon.png"
#define LIKE_ICON       "/sdcard/DCIM/like.png"
#define FRIEND_ICON     "/sdcard/DCIM/friendIcon.png"
#define REQUEST_ICON    "/sdcard/DCIM/requestIcon.png"
#define SEARCH_ICON     "/sdcard/DCIM/searchIcon.png"
#define SUGGEST_ICON    "/sdcard/DCIM/suggestionsIcon.png"
#define CONFIRM_ICON    "/sdcard/DCIM/confirmIcon.png"
#define ADDFRIEND_ICON  "/sdcard/DCIM/addFriendIcon.png"

#endif // APPDEFINES_H
