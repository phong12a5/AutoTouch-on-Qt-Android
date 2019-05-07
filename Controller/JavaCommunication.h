#ifndef JAVACOMMUNICATION_H
#define JAVACOMMUNICATION_H

#include <QObject>
#include "AppDefines.h"

#ifdef ANDROID_KIT
#include <QAndroidJniObject>
#endif

class JavaCommunication : public QObject
{
    Q_OBJECT
public:
    explicit JavaCommunication(QObject *parent = nullptr);

    void openApplication(QString packageName, QString activityName) const;
    void backToAppMain() const;
signals:

public slots:
};

#endif // JAVACOMMUNICATION_H
