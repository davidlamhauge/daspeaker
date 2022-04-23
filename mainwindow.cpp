#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QProcess>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
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
    connect(ui->sliderSpeed, &QSlider::valueChanged, this, &MainWindow::setSpeed);

    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::play);
    connect(ui->btnPause, &QPushButton::clicked, this, &MainWindow::pause);
    connect(ui->btnResume, &QPushButton::clicked, this, &MainWindow::resume);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::stop);
    connect(ui->cbLanguages, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::setLanguage);

    updateLabels();

    connect(QApplication::clipboard(), &QClipboard::selectionChanged, this, &MainWindow::updateClipboard);
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
    ui->labActualSpeed->setText(QString::number(mSpeed));
}

void MainWindow::updateClipboard()
{
    if (QApplication::clipboard()->text().length() > 0)
    {
        mSelection = QApplication::clipboard()->text();
    }
    else
    {
        mSelection = mBoard->text();
    }
}

void MainWindow::setVolume(int volume)
{
    mVolume = volume / 100.0;
    ui->labActualVolume->setText(QString::number(mVolume));
    mSpeaker->setVolume(mVolume);
}

void MainWindow::setSpeed(int speed)
{
    mSpeed = speed / 100.0;
    ui->labActualSpeed->setText(QString::number(mSpeed));
    mSpeaker->setRate(mSpeed);
}

void MainWindow::resetValues()
{
    setVolume(80);
    ui->sliderVolume->setValue(static_cast<int>(mVolume * 100));
    setSpeed(-70);
    ui->sliderSpeed->setValue(static_cast<int>(mSpeed * 100));
    updateLabels();
}

void MainWindow::play()
{
    updateClipboard();
    if (mSelection.length() > 0)
        mSpeaker->say(mSelection);
}

void MainWindow::pause()
{
    mSpeaker->pause();
}

void MainWindow::resume()
{
    mSpeaker->resume();
}

void MainWindow::stop()
{
    mSpeaker->stop();
}
