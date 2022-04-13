#include "mainwindow.h"
#include "ui_mainwindow.h"

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

