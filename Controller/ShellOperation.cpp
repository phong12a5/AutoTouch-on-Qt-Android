#include "ShellOperation.h"

ShellOperation::ShellOperation(QObject *parent) : QObject(parent)
{
    m_shellProcess = new QProcess(this);
}

#ifdef ANDROID_KIT
void ShellOperation::initShellCommand() const
{
    LOG;
//    m_shellProcess->startDetached("su");
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

void ShellOperation::callScrollEvent(QPoint point1, QPoint point2)
{
    LOG << QString("Scrolling from [%1,%2] to [%3,%4]")\
           .arg(point1.x()).arg(point1.y())\
           .arg(point2.x()).arg(point2.y());

    QStringList arg = QStringList()<< "-c"
                                   << "input"
                                   << "swipe"
                                   << QString::number(point1.x())\
                                   << QString::number(point1.y())\
                                   << QString::number(point2.x())\
                                   << QString::number(point2.y());
    LOG << "Args: " << arg;

    m_shellProcess->start("su",arg);
    m_shellProcess->waitForFinished(-1);
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

    m_shellProcess->start("su", QStringList()<< "-c" << "/system/bin/screencap" << "-p" << (path));
    m_shellProcess->waitForFinished(-1);
    return path;
}
#endif
