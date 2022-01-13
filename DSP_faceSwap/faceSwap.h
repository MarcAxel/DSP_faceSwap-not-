#ifndef FACESWAP_H
#define FACESWAP_H

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QDir>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QResource>
#include "MatToQImage.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class FaceSwap : public QObject
{   Q_OBJECT
    QString facecascade_filename_;
    QString eyecascade_filename_;
    QString smilecascade_filename_;
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;
    cv::CascadeClassifier smileCascade;
    void loadFiles(cv::String faceCascadeFilename, cv::String eyesCascadeFilename, cv::String smileCascaseFilename);
    QImage frame_oper;

public:
    FaceSwap(QObject *parent=0) : QObject(parent)
    {
        facecascade_filename_ = "resources/haarcascade_frontalface_alt2.xml";
        eyecascade_filename_ = "resources/haarcascade_eye_tree_eyeglasses.xml";
        smilecascade_filename_= "resources/haarcascade_eye_tree_eyeglasses.xml";
        loadFiles(facecascade_filename_.toStdString().c_str(),
                  eyecascade_filename_.toStdString().c_str(),
                  smilecascade_filename_.toStdString().c_str());
    }
    ~FaceSwap();

signals:
    void image_signal(const QImage&);

public slots:
    void buff(const QImage&);
    void cameraIndexload(int index);
    void running(const QImage&);

private:
    VideoCapture cap;
    Mat capture, smooth, edge, hline, hline2;
    int cameraIndex;
};

#endif // FACESWAP_H
