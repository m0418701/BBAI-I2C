#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnWrite_clicked();
    void on_btnRead_clicked();

private:
    Ui::MainWindow *ui;

    int I2C_Open(int addr);
    int I2C_Write(char *addrStart, int length);
    int I2C_Read(char *bufRead, int length);
    int I2C_Close();
    int file = -1;
};
#endif // MAINWINDOW_H
