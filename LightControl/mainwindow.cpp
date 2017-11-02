#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

//Global variables
QSerialPort serial;
QTimer *timerOne;
Mat inputVideo;
Mat inputImage;
unsigned int intensityLevel = 0;
unsigned int setPointFromUI = 0;
bool serialFlag = false;
signed int error_p = 0;

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
    ui->getIntensity->setDisabled(true);
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
        timerOne->start(2000);
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
    VideoCapture videoCam;
    videoCam.open(0);
    if(videoCam.isOpened())
    {
        videoCam >> inputImage;
        ui->grayScale->clicked();
        ui->middlePoints->clicked();
        ui->getIntensity->clicked();

        //Get set point from ui
        enableSetPoint();
        //Get the error and send it to the controller
        error_p = setPointFromUI - intensityLevel;
        fuzzyController(error_p);

    }
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
    //enable visualization of getIntensity button
    ui->getIntensity->setEnabled(true);
}

/* Function name: on_getIntensity_clicked()
 * Developer:     Raul Castañon
 * Details:       Get intensity levels from the image
 */
void MainWindow::on_getIntensity_clicked()
{
    Scalar promAreaOne, promAreaTwo, promAreaThree, promAreaFour, promAreaFive;
    Mat areaOne, areaTwo, areaThree, areaFour, areaFive;
    //Verify size of the area
    if((ui->widthArea->text().isEmpty())||(ui->hightArea->text().isEmpty()))
    {
        qDebug("Default size asigned");
        ui->widthArea->setText(QString::number(50));
        ui->hightArea->setText(QString::number(50));
    }
    //Get areas
    areaOne = inputImage(Rect(middlePoints[0][0], middlePoints[0][1], ui->widthArea->text().toInt(), ui->hightArea->text().toInt()));
    areaTwo = inputImage(Rect(middlePoints[1][0], middlePoints[1][1], ui->hightArea->text().toInt(), ui->hightArea->text().toInt()));
    areaThree = inputImage(Rect(middlePoints[2][0], middlePoints[2][1], ui->widthArea->text().toInt(), ui->hightArea->text().toInt()));
    areaFour = inputImage(Rect(middlePoints[3][0], middlePoints[3][1], ui->widthArea->text().toInt(), ui->hightArea->text().toInt()));
    areaFive = inputImage(Rect(middlePoints[4][0], middlePoints[4][1], ui->widthArea->text().toInt(), ui->hightArea->text().toInt()));
    //Get intensity level per area
    promAreaOne = mean(areaOne);
    promAreaTwo = mean(areaTwo);
    promAreaThree = mean(areaThree);
    promAreaFour = mean(areaFour);
    promAreaFive = mean(areaFive);
    //Show results
    ui->intensityLevel_1->setText(QString::number(promAreaOne[0]));
    ui->intensityLevel_2->setText(QString::number(promAreaTwo[0]));
    ui->intensityLevel_3->setText(QString::number(promAreaThree[0]));
    ui->intensityLevel_4->setText(QString::number(promAreaFour[0]));
    ui->intensityLevel_5->setText(QString::number(promAreaFive[0]));
    //Get intensity level mean
    intensityLevel = (int)((promAreaOne[0] + promAreaTwo[0] + promAreaThree[0] + promAreaFour[0] + promAreaFive[0]) / 5.0);
    ui->intensityLevel->setText(QString::number(intensityLevel));
}

/* Function name: enableSetPoint()
 * Developer:     Raul Castañon
 * Details:       Retrieve set point from UI
 */
void MainWindow::enableSetPoint(void)
{
    //Verify if there is a setPoint
    if(!(ui->setPoint->text().isEmpty()))
    {
        setPointFromUI = ui->setPoint->text().toInt();
    }
    //If not put a default value
    else
    {
        ui->setPoint->setText(DEFAULT_TEST_POINT);
        setPointFromUI = ui->setPoint->text().toInt();
    }
}
