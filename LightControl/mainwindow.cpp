#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

//Global variables
QSerialPort serial;

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

/* Function name: OpenImageButton()
 * Developer:     Raul Castañon
 * Details:       Function used to open and show an image
 */
void MainWindow::on_OpenImageButton_clicked()
{
    QString inputImg = QFileDialog::getOpenFileName();
    Mat inputImage = imread(inputImg.toLatin1().data());
    //Verify if there is an image
    if(!(inputImage.empty()))
    {
        //Show image
        namedWindow("Selected Image", WINDOW_NORMAL);
        imshow("Selected Image", inputImage);
    }
}

/* Function name: closeApp()
 * Developer:     Raul Castañon
 * Details:       Close application
 */
void MainWindow::on_closeApp_clicked()
{
    close();
}

/* Function name: openSerialPort()
 * Developer:     Raul Castañon
 * Details:       Configure and open the serialPort
 */
void MainWindow::on_openSerialPort_clicked()
{
    //Set configuration conditions
    serial.setPortName("COM10");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    //Check if the port has been open
    if(serial.open(QIODevice::ReadWrite))
    {
        qDebug(CONNECTION_SUCESSFUL);
        serial.write("95\n");
    }
    //if not send error message
    else
    {
        qDebug(SERIAL_COMM_ERROR);
    }
}

/* Function name: closeSerialPort()
 * Developer:     Raul Castañon
 * Details:       Close serial port
 */
void MainWindow::on_closeSerialPort_clicked()
{
    serial.close();
    qDebug(SERIAL_CLOSED);
}
