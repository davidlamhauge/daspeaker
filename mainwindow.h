#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtTextToSpeech/QTextToSpeech>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void initUi();
    void updateLabels();

    void setVolume(int volume) { mVolume = volume; updateLabels(); }
    void setPitch(int pitch) { mPitch = pitch; updateLabels(); }
    void setSpeed(int speed) { mSpeed = speed; updateLabels(); }
    void resetValues();

    void updatePlayButtons();
    void play();
    void playSelection();

    int mVolume = 100;
    int mPitch = 50;
    int mSpeed = 200;

    QTextToSpeech* mSpeaker;
    QVector<QLocale> mLanguages;
    QVector<QVoice> mVoices;
};
#endif // MAINWINDOW_H
