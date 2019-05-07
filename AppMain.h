#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>
#include "AppDefines.h"
#include <QQmlContext>
#include "Model.h"
#include <QQuickView>
#include "AppEnums.h"
#include "Controller/MainController.h"

class AppMain : public QObject
{
    Q_OBJECT
public:
    explicit AppMain(QObject *parent = nullptr);
    void initApplication(QQuickView* view);

private:
    void connectSignalSlot() const;

private:
    QQuickView* m_view;

signals:

public slots:
    void onRequestTestCase(int testCase);
};

#endif // APPMAIN_H
