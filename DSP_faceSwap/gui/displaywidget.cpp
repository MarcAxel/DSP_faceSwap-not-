#include "gui/displaywidget.h"
#include <QMessageBox>

bool flagSel;
DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
    QStringList cameraOptions;
    cameraOptions << "0" << "1" << "2" << "3" << "4" << "5" << "6";
    QComboBox* cameraComboBox = new QComboBox;
    cameraComboBox->addItems(cameraOptions);

    QHBoxLayout* horizontalLayout = new QHBoxLayout();
    QPushButton *runButton = new QPushButton("Start/Stop", this);
    //QPushButton *fileSelector = new QPushButton("SELECT XML");
    QPushButton *openFile = new QPushButton("Template");
    QPushButton *detailBut = new QPushButton("Detail");

    horizontalLayout->addWidget(cameraComboBox);
    //horizontalLayout->addWidget(fileSelector);
    horizontalLayout->addWidget(openFile);
    horizontalLayout->addWidget(runButton);
    horizontalLayout->addWidget(detailBut);

    QVBoxLayout *layout = new QVBoxLayout;
    image_viewer_ = new ImageViewer(this);
    raw_viewer_ = new ImageViewer(this);
    temp_viewer_ = new ImageViewer(this);
    cam_viewer = new ImageViewer(this);
//    QRadioButton *sourceSelector = new QRadioButton("Use Camera Stream",
//		    				    this);

//    sourceSelector->setDown(true);

    QHBoxLayout* horizontalLayout2 = new QHBoxLayout();
    horizontalLayout2->addWidget(cam_viewer);
    horizontalLayout2->addWidget(image_viewer_);
    horizontalLayout2->addWidget(raw_viewer_);
//    horizontalLayout2->addWidget(temp_viewer_);
    QHBoxLayout* horiLay = new QHBoxLayout();
    horiLay->addWidget(temp_viewer_);
    horizontalLayout2->addLayout(horiLay);

    layout->addLayout(horizontalLayout2);
    layout->addLayout(horizontalLayout);
//    layout->addWidget(sourceSelector);

    setLayout(layout);

    rawcamera_ = new Camera();
    camera_ = new Camera();
    faceDector_ = new FaceDetector();
    faceswap_ = new FaceSwap();
    tempDector_ = new FaceDetector();

    //faceDector_->setProcessAll(true);

    faceDetectThread_.start();
    cameraThread_.start();
    rawcameraThread_.start();
    swapThread_.start();
    tempDetectThread_.start();

    camera_->moveToThread(&cameraThread_);
    rawcamera_->moveToThread(&rawcameraThread_);
    faceDector_->moveToThread(&faceDetectThread_);
    tempDector_->moveToThread(&tempDetectThread_);
    faceswap_->moveToThread(&swapThread_);

    // TODO: Add in slot to turn off camera_, or something
    if(status == 1){
    image_viewer_->connect(faceDector_,
                           SIGNAL(image_signal(QImage)),
                           SLOT(set_image(QImage)));

    temp_viewer_->connect(tempDector_,
                           SIGNAL(image_signal(QImage)),
                           SLOT(set_image(QImage)));

    raw_viewer_->connect(faceswap_,
                           SIGNAL(image_signal(QImage)),
                           SLOT(set_image(QImage)));}
    else{
    cam_viewer->connect(camera_,
                        SIGNAL(test(QImage)),
                        SLOT(set_image(QImage)));}
//    QObject::connect(rawcamera_, SIGNAL(test(QImage)), this, SLOT(image_converting(QImage)));
//    faceDector_->connect(rawcamera_, SIGNAL(matReady(cv::Mat)),
//                 SLOT(convert_template(cv::Mat)));

    faceDector_->connect(camera_, SIGNAL(matReady(cv::Mat)),
                 SLOT(processFrame(cv::Mat)));
    tempDector_->connect(rawcamera_, SIGNAL(matReady(cv::Mat)),
                 SLOT(processFrame(cv::Mat)));
    faceswap_->connect(rawcamera_, SIGNAL(test(QImage)),
                       SLOT(running(QImage)));

    QObject::connect(cameraComboBox, SIGNAL(currentIndexChanged(int)),
                     camera_, SLOT(cameraIndexSlot(int)));

    //QObject::connect(fileSelector, SIGNAL(clicked()),
     //                this,	SLOT(openFileDialog()));

    QObject::connect(openFile, SIGNAL(clicked()),
                     this,	SLOT(openFileDialog()));

    QObject::connect(detailBut, SIGNAL(clicked()),
                     this,	SLOT(detailInfo()));

//    QObject::connect(sourceSelector, SIGNAL(toggled(bool)),
//                     camera_, SLOT(usingVideoCameraSlot(bool)));

    QObject::connect(this, SIGNAL(videoFileNameSignal(QString)), rawcamera_, SLOT(videoFileNameSlot(QString)));

    QObject::connect(runButton, SIGNAL(clicked()), camera_, SLOT(runSlot()));
    QObject::connect(runButton, SIGNAL(true), camera_, SLOT(usingVideoCameraSlot(bool)));
    QObject::connect(runButton, SIGNAL(clicked()), rawcamera_, SLOT(runSlot()));

    faceDector_->connect(this, SIGNAL(facecascade_name_signal(QString)),
                     SLOT(facecascade_filename(QString)));


}

DisplayWidget::~DisplayWidget()
{
    faceDector_->~FaceDetector();
    camera_->~Camera();
    rawcamera_->~Camera();
    faceDetectThread_.quit();
    cameraThread_.quit();
    rawcameraThread_.quit();
    faceDetectThread_.wait();
    cameraThread_.wait();
    rawcameraThread_.wait();
}

void DisplayWidget::change_face_cascade_filename(QString filename)
{
    emit facecascade_name_signal(filename);
}

void DisplayWidget::openFileDialog()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Video"));
    emit videoFileNameSignal(filename);
    status = 1;
}

void DisplayWidget::detailInfo(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("This is the Program to detect Face + Eyes.\nSee 'Show Details...' to learn how to operate it.");
    msgBox.setDetailedText("Step to operate with camera :\n1. Select the camera (Defult: 0 - Webcam)\n2. Tick the 'Use Camera Stream'"
"\n3. Click 'Start' to show the result\n\nStep to operate with file :\n1. Click 'OPEN'\n2. Select the image or video\n"
"3. Untick the 'Use Camera Stream'\n4. Click 'Start' to show the result\n\nIMPORTANT!!\nWhenever want to change setting, \nmake sure the 'Stop' button"
" is already clicked!\n(If there are problems, tick and untick the 'Use Camera Stream'!)");
    msgBox.exec();
}
void DisplayWidget::checkCam(){
;
}
