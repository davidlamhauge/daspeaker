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
    void setLanguage(int lang);
    void updateLabels();

    void setVolume(int volume);
    void setPitch(int pitch);
    void setSpeed(int speed);
    void resetValues();

    void updatePlayButtons();
    void play();
    void playSelection();

    double mVolume = 0.75;
    double mPitch = 0.0;
    double mSpeed = 0.0;

    QString espeak = "espeak";
    QTextToSpeech* mSpeaker;
    QVector<QLocale> mLanguages;
    QVector<QVoice> mVoices;
};
#endif // MAINWINDOW_H
