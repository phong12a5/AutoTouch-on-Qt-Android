#include "JavaCommunication.h"

JavaCommunication::JavaCommunication(QObject *parent) : QObject(parent)
{
    LOG << this->getSimCardSerialNo();
}

void JavaCommunication::openApplication(QString packageName, QString activityName) const
{
    LOG << "Openning " << packageName + "/" + activityName;
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if ( activity.isValid() )
    {
        // Equivalent to Jave code: 'Intent intent = new Intent();'
        QAndroidJniObject intent("android/content/Intent","()V");
        if ( intent.isValid() )
        {
            QAndroidJniObject param1 = QAndroidJniObject::fromString(packageName);
            QAndroidJniObject param2 = QAndroidJniObject::fromString(activityName);

            if ( param1.isValid() && param2.isValid() )
            {
                // Equivalent to Jave code: 'intent.setClassName(packageName, activityName);'
                intent.callObjectMethod("setClassName","(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",param1.object<jobject>(),param2.object<jobject>());

                // Equivalent to Jave code: 'startActivity(intent);'
                activity.callMethod<void>("startActivity","(Landroid/content/Intent;)V",intent.object<jobject>());
            }
        }
    }
}

void JavaCommunication::backToAppMain() const
{
    LOG;
    this->openApplication("org.qtproject.example.AutoTouchQtAndroid","org.qtproject.qt5.android.bindings.QtActivity");
}

QString JavaCommunication::getDeviceIMEI()
{
    QAndroidJniEnvironment env;
    jclass contextClass = env->FindClass("android/content/Context");
    jfieldID fieldId = env->GetStaticFieldID(contextClass, "TELEPHONY_SERVICE", "Ljava/lang/String;");
    jstring telephonyManagerType = (jstring) env->GetStaticObjectField(contextClass, fieldId);

    jclass telephonyManagerClass = env->FindClass("android/telephony/TelephonyManager");
    jmethodID methodId = env->GetMethodID(contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

    QAndroidJniObject qtActivityObj = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",  "activity", "()Landroid/app/Activity;");
    jobject telephonyManager = env->CallObjectMethod(qtActivityObj.object<jobject>(), methodId, telephonyManagerType);

    methodId = env->GetMethodID(telephonyManagerClass, "getDeviceId", "()Ljava/lang/String;");
    jstring jstr = (jstring) env->CallObjectMethod(telephonyManager, methodId);

    return QAndroidJniObject::fromLocalRef(jstr).toString();
}

QString JavaCommunication::getDeiceIMSI()
{
    QAndroidJniEnvironment env;
    jclass contextClass = env->FindClass("android/content/Context");
    jfieldID fieldId = env->GetStaticFieldID(contextClass, "TELEPHONY_SERVICE", "Ljava/lang/String;");
    jstring telephonyManagerType = (jstring) env->GetStaticObjectField(contextClass, fieldId);

    jclass telephonyManagerClass = env->FindClass("android/telephony/TelephonyManager");
    jmethodID methodId = env->GetMethodID(contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

    QAndroidJniObject qtActivityObj = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",  "activity", "()Landroid/app/Activity;");
    jobject telephonyManager = env->CallObjectMethod(qtActivityObj.object<jobject>(), methodId, telephonyManagerType);

    methodId = env->GetMethodID(telephonyManagerClass, "getSubscriberId", "()Ljava/lang/String;");
    jstring jstr = (jstring) env->CallObjectMethod(telephonyManager, methodId);

    return QAndroidJniObject::fromLocalRef(jstr).toString();
}

QString JavaCommunication::getDeviceModel()
{
    QAndroidJniEnvironment env;
    jclass contextClass = env->FindClass("android/os/Build");
    jfieldID fieldId = env->GetStaticFieldID(contextClass, "MODEL", "Ljava/lang/String;");
    jstring model = (jstring) env->GetStaticObjectField(contextClass, fieldId);
    return QAndroidJniObject::fromLocalRef(model).toString();;
}

QString JavaCommunication::getAndroidVersion()
{
#ifdef PREFER_QT
    return QSysInfo::productVersion();
#else
    QAndroidJniEnvironment env;
    jclass contextClass = env->FindClass("android/os/Build$VERSION");
    jfieldID fieldId = env->GetStaticFieldID(contextClass, "RELEASE", "Ljava/lang/String;");
    jstring osVersion = (jstring) env->GetStaticObjectField(contextClass, fieldId);
    return QAndroidJniObject::fromLocalRef(osVersion).toString();
#endif
}

QString JavaCommunication::getAndroidID()
{
    QAndroidJniObject androidIdField = QAndroidJniObject::getStaticObjectField("android/provider/Settings$Secure", "ANDROID_ID", "Ljava/lang/String;");

    QAndroidJniObject qtActivityObj = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",  "activity", "()Landroid/app/Activity;");
    QAndroidJniObject contentResolver = qtActivityObj.callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");

    QString androidID = QAndroidJniObject::callStaticObjectMethod("android/provider/Settings$Secure","getString", "(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;",contentResolver.object<jobject>(),androidIdField.object<jobject>()).toString();

    return androidID;
}

QString JavaCommunication::getSimCardSerialNo()
{
   /*TelephonyManager telemamanger = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
    String getSimSerialNumber = telemamanger.getSimSerialNumber();*/

    QAndroidJniEnvironment env;
    jclass contextClass = env->FindClass("android/content/Context");
    jfieldID fieldId = env->GetStaticFieldID(contextClass, "TELEPHONY_SERVICE", "Ljava/lang/String;");
    jstring telephonyManagerType = (jstring) env->GetStaticObjectField(contextClass, fieldId);

    jclass telephonyManagerClass = env->FindClass("android/telephony/TelephonyManager");
    jmethodID methodId = env->GetMethodID(contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

    QAndroidJniObject qtActivityObj = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",  "activity", "()Landroid/app/Activity;");
    jobject telephonyManager = env->CallObjectMethod(qtActivityObj.object<jobject>(), methodId, telephonyManagerType);

    methodId = env->GetMethodID(telephonyManagerClass, "getSimSerialNumber", "()Ljava/lang/String;");
    jstring jstr = (jstring) env->CallObjectMethod(telephonyManager, methodId);

    return QAndroidJniObject::fromLocalRef(jstr).toString();;
}

QString JavaCommunication::getSimNumber()
{
    /*TelephonyManager telemamanger = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
     String getSimSerialNumber = telemamanger.getSimSerialNumber();*/

     QAndroidJniEnvironment env;
     jclass contextClass = env->FindClass("android/content/Context");
     jfieldID fieldId = env->GetStaticFieldID(contextClass, "TELEPHONY_SERVICE", "Ljava/lang/String;");
     jstring telephonyManagerType = (jstring) env->GetStaticObjectField(contextClass, fieldId);

     jclass telephonyManagerClass = env->FindClass("android/telephony/TelephonyManager");
     jmethodID methodId = env->GetMethodID(contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

     QAndroidJniObject qtActivityObj = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",  "activity", "()Landroid/app/Activity;");
     jobject telephonyManager = env->CallObjectMethod(qtActivityObj.object<jobject>(), methodId, telephonyManagerType);

     methodId = env->GetMethodID(telephonyManagerClass, "getLine1Number", "()Ljava/lang/String;");
     jstring jstrNumber = (jstring) env->CallObjectMethod(telephonyManager, methodId);

     return QAndroidJniObject::fromLocalRef(jstrNumber).toString();
}


