#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGuiApplication>

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
    void updateClipboard();

    void setVolume(int volume);
    void setSpeed(int speed);
    void resetValues();

    void play();
    void pause();
    void resume();
    void stop();

    double mVolume = 0.75;
    double mSpeed = 0.0;

    QClipboard* mBoard = QGuiApplication::clipboard();
    QString mSelection = "";

    QTextToSpeech* mSpeaker;
    QVector<QLocale> mLanguages;
    QVector<QVoice> mVoices;
};
#endif // MAINWINDOW_H
