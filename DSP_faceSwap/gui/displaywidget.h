#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QFileDialog>
#include <QThread>

#include <iostream>
#include <stdio.h>

#include "gui/imageviewer.h"
#include "camera.h"
#include "faceDetector.h"
#include "faceSwap.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT
    int status;
public:
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();

signals:
    void videoFileNameSignal(QString videoFileName);
    void facecascade_name_signal(QString filename);
    void runcam();

public slots:
    void openFileDialog();
    void change_face_cascade_filename(QString filename);
    void detailInfo();
    void checkCam();

private:
    FaceDetector* faceDector_;
    FaceDetector* tempDector_;
    Camera* camera_;
    Camera* rawcamera_;
    FaceSwap* faceswap_;
    QThread faceDetectThread_;
    QThread tempDetectThread_;
    QThread cameraThread_;
    QThread rawcameraThread_;
    QThread swapThread_;
    ImageViewer* image_viewer_;
    ImageViewer* raw_viewer_;
    ImageViewer* temp_viewer_;
    ImageViewer* cam_viewer;
};

#endif // DISPLAYWIDGET_H
