#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QScreen>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include "Model.h"
#include <QQuickView>
#include <QProcess>
#include <opencv2/core/core.hpp>
//#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include "Controller/ShellOperation.h"
#include <QTest>
#include <QStandardPaths>
#include <QApplication>
#include <QRect>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

int result_x = -1;
int result_y = -1;

/// Function Headers
void MatchingMethod( int, void* );


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setGeometry(0,0,1080,1920);
    view->setSource(QStringLiteral("qrc:/main.qml"));
    view->show();
    LOG << "screen: " << view->size();
    QImage image = view->grabWindow();
    LOG << "screenShot: " << image.size();

    QRect rect = qApp->primaryScreen()->geometry();

    LOG << "rect: "<< rect; ;

    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

    if (path.isEmpty())
        return 0;
    LOG << "Path: " << path;
    path.append("/Screen.png");
    image.save(path);

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;

//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    ShellOperation shellOperation;
//    shellOperation.initWorkSpace();
//    shellOperation.makeDir("ScreenShot/");
//    shellOperation.openApplication("com.facebook.katana","com.facebook.katana.LoginActivity");
//    QTest::qSleep(5000);
//    shellOperation.screenShot(WORKING_PATH,"ScreenShot/Image1.png");

//    QTest::qSleep(2000);
//    templ = imread( "/sdcard/DCIM/like.png", 1 );

//    QImage image("/storage/emulated/0/AutoTouchApp/ScreenShot/Image1.png");
//    LOG << "image.size: " << image.size();
//    img = imread("/storage/emulated/0/AutoTouchApp/ScreenShot/Image1.png", 1 );

//    LOG << "Image exist: " << QFile("/storage/emulated/0/AutoTouchApp/ScreenShot/Image1.png").exists();
//    LOG << "img: " << img.cols << " " << img.rows;

//    QImage imageA("/storage/emulated/0/AutoTouchApp/ScreenShot/Image1.png");
//    LOG << "image.size: " << imageA.size();
////    /// Create windows
//////    namedWindow( image_window, CV_WINDOW_AUTOSIZE );
//////    namedWindow( result_window, CV_WINDOW_AUTOSIZE );

////    /// Create Trackbar
//////    char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//////    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

//    if(img.rows > 0 && img.cols > 0){
//            MatchingMethod( 0, 0 );

//            QTest::qSleep(2000);
//            shellOperation.callTapEvent(result_x, result_y);
//    }

//    Model model(view);

    return app.exec();
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_rows, result_cols, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  result_x = matchLoc.x + templ.cols/2;
  result_y = matchLoc.y + templ.rows/2;

  qDebug() << "result_x: " << result_x;
  qDebug() << "result_y: " << result_y;

  /// Show me what you got
  rectangle( img, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

//  imshow( image_window, img_display );
//  imshow( result_window, result );

  return;
}
