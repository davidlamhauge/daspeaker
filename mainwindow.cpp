#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QProcess>

#include "daspeaker_def.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    updateLabels();

    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnResetValues, &QPushButton::clicked, this, &MainWindow::resetValues);
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &MainWindow::setVolume);
    connect(ui->sliderPitch, &QSlider::valueChanged, this, &MainWindow::setPitch);
    connect(ui->sliderSpeed, &QSlider::valueChanged, this, &MainWindow::setSpeed);

    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::play);
}

void MainWindow::updateLabels()
{
    ui->labActualVolume->setText(QString::number(mVolume));
    ui->labActualPitch->setText(QString::number(mPitch));
    ui->labActualSpeed->setText(QString::number(mSpeed));
}

void MainWindow::resetValues()
{
    setVolume(100);
    ui->sliderVolume->setValue(mVolume);
    setPitch(50);
    ui->sliderPitch->setValue(mPitch);
    setSpeed(200);
    ui->sliderSpeed->setValue(mSpeed);
    updateLabels();
}

void MainWindow::play()
{
    QString progString = "ESPEAK ";
    progString += " -vda";
    progString += " -a" + QString::number(ui->sliderVolume->value());
    progString += " -p" + QString::number(ui->sliderPitch->value());
    progString += " -s" + QString::number(ui->sliderSpeed->value());
    QStringList list;
    list.append(" en kop kaffe, tak.");
    qDebug() << progString;
//    QProcess::execute(progString, list);
    QProcess::execute(QString("ESPEAK %1 %2 %3 %4").arg(" -vda ").arg("QString::number(ui->sliderVolume->value()")
                      .arg("QString::number(ui->sliderPitch->value()").arg("QString::number(ui->sliderSpeed->value()"), list);
}

void MainWindow::playSelection()
{

}

