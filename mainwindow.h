#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void play();
    void playSelection();

    int mVolume = 100;
    int mPitch = 50;
    int mSpeed = 200;
};
#endif // MAINWINDOW_H
