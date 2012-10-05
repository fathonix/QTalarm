#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSystemTrayIcon>
#include <QMainWindow>
#include "timer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    Timer *TimeKeeper;
    Alarm *CurAlarm;
    ScheduleCollection *_Schedules;
    int _CurrentAlarm;

    void closeEvent(QCloseEvent*);
    void ShowActiveAlarm(Schedule*);

private slots:
    void ShowWindow();
    void ShowWindow(QSystemTrayIcon::ActivationReason);
    void SetWDTime();
    void SetWETime();
    void SetCustomTime();
    void ToggleWD(bool);
    void ToggleWE(bool);
    void ToggleCust(bool);
    void SetAlarmNumber();
    void Quit();
};

#endif // MAINWINDOW_H
