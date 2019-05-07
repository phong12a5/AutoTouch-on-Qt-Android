import QtQuick 2.9
import QtQuick.Window 2.2
import AppEnums 1.0

Item {
    id: rootScreen
    visible: true
    width: APP_MODEL.widthDisplay
    height: APP_MODEL.heightDisplay

    ListModel{
        id: listModel1

        ListElement {
            name: "Like new feeds"
            value: AppEnums.HMI_CASE_LIKE_NEW_FEED
        }
        ListElement {
            name: "Add + Confirm friends "
            value: AppEnums.HMI_CASE_ADD_CONFIRM_FRIEND
        }
        ListElement {
            name: "Add friends by UID"
            value: AppEnums.HMI_CASE_ADD_FRIEND_BY_UID
        }
        ListElement {
            name: "Follow page"
            value: AppEnums.HMI_CASE_FOLLOW_PAGE
        }
        ListElement {
            name: "Like page"
            value: AppEnums.HMI_CASE_LIKE_PAGE
        }
        ListElement {
            name: "Share profile"
            value: AppEnums.HMI_CASE_SHARE_PROFILE
        }
    }

    ListModel{
        id: listModel2

        ListElement {
            name: "Share page"
            value: AppEnums.HMI_CASE_SHARE_PAGE
        }
        ListElement {
            name: "Group Like"
            value: AppEnums.HMI_CASE_GROUP_LIKE
        }
        ListElement {
            name: "Group comment"
            value: AppEnums.HMI_CASE_GROUP_COMMENT
        }
        ListElement {
            name: "Up photo"
            value: AppEnums.HMI_CASE_UP_PHOTO
        }
        ListElement {
            name: "Set photo to Profile Pic"
            value: AppEnums.HMI_CASE_SET_PHOTO_TO_AVT
        }
        ListElement {
            name: "Update information"
            value: AppEnums.HMI_CASE_UPDATE_INFO
        }
    }

    Item {
        id: leftItem
        width: parent.width/2
        height: parent.height
        ListView{
            id: listview1
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 20
            height: parent.height
            model: listModel1
            delegate: Rectangle{
                id: delegate1
                width:  parent.width
                height: listview1.height / listModel1.count
                color: "grey"
                opacity: 0.7
                border.width: 1
                border.color: "black"
                radius: 5
                Text {
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                    text: name
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        parent.opacity = 1
                    }
                    onPressAndHold: {
                        parent.opacity = 1
                    }
                    onReleased: {
                        parent.opacity = 0.7
                        timer1.start()
                    }
                    onCanceled: {
                        parent.opacity = 0.7
                    }
                }
                Timer{
                    id: timer1
                    interval: 1000
                    repeat: false
                    running: false
                    onTriggered: {
                        APP_MODEL.testFunc(value,name)
                    }
                }
            }
        }
    }

    Item {
        id: rightItem
        width: parent.width/2
        height: parent.height
        anchors.right: parent.right

        ListView{
            id: listview2
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 20
            height: parent.height
            model: listModel2
            delegate: Rectangle{
                id: delegate2
                width:  parent.width
                height: listview2.height / listModel2.count
                color: "grey"
                opacity: 0.7
                border.width: 1
                border.color: "black"
                Text {
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                    text: name
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        parent.opacity = 1
                    }
                    onPressAndHold: {
                        parent.opacity = 1
                    }
                    onReleased: {
                        parent.opacity = 0.7
                        timer2.start()
                    }
                    onCanceled: {
                        parent.opacity = 0.7
                    }
                }
                Timer{
                    id: timer2
                    interval: 1000
                    repeat: false
                    running: false
                    onTriggered: {
                        APP_MODEL.testFunc(value,name)
                    }
                }
            }
        }
    }

}
