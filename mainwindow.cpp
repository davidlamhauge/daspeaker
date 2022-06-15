#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QProcess>
#include <QClipboard>
#include <QScreen>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    initUi();

    // position where we left it
    QSize scr = QGuiApplication::primaryScreen()->availableSize();
    QSettings settings("TeamLamhauge", "daSpeaker");
    resize(settings.value("winSize", QSize(400, 320)).toSize());
    move(settings.value("winPos", QPoint(scr.width()/2 - 200, scr.height()/2 - 160)).toPoint());

}

MainWindow::~MainWindow()
{
    QSettings settings("TeamLamhauge", "daSpeaker");
    settings.setValue("winSize", size());
    settings.setValue("winPos", pos());

    delete ui;
}

void MainWindow::initUi()
{
    setWindowTitle(tr("daspeaker"));

    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnResetValues, &QPushButton::clicked, this, &MainWindow::resetValues);
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &MainWindow::setVolume);
    connect(ui->sliderSpeed, &QSlider::valueChanged, this, &MainWindow::setSpeed);
    connect(ui->sliderPitch, &QSlider::valueChanged, this, &MainWindow::setPitch);

    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::play);
    connect(ui->cbLanguages, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::setLanguage);

    QSettings settings("TeamLamhauge", "daSpeaker");

    mLang = settings.value("lang", "-vda").toString();
    mLangIndex = settings.value("langIndex", 0).toInt();
    ui->cbLanguages->setCurrentIndex(mLangIndex);
    setLanguage(mLangIndex);

    mVolume = settings.value("volume", 100).toInt();
    setVolume(mVolume);
    mSpeed = settings.value("speed", 160).toInt();
    setSpeed(mSpeed);
    mPitch = settings.value("pitch", 50).toInt();
    setPitch(mPitch);

    updateLabels();

    connect(QApplication::clipboard(), &QClipboard::selectionChanged, this, &MainWindow::updateSelected);
}

void MainWindow::setLanguage(int lang)
{
    if (lang < 0)
        return;

    switch (lang)
    {
    case 0: mLang = "-vda"; break;
    case 1: mLang = "-ven"; break;
    case 2: mLang = "-vde"; break;
    case 3: mLang = "-vfr"; break;
    case 4: mLang = "-ves"; break;
    default: mLang = "-vda"; break;
    }
    QSettings settings("TeamLamhauge", "daSpeaker");
    settings.setValue("lang", mLang);
    settings.setValue("langIndex", lang);
}

void MainWindow::updateLabels()
{
    ui->labActualVolume->setText(QString::number(mVolume));
    ui->labActualSpeed->setText(QString::number(mSpeed));
    ui->labActualPitch->setText(QString::number(mPitch));
}

void MainWindow::updateSelected()
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
    mVolume = volume;
    mSetVolume = "-a" + QString::number(volume);
    ui->sliderVolume->setValue(volume);
    ui->labActualVolume->setText(QString::number(mVolume));
    QSettings settings("TeamLamhauge", "daSpeaker");
    settings.setValue("volume", mVolume);
}

void MainWindow::setSpeed(int speed)
{
    mSpeed = speed;
    mSetSpeed = "-s" + QString::number(speed);
    ui->sliderSpeed->setValue(speed);
    ui->labActualSpeed->setText(QString::number(mSpeed));
    QSettings settings("TeamLamhauge", "daSpeaker");
    settings.setValue("speed", mSpeed);
}

void MainWindow::setPitch(int pitch)
{
    mPitch = pitch;
    mSetPitch = "-p" + QString::number(pitch);
    ui->sliderPitch->setValue(pitch);
    ui->labActualPitch->setText(QString::number(mPitch));
    QSettings settings("TeamLamhauge", "daSpeaker");
    settings.setValue("pitch", mPitch);
}

void MainWindow::resetValues()
{
    // includes updating settings
    setVolume(100);
    ui->sliderVolume->setValue(100);
    setSpeed(180);
    ui->sliderSpeed->setValue(180);
    setPitch(50);
    ui->sliderPitch->setValue(50);
    updateLabels();
}

void MainWindow::play()
{
    updateSelected();
    QProcess* proc = new QProcess();
    QString path = QGuiApplication::applicationDirPath() + "/eSpeak/command_line/espeak.exe";
    QStringList args;
    args << mLang << mSetSpeed << mSetVolume << mSetPitch << mSelection;
    proc->start(path , args);
}
