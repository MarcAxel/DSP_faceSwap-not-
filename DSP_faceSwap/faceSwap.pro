#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T18:15:50
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = opencv
TEMPLATE = app
DESTDIR = $$PWD
INCLUDEPATH += /usr/include/opencv \
                ./gui \
                .
#    ./resources

#QT_CONFIG -= no-pkg-config
#CONFIG += link_pkgconfig
#PKGCONFIG += opencv

win32 {
    INCLUDEPATH += "D:\\OpenCV2.4.9\\build\\include" \

    CONFIG(debug,debug|release) {
        LIBS += -L"D:\\OpenCV2.4.9\\build\\x64\\vc12\\lib" \
            -lopencv_core249d \
            -lopencv_highgui249d \
            -lopencv_imgproc249d \
#            -lopencv_features2d249d \
#            -lopencv_calib3d249d
    }

    CONFIG(release,debug|release) {
        DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
        LIBS += -L"D:\\OpenCV2.4.9\\build\\x64\\vc12\\lib" \
            -lopencv_core249 \
            -lopencv_highgui249 \
            -lopencv_imgproc249 \
#            -lopencv_features2d249 \
#            -lopencv_calib3d249
    }
}


unix {
#    QT_CONFIG -= no-pkg-config
#    CONFIG += link_pkgconfig
#    PKGCONFIG += opencv
    QMAKE_CXXFLAGS += -std=c++1y
    QMAKE_CXXFLAGS += -Wall
    # OpenCv Configuration opencv-4.2.0
    INCLUDEPATH += "/usr/include/opencv4/opencv2"
    INCLUDEPATH += "/usr/include/opencv4"
    LIBS += -L~/usr/lib/x86_64-linux-gnu \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_objdetect \
    -lopencv_imgcodecs \
    -lopencv_features2d \
    -lopencv_calib3d \
    -lopencv_video\
    -lopencv_videoio
}
#LIBS += -L/lib -I/usr/include/opencv -lopencv_calib3d -lopencv_core -lopencv_cudaarithm -lopencv_cudabgsegm -lopencv_cudacodec -lopencv_cudafeatures2d -lopencv_cudafilters -lopencv_cudaimgproc -lopencv_cudaobjdetect -lopencv_cudaoptflow -lopencv_cudastereo -lopencv_cudawarping -lopencv_cudev -lopencv_features2d -lopencv_flann -lopencv_hal -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videoio -lopencv_videostab

SOURCES += main.cpp \
    MatToQImage.cpp \
    faceSwap.cpp \
    gui/mainwindow.cpp \
    camera.cpp \
    gui/displaywidget.cpp \
    faceDetector.cpp \
    gui/imageviewer.cpp

HEADERS += gui/mainwindow.h \
    MatToQImage.h \
    camera.h \
    faceSwap.h \
    gui/displaywidget.h \
    faceDetector.h \
    gui/imageviewer.h
