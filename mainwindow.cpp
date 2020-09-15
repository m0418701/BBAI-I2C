#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int nI2COpenResault = I2C_Open(0x50);
    ui->teMessage->append(QString("I2C Open resault:%1").arg(nI2COpenResault));
}

MainWindow::~MainWindow()
{
    I2C_Close();

    delete ui;
}


int MainWindow::I2C_Open(int addr)
{
    QString sFilename = "/dev/i2c-3";
    QByteArray ba = sFilename.toLocal8Bit();
    const char *filename = ba.data();
    file = open(filename, O_RDWR);
    if(file < 0)
    {
        qDebug() << "Open i2c-3 file failed.";
        return file;
    }
    int ret = ioctl(file, I2C_SLAVE, addr);
    if(ret < 0)
    {
        qDebug() << "Open Buss failed.";
        return ret;
    }
    return ret;
}

int MainWindow::I2C_Write(char *addrStart, int length)
{
    if(file == -1)
        return -1;
    int ret = write(file, addrStart, length);
    return ret;
}

int MainWindow::I2C_Read(char *bufRead, int length)
{
    if(file == -1)
        return -1;
    int ret = read(file, bufRead, length);
    return ret;
}

int MainWindow::I2C_Close()
{
    if(file == -1)
        return -1;
    ::close(file);
    return 0;
}

void MainWindow::on_btnWrite_clicked()
{
    char cWriteData[3];
    cWriteData[0] = ui->leAddr1->text().toInt();
    cWriteData[1] = ui->leAddr2->text().toInt();
    cWriteData[2] = ui->leData->text().toInt();

    int nResault = I2C_Write(cWriteData, 3);
    ui->teMessage->append(QString("write Resault:%1").arg(nResault));
}

void MainWindow::on_btnRead_clicked()
{
    char *rbuf = new char;
    char cWriteData[2] = {ui->leAddr1->text().toInt(), ui->leAddr2->text().toInt()};
    int nWriteResault = I2C_Write(cWriteData, 2);
    usleep(1000);
    int nReadResault = I2C_Read(rbuf, ui->leReadLength->text().toInt());
    ui->teMessage->append(QString("ReadWrite Resault:%1").arg(nWriteResault));
    ui->teMessage->append(QString("Read Resault:%1").arg(nReadResault));
    ui->teMessage->append(QString("Read Data:%1").arg((int)*rbuf));

    delete rbuf;
}
