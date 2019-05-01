#ifndef MODEL_H
#define MODEL_H

#include <QGuiApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QScreen>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include <QQuickView>
#include <QTest>
#include <QProcess>
#include <QString>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    explicit Model(QQuickView *view = nullptr);

private:
    QTimer timer;
    QQuickView* m_view;
    int count;
signals:

public slots:
    void onTimeout();
};

#endif // MODEL_H
