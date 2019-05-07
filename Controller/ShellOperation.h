#ifndef SHELLOPERATION_H
#define SHELLOPERATION_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QImage>
#include "AppDefines.h"
#include <QStandardPaths>



class ShellOperation : public QObject
{
    Q_OBJECT
public:
    explicit ShellOperation(QObject *parent = nullptr);

public:

#ifdef ANDROID_KIT
    void initShellCommand() const;
    void screenShot(QString path, QString fileName) const;
    QString screenShot(QString fileName) const;
    void callTapEvent(const int x, const int y) const;
    void callScrollEvent(QPoint point1, QPoint point2);
#endif

private:
    QProcess* m_shellProcess;
signals:

public slots:
};

#endif // SHELLOPERATION_H
