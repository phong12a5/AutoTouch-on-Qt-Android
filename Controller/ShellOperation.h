#ifndef SHELLOPERATION_H
#define SHELLOPERATION_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QAndroidJniObject>
#include <QImage>
#include "AppDefines.h"

class ShellOperation : public QObject
{
    Q_OBJECT
public:
    explicit ShellOperation(QObject *parent = nullptr);
    void initWorkSpace(void) const;

public:
    void makeDir(QString folderName) const;
    void screenShot(QString path, QString fileName) const;
    void openApplication(QString packageName, QString activityName) const;
    void callTapEvent(const int x, const int y) const;
signals:

public slots:
};

#endif // SHELLOPERATION_H
