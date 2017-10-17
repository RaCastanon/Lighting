#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Include libraries
#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QDebug>
#include <QtSerialPort/QSerialPort>

//Definitions
#define SERIAL_COMM_ERROR "Error: could not open serial port"
#define CONNECTION_SUCESSFUL "Serial communication sucessful"
#define SERIAL_CLOSED "Serial port closed"

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
