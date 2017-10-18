#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

//Global variables
QSerialPort serial;
QTimer *timerOne;
bool serialFlag = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Configure timer one
    timerOne = new QTimer(this);
    connect(timerOne, SIGNAL(timeout()), this, SLOT(onTimeOut()));

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
    //Check if we need to stop timer
    if(timerOne->isActive())
    {
        MainWindow::on_closeSerialPort_clicked();
    }
    //Check if we need to close SerialPort
    if(true == serialFlag)
    {
        MainWindow::on_closeSerialPort_clicked();
    }
    close();
}

/* Function name: openSerialPort()
 * Developer:     Raul Castañon
 * Details:       Configure and open the serialPort
 */
void MainWindow::on_openSerialPort_clicked()
{
    if(false == serialFlag)
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
            serialFlag = true;
        }
        //if not send error message
        else
        {
            qDebug(SERIAL_COMM_ERROR);
        }
    }
    else
    {
        qDebug("Port already open");
    }
}

/* Function name: closeSerialPort()
 * Developer:     Raul Castañon
 * Details:       Close serial port
 */
void MainWindow::on_closeSerialPort_clicked()
{
    serial.close();
    serialFlag = false;
    qDebug(SERIAL_CLOSED);
}

/* Function name: setTimer()
 * Developer:     Raul Castañon
 * Details:       Start timer one
 */
void MainWindow::on_setTimer_clicked()
{
    //Verify if timer one is not active
    if(!(timerOne->isActive()))
    {
        timerOne->start(1000);
    }
    else
    {
        qDebug("Timer one is enabled");
    }
}

/* Function name: stopTimer()
 * Developer:     Raul Castañon
 * Details:       Stop timer one
 */
void MainWindow::on_stopTimer_clicked()
{
    //Verify timer one is active
    if(timerOne->isActive())
    {
        timerOne->stop();
    }
    else
    {
        qDebug("Timer one was not active");
    }
}

/* Function name: onTimeOut()
 * Developer:     Raul Castañon
 * Details:       Linker to the timeOut signal from timerOne
 */
void MainWindow::onTimeOut()
{
    setProcess();
}
