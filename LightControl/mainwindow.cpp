#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenImageButton_clicked()
{
    QString inputImg = QFileDialog::getOpenFileName();
    Mat inputImage = imread(inputImg.toLatin1().data());
    namedWindow("Selected Image", WINDOW_NORMAL);
    imshow("Selected Image", inputImage);
}

void MainWindow::on_closeApp_clicked()
{
    close();
}
