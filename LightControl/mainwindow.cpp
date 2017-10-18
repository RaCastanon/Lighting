#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

//Global variables
QSerialPort serial;
QTimer *timerOne;
Mat inputVideo;
Mat inputImage;
bool serialFlag = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Configure timer one
    timerOne = new QTimer(this);
    connect(timerOne, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    ui->setupUi(this);

    //Disable not required buttons
    ui->grayScale->setDisabled(true);
    ui->middlePoints->setDisabled(true);
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
    inputImage = imread(inputImg.toLatin1().data());
    //Verify if there is an image
    if(!(inputImage.empty()))
    {
        //Show image
        namedWindow(NAMED_WINDOW, WINDOW_NORMAL);
        imshow(NAMED_WINDOW, inputImage);
        //Enable grayscale button
        ui->grayScale->setEnabled(true);
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

/* Function name: on_openVideoCam_clicked()
 * Developer:     Raul Castañon
 * Details:       Open video camera and show continuosly
 */
void MainWindow::on_openVideoCam_clicked()
{
    VideoCapture videoCam;
    videoCam.open(0);
    if(videoCam.isOpened())
    {
        do
        {
            videoCam >> inputVideo;
            imshow("video", inputVideo);
            waitKey(100);
            if(waitKey(30) > 0)
            {
                videoCam.release();
                destroyWindow("video");
                break;
            }
        }while(true);
    }
}

/* Function name: on_grayScale_clicked()
 * Developer:     Raul Castañon
 * Details:       Convert image in grayscale format
 */
void MainWindow::on_grayScale_clicked()
{
    if(!(inputImage.empty()))
    {
        //Set image in grayscale format
        cvtColor(inputImage, inputImage, CV_RGB2GRAY);
        //Show result in same window
        imshow(NAMED_WINDOW, inputImage);
        ui->middlePoints->setEnabled(true);
    }
}

/* Function name: on_middlePoints_clicked()
 * Developer:     Raul Castañon
 * Details:       Get the middle points to process the calculation of intensity
 */
void MainWindow::on_middlePoints_clicked()
{
    //Call function to get middle points
    setMiddlePoints(inputImage.cols, inputImage.rows);
    //Put value on labels
    ui->P_one_cols->setText(QString::number(middlePoints[0][0]));
    ui->P_one_rows->setText(QString::number(middlePoints[0][1]));
    ui->P_two_cols->setText(QString::number(middlePoints[1][0]));
    ui->P_two_rows->setText(QString::number(middlePoints[1][1]));
    ui->P_three_cols->setText(QString::number(middlePoints[2][0]));
    ui->P_three_rows->setText(QString::number(middlePoints[2][1]));
    ui->P_four_cols->setText(QString::number(middlePoints[3][0]));
    ui->P_four_rows->setText(QString::number(middlePoints[3][1]));
    ui->P_five_cols->setText(QString::number(middlePoints[4][0]));
    ui->P_five_rows->setText(QString::number(middlePoints[4][1]));
}

/* Function name: on_getIntensity_clicked()
 * Developer:     Raul Castañon
 * Details:       Get intensity levels from the image
 */
void MainWindow::on_getIntensity_clicked()
{

}
