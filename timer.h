#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDateTime>
#include <QList>
#include "alarm.h"
#include "schedule.h"
#include "schedulecollection.h"

class Timer : public QObject
{
    Q_OBJECT
public:
    void StartTimer(Alarm*);
    explicit Timer(QObject *parent = 0,ScheduleCollection* Collection=0);

private:
    Alarm *_CurAlarm;
    QList<Schedule *> _Schedules;
    void SetCustomSound(int);

signals:
    
private slots:
    void AlarmCheck();
};

#endif // TIMER_H
