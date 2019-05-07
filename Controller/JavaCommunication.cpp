#include "JavaCommunication.h"

JavaCommunication::JavaCommunication(QObject *parent) : QObject(parent)
{

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
