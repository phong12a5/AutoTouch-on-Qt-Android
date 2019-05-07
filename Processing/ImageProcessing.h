#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <stdio.h>
#include <QObject>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "AppDefines.h"
#include "QPoint"


class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(QObject *parent = nullptr);


public:
#ifdef ANDROID_KIT
    static QList<QPoint> findImageOnImage(const QString& smallImage, const QString& largeImage);
#endif
private:

signals:

public slots:
};

#endif // IMAGEPROCESSING_H
