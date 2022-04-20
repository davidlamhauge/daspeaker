#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QProcess>

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
    setWindowTitle(tr("daspeaker"));

    // engine
    mSpeaker = new QTextToSpeech(this);
    const auto engines = mSpeaker->availableEngines();
    mSpeaker->say(tr("Hello world. Here we go again!"));

    // languages
    mLanguages = mSpeaker->availableLocales();
    mSpeaker->setLocale(QLocale::Danish);

    // Voices
//    mVoices = mSpeaker->availableVoices();


    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnResetValues, &QPushButton::clicked, this, &MainWindow::resetValues);
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &MainWindow::setVolume);
    connect(ui->sliderPitch, &QSlider::valueChanged, this, &MainWindow::setPitch);
    connect(ui->sliderSpeed, &QSlider::valueChanged, this, &MainWindow::setSpeed);

    connect(ui->plainTextHolder, &QPlainTextEdit::textChanged, this, &MainWindow::updatePlayButtons);

    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::play);

    updateLabels();
    updatePlayButtons();
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

void MainWindow::updatePlayButtons()
{
    if (ui->plainTextHolder->toPlainText().length() < 1)
    {
        ui->btnPlay->setEnabled(false);
        ui->btnPlaySelection->setEnabled(false);
    }
    else
    {
        ui->btnPlay->setEnabled(true);
        ui->btnPlaySelection->setEnabled(true);
    }
}

void MainWindow::play()
{
    mSpeaker->say(ui->plainTextHolder->toPlainText());
}

void MainWindow::playSelection()
{

}

