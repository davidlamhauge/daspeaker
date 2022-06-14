#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGuiApplication>

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

    int mVolume = 100;
    QString mSetVolume = "-a100";
    int mSpeed = 180;
    QString mSetSpeed = "-s175";

    QClipboard* mBoard = QGuiApplication::clipboard();
    QString mSelection = "";

    QString mLang = "-vda";     // Danish is default

};
#endif // MAINWINDOW_H
