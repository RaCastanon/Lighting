#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Include libraries
#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include "methods.h"
#include <QTimer>

//Definitions
#define SERIAL_COMM_ERROR "Error: could not open serial port"
#define CONNECTION_SUCESSFUL "Serial communication sucessful"
#define SERIAL_CLOSED "Serial port closed"
#define NAMED_WINDOW "Selected Image"
#define DEFAULT_TEST_POINT "180"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenImageButton_clicked();

    void on_closeApp_clicked();

    void on_openSerialPort_clicked();

    void on_closeSerialPort_clicked();

    void on_setTimer_clicked();

    void onTimeOut();

    void on_stopTimer_clicked();

    void on_openVideoCam_clicked();

    void on_grayScale_clicked();

    void on_middlePoints_clicked();

    void on_getIntensity_clicked();
    //Function Declarations
    void enableSetPoint(void);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
