#ifndef APPENUMS_H
#define APPENUMS_H

#include <QObject>

class AppEnums : public QObject
{
    Q_OBJECT
    Q_ENUMS( HMI_REQUESTED_ACTIONS )

public:

    enum HMI_REQUESTED_ACTIONS: int
    {
        HMI_CASE_LIKE_NEW_FEED = 0,
        HMI_CASE_ADD_CONFIRM_FRIEND,
        HMI_CASE_ADD_FRIEND_BY_UID,
        HMI_CASE_FOLLOW_PAGE,
        HMI_CASE_LIKE_PAGE,
        HMI_CASE_SHARE_PROFILE,

        HMI_CASE_SHARE_PAGE,
        HMI_CASE_GROUP_LIKE,
        HMI_CASE_GROUP_COMMENT,
        HMI_CASE_UP_PHOTO,
        HMI_CASE_SET_PHOTO_TO_AVT,
        HMI_CASE_UPDATE_INFO,
        HMI_CASE_NONE_REQUEST
    };

    enum HMI_SCREEN_ID: int
    {
        HMI_START_UP_SCREEN = 0,
        HMI_NEW_FEED_SCREEN,
    };
};

#endif // APPENUMS_H
