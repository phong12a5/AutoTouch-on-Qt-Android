import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    visible: true
    width: 1080
    height: 1920
//    title: qsTr("Hello World")

    Rectangle{
        anchors.centerIn: parent
        width: 100
        height: 50
        border.width: 2
        border.color: "black"
        color: "gray"
        Text {
            text: qsTr("Start")
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 30
        }
    }

}
