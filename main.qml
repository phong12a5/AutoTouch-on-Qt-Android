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
            enable: true
        }
        ListElement {
            name: "Add + Confirm friends "
            value: AppEnums.HMI_CASE_ADD_CONFIRM_FRIEND
            enable: false
        }
        ListElement {
            name: "Add friends by UID"
            value: AppEnums.HMI_CASE_ADD_FRIEND_BY_UID
            enable: false
        }
        ListElement {
            name: "Follow page"
            value: AppEnums.HMI_CASE_FOLLOW_PAGE
            enable: false
        }
        ListElement {
            name: "Like page"
            value: AppEnums.HMI_CASE_LIKE_PAGE
            enable: false
        }
        ListElement {
            name: "Share profile"
            value: AppEnums.HMI_CASE_SHARE_PROFILE
            enable: false
        }
    }

    ListModel{
        id: listModel2

        ListElement {
            name: "Share page"
            value: AppEnums.HMI_CASE_SHARE_PAGE
            enable: false
        }
        ListElement {
            name: "Group Like"
            value: AppEnums.HMI_CASE_GROUP_LIKE
            enable: false
        }
        ListElement {
            name: "Group comment"
            value: AppEnums.HMI_CASE_GROUP_COMMENT
            enable: false
        }
        ListElement {
            name: "Up photo"
            value: AppEnums.HMI_CASE_UP_PHOTO
            enable: false
        }
        ListElement {
            name: "Set photo to Profile Pic"
            value: AppEnums.HMI_CASE_SET_PHOTO_TO_AVT
            enable: false
        }
        ListElement {
            name: "Update information"
            value: AppEnums.HMI_CASE_UPDATE_INFO
            enable: false
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
            boundsBehavior : Flickable.StopAtBounds
            delegate: Rectangle{
                id: delegate1
                width:  parent.width
                height: listview1.height / listModel1.count
                color: enabled?"#E6E6FA" : "grey"
                opacity: 0.7
                border.width: 2
                border.color: "black"
                radius: 5
                enabled: enable
                Text {
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                    text: name
                }
                MouseArea{
                    anchors.fill: parent
                    enabled: parent.enabled
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
            boundsBehavior : Flickable.StopAtBounds
            delegate: Rectangle{
                id: delegate2
                width:  parent.width
                height: listview2.height / listModel2.count
                color: enabled?"#E6E6FA" : "grey"
                opacity: 0.7
                border.width: 2
                border.color: "black"
                enabled: enable
                Text {
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                    text: name
                }
                MouseArea{
                    anchors.fill: parent
                    enabled: parent.enabled
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
