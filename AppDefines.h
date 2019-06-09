#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QTest>
#include <QMap>
#include <AppEnums.h>

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] >>"

#define delay(milescond)    QTest::qSleep(milescond)

#define PROFILE_ICON    "assets:/images/profileIcon.png"

#define LIKE_ICON       "assets:/images/like.png"
#define LIKE_ICON_LITE  "assets:/images/likeIcon-Lite.png"

#define FRIEND_ICON     "assets:/images/friendIcon.png"

#define REQUEST_ICON    "assets:/images/requestIcon.png"

#define SEARCH_ICON     "assets:/images/searchIcon.png"

#define SUGGEST_ICON    "assets:/images/suggestionsIcon.png"

#define CONFIRM_ICON    "assets:/images/confirmIcon.png"

#define ADDFRIEND_ICON  "assets:/images/addFriendIcon.png"


#endif // APPDEFINES_H
