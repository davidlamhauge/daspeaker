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

    // languages
    mLanguages = mSpeaker->availableLocales();
    mSpeaker->setLocale(QLocale::Danish);

    // Voices
    mVoices = mSpeaker->availableVoices();


    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnResetValues, &QPushButton::clicked, this, &MainWindow::resetValues);
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &MainWindow::setVolume);
    connect(ui->sliderPitch, &QSlider::valueChanged, this, &MainWindow::setPitch);
    connect(ui->sliderSpeed, &QSlider::valueChanged, this, &MainWindow::setSpeed);

    connect(ui->plainTextHolder, &QPlainTextEdit::textChanged, this, &MainWindow::updatePlayButtons);

    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::play);
    connect(ui->cbLanguages, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::setLanguage);

    updateLabels();
    updatePlayButtons();
}

void MainWindow::setLanguage(int lang)
{
    if (lang < 0)
        return;

    switch (lang)
    {
    case 0:
        mSpeaker->setLocale(QLocale::Danish);
        break;
    case 1:
        mSpeaker->setLocale(QLocale::English);
        break;
    case 2:
        mSpeaker->setLocale(QLocale::German);
        break;
    case 3:
        mSpeaker->setLocale(QLocale::French);
        break;
    case 4:
        mSpeaker->setLocale(QLocale::Spanish);
        break;
    default:
        mSpeaker->setLocale(QLocale::Danish);
        break;
    }
}

void MainWindow::updateLabels()
{
    ui->labActualVolume->setText(QString::number(mVolume));
    ui->labActualPitch->setText(QString::number(mPitch));
    ui->labActualSpeed->setText(QString::number(mSpeed));
}

void MainWindow::setVolume(int volume)
{
    mVolume = volume / 100.0;
    ui->labActualVolume->setText(QString::number(mVolume));
    mSpeaker->setVolume(mVolume);
}

void MainWindow::setPitch(int pitch)
{
    mPitch = pitch / 100.0;
    ui->labActualPitch->setText(QString::number(mPitch));
    mSpeaker->setPitch(mPitch);
}

void MainWindow::setSpeed(int speed)
{
    mSpeed = speed / 100.0;
    ui->labActualSpeed->setText(QString::number(mSpeed));
    mSpeaker->setRate(mSpeed);
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

