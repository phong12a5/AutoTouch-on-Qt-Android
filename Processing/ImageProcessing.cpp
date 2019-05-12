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

    LOG << "Small image: " << QImage(smallImagePath).size();
    LOG << "Large image: " << QImage(largeImagePath).size();

    cv::Mat _smallImage = QImage2Mat(QImage(smallImagePath));
    cv::Mat _largeImage = QImage2Mat(QImage(largeImagePath));

    //kiểm tra kích cỡ của ảnh input & template
    if (_smallImage.rows > _largeImage.rows || _smallImage.cols > _largeImage.cols)
    {
        LOG << "Mat template must be smaller than matInput";
        return retVal;
    }else if(_smallImage.rows <= 0 || _smallImage.cols <= 0 || _largeImage.rows <= 0 || _largeImage.cols <= 0){
        LOG << "Invalid Image";
        return retVal;
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
    double bestMaxval = 0;
    //ngưỡng chính xác, giảm xuống thì sẽ tìm được nhiều đối tượng hơn nhưng sai số nhiều hơn

    while (true)
    {
        cv::Point minloc, maxloc;
        cv::minMaxLoc(result, &minval, &maxval, &minloc, &maxloc);

        LOG << "minval: " << minval;
        LOG << "maxval: " << maxval;
        LOG << "threshold:" << threshold;

        if (maxval > threshold)
        {
            //vẽ hình chữ nhật lên đối tượng tìm được
            if(maxval > bestMaxval){
                bestMaxval = maxval;
                if(!retVal.isEmpty())
                    retVal.pop_back();

                retVal << QPoint(maxloc.x + _smallImage.cols/2, maxloc.y + _smallImage.rows/2);
            }
            cv::floodFill(result, maxloc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));

        }
        else
            break;
    }

    LOG << "Return values: " << retVal << " --- bestMaxVal: " << bestMaxval;
    return retVal;
}

cv::Mat ImageProcessing::QImage2Mat(const QImage &src)
{
    cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cvtColor(tmp, result,CV_BGR2RGB);
    return result;
}
#endif
