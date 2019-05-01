#include "ShellOperation.h"

ShellOperation::ShellOperation(QObject *parent) : QObject(parent)
{

}

void ShellOperation::initWorkSpace() const
{
    if(!QDir(WORKING_PATH).exists()){
        LOG << "Creating Working folder: " << QString(WORKING_PATH);
        QDir().mkdir(QString(WORKING_PATH));
    }
    else{
        LOG << WORKING_PATH << " existed";
    }
}

void ShellOperation::openApplication(QString packageName, QString activityName) const
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

void ShellOperation::callTapEvent(const int x, const int y) const
{
    LOG << QString("Tapping at [%1,%2]").arg(x).arg(y);
    QStringList arg = QStringList()<< QString("-c")
                                   << QString("/system/bin/input")
                                   << QString("tap")
                                   << QString::number(x)
                                   << QString::number(y);
    LOG << "Args: " << arg;
    QProcess ::startDetached("su",arg );
}

void ShellOperation::makeDir(QString folderName) const
{
    if(!QDir(QString(WORKING_PATH) + folderName).exists()){
        LOG << "Creating folder: " << folderName;
        QDir().mkdir(QString(WORKING_PATH) + folderName);
    }else{
        LOG << QString(WORKING_PATH) + folderName << " existed";
    }
}

void ShellOperation::screenShot(QString path, QString fileName) const
{
    LOG << "Taking screen >> fileName: " << path + fileName;
    QProcess process;
    process.startDetached("su", QStringList()<< "-c" << "/system/bin/screencap" << "-p" << (path + fileName));
    QImage img(QString(path + fileName));
    if(img.isNull() || img.size().width() ==0 || img.size().height() == 0){
        LOG << "Capturing false >> Do again";
        process.startDetached("su", QStringList()<< "-c" << "/system/bin/screencap" << "-p" << (path + fileName));
    }
    delay(5000);
}

QString ShellOperation::screenShot(QString fileName) const
{
    LOG << "Taking screen >> fileName: " << fileName;
    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (path.isEmpty()){
        LOG << "Could't not save to " << path;
        return QString("");
    }
    path.append(QString("/%1").arg(fileName));
    LOG << "Path: " << path;

    QProcess::startDetached("su", QStringList()<< "-c" << "/system/bin/screencap" << "-p" << (path));
    delay(5000);
    return path;
}
