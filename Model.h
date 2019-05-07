#ifndef MODEL_H
#define MODEL_H

#include <QGuiApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QScreen>
#include <QQuickView>
#include <QTest>
#include <QString>
#include "AppDefines.h"

class Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int widthDisplay READ widthDisplay WRITE setWidthDisplay NOTIFY widthDisplayChanged)
    Q_PROPERTY(int heightDisplay READ heightDisplay WRITE setHeightDisplay NOTIFY heightDisplayChanged)

public:
    static Model* instance();

    Q_INVOKABLE void testFunc(int caseIndex, QString extraData);

public:
    int widthDisplay() const;
    void setWidthDisplay(const int width);

    int heightDisplay() const;
    void setHeightDisplay(const int height);

private:
    explicit Model(QObject *parent = nullptr);

private:
    QQuickView* m_view;

    int m_widthDisplay;
    int m_heightDisplay;
private:
    static Model* m_instance;

signals:
    void widthDisplayChanged();
    void heightDisplayChanged();

    void requestTestCase(int caseIndex);
public slots:
};

#endif // MODEL_H
