#include "ImageProcessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject(parent)
{

}

#ifdef ANDROID_KIT
QList<QPoint> ImageProcessing::findImageOnImage(const QString &smallImagePath, const QString &largeImagePath)
{
    LOG << "smallImage: " << smallImagePath;
    LOG << "largeImage: " << largeImagePath;

    QList<QPoint> retVal;
    retVal.clear();

    cv::Mat _smallImage = cv::imread(smallImagePath.toUtf8().constData());
    cv::Mat _largeImage = cv::imread(largeImagePath.toUtf8().constData());

    //kiểm tra kích cỡ của ảnh input & template
    if (_smallImage.rows > _largeImage.rows || _smallImage.cols > _largeImage.cols)
    {
        LOG << "Mat template must be smaller than matInput";
        return retVal;
    }else if(_smallImage.rows <= 0 || _smallImage.cols <= 0 || _largeImage.rows <= 0 || _largeImage.cols <= 0){
        LOG << "Invalid Image";
    }

    cv::Mat result;
    int result_cols = _largeImage.cols - _smallImage.cols + 1;
    int result_rows = _largeImage.rows - _smallImage.rows + 1;
    result.create(result_rows, result_cols, CV_32FC1);

    //tìm mẫu
    cv::matchTemplate(_largeImage, _smallImage, result, CV_TM_CCORR_NORMED);


    double threshold = 0.99;
    cv::threshold(result, result, threshold, 1., CV_THRESH_TOZERO);
    double minval, maxval;
    //ngưỡng chính xác, giảm xuống thì sẽ tìm được nhiều đối tượng hơn nhưng sai số nhiều hơn

    cv::Point minloc, maxloc;
    cv::minMaxLoc(result, &minval, &maxval, &minloc, &maxloc);

    LOG << "minval: " << minval;
    LOG << "maxval: " << maxval;
    LOG << "threshold:" << threshold;

    if (maxval > threshold)
    {
        //vẽ hình chữ nhật lên đối tượng tìm được

        retVal << QPoint(maxloc.x + _smallImage.cols/2, maxloc.y + _smallImage.rows/2);
    }

    LOG << "Return values: " << retVal;
    return retVal;
}
#endif
