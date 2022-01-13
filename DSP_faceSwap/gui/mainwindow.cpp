#include "gui/mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    face_cascade_ = new QAction("Select File", this);
    help_menu = new QAction("How To..", this);

    this->connect(help_menu, SIGNAL(triggered()), SLOT(messageBox_help()));

    auto cascade_file_menu = this->menuBar()->addMenu(tr("File"));
    auto cascade_file_menu2 = this->menuBar()->addMenu(tr("Help"));
    cascade_file_menu->addAction(face_cascade_);
    cascade_file_menu2->addAction(help_menu);

    DisplayWidget* display = new DisplayWidget(this);
    display->connect(this, SIGNAL(face_cascade_filename_signal(QString)),
                     SLOT(change_face_cascade_filename(QString)));

    setCentralWidget(display);
    this->connect(face_cascade_, SIGNAL(triggered()), display, SLOT(openFileDialog()));
}

void MainWindow::change_face_cascade()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                tr("HaarCascade Filename"));

    emit face_cascade_filename_signal(filename);

}

void MainWindow::messageBox_help(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("This is the Program to detect Face + Eyes.\nSee 'Show Details...' to learn how to operate it.");
    msgBox.setDetailedText("Step to operate with camera :\n1. Select the camera (Defult: 0 - Webcam)\n2. Tick the 'Use Camera Stream'"
"\n3. Click 'Start' to show the result\n\nStep to operate with file :\n1. Click 'OPEN'\n2. Select the image or video\n"
"3. Untick the 'Use Camera Stream'\n4. Click 'Start' to show the result\n\nIMPORTANT!!\nWhenever want to change setting, \nmake sure the 'Stop' button"
" is already clicked!\n(If there are problems, tick and untick the 'Use Camera Stream'!)");
    msgBox.exec();
}
MainWindow::~MainWindow()
{
}

