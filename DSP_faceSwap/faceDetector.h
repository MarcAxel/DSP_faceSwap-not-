#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QDir>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QResource>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class FaceDetector : public QObject
{
    Q_OBJECT
    QString facecascade_filename_;
    QString eyecascade_filename_;
    QString smilecascade_filename_;
    QBasicTimer timer_;
    cv::Mat frame_;
    cv::Mat tem_frame_;
    bool processAll_;
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;
    cv::CascadeClassifier smileCascade;

    void process(cv::Mat frame);
    void loadFiles(cv::String faceCascadeFilename, cv::String eyesCascadeFilename, cv::String smileCascaseFilename);
    void queue(const cv::Mat & frame);
    void timerEvent(QTimerEvent* ev);
    static void matDeleter(void* mat);

public:
    FaceDetector(QObject *parent=0) : QObject(parent), processAll_(true)
    {
        facecascade_filename_ = "resources/haarcascade_frontalface_alt2.xml";
        eyecascade_filename_ = "resources/haarcascade_eye_tree_eyeglasses.xml";
        smilecascade_filename_= "resources/haarcascade_eye_tree_eyeglasses.xml";
        loadFiles(facecascade_filename_.toStdString().c_str(),
                  eyecascade_filename_.toStdString().c_str(),
                  smilecascade_filename_.toStdString().c_str());
    }
    void setProcessAll(bool all);
    ~FaceDetector();

signals:
    void image_signal(const QImage&);

public slots:
    void processFrame(const cv::Mat& frame);
    void facecascade_filename(QString filename);
private:
    void convert_template(const cv::Mat& frame);
};

#endif // FACEDETECTOR_H
