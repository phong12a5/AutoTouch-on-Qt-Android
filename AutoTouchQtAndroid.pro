QT += quick
QT += testlib
QT += widgets


CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Model.h \
    Controller/ShellOperation.h \
    AppDefines.h \
    Processing/ImageProcessing.h \
    AppMain.h \
    AppEnums.h \
    Controller/MainController.h \
    Controller/JavaCommunication.h

SOURCES += \
        main.cpp \
    Model.cpp \
    Controller/ShellOperation.cpp \
    Processing/ImageProcessing.cpp \
    AppMain.cpp \
    Controller/MainController.cpp \
    Controller/JavaCommunication.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android-sources/AndroidManifest.xml

INCLUDEPATH += "$$_PRO_FILE_PWD_/../OpenCV-android-sdk/sdk/native/jni/include"

android {

    DEFINES += ANDROID_KIT

    QT += androidextras

    LIBS += \
        -L"$$_PRO_FILE_PWD_/../OpenCV-android-sdk/sdk/native/3rdparty/libs/armeabi-v7a"\
        -L"$$_PRO_FILE_PWD_/../OpenCV-android-sdk/sdk/native/libs/armeabi-v7a"\
        -llibtiff\
        -llibjpeg\
        -llibjasper\
        -llibpng\
        -lIlmImf\
        -ltbb\
        -lopencv_core\
        -lopencv_androidcamera\
        -lopencv_flann\
        -lopencv_imgproc\
        -lopencv_highgui\
        -lopencv_features2d\
        -lopencv_calib3d\
        -lopencv_ml\
        -lopencv_objdetect\
        -lopencv_video\
        -lopencv_contrib\
        -lopencv_photo\
        -lopencv_java\
        -lopencv_legacy\
        -lopencv_ocl\
        -lopencv_stitching\
        -lopencv_superres\
        -lopencv_ts\
        -lopencv_videostab

    ANDROID_PACKAGE_SOURCE_DIR=$$_PRO_FILE_PWD_/android-sources
}
