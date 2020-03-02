#include "fileio.h"
#include "schedule.h"
#include "schedulecollection.h"
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <QTime>
#include <QList>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

}

bool FileIO::ExtractAudio()
{
    if(QFile::copy(":/new/sounds/alarm.ogg", QDir::tempPath()+"/QTalarm.ogg"))
    {
        return true;
    }
    return false;
}

bool FileIO::DelExtracted()
{
    return QFile::remove(QDir::tempPath()+"/QTalarm.ogg");
}

QList<Schedule*> FileIO::LoadConfig()
{
    QList<Schedule*> scheduleList;
    QString indexStr;

    for(int index=0;index<this->_Settings.value("AlarmCount").toInt();index++)
    {
        Schedule *sched=new Schedule(this);

        indexStr.setNum(index);

        sched->SetTime(this->_Settings.value(indexStr+"Time").toTime());
        if(sched->GetTime().isNull())
        {
            QTime reset;
            reset.setHMS(0,0,0,0);
            sched->SetTime(reset);
        }

        sched->setIsMonEnabled(this->_Settings.value(indexStr+"MonEnabled").toBool());
        sched->setIsTueEnabled(this->_Settings.value(indexStr+"TueEnabled").toBool());
        sched->setIsWedEnabled(this->_Settings.value(indexStr+"WedEnabled").toBool());
        sched->setIsThurEnabled(this->_Settings.value(indexStr+"ThurEnabled").toBool());
        sched->setIsFriEnabled(this->_Settings.value(indexStr+"FriEnabled").toBool());
        sched->setIsSatEnabled(this->_Settings.value(indexStr+"SatEnabled").toBool());
        sched->setIsSunEnabled(this->_Settings.value(indexStr+"SunEnabled").toBool());
        sched->SetIsBastard(this->_Settings.value(indexStr+"Bastard").toBool());

        sched->SetCustEnabled(this->_Settings.value(indexStr+"CustEnabled").toBool());
        sched->SetCust(this->_Settings.value(indexStr+"CustDate").toDate());

        sched->SetCustomSoundEnabled(this->_Settings.value(indexStr+"CustomSoundEnabled").toBool());
        sched->SetCustomSound(this->_Settings.value(indexStr+"CustomSound").toString());

        scheduleList.append(sched);
    }
    return scheduleList;
}

bool FileIO::Save(ScheduleCollection *Collection)
{
    try
    {
        QList<Schedule*> SchedList=Collection->GetScheduleList();
        Schedule *currentSche;
        int index=0;

        this->_Settings.setValue("AlarmCount",SchedList.count());
        foreach(currentSche,SchedList)
        {
            QString IndexStr;
            IndexStr.setNum(index);
            this->_Settings.setValue(IndexStr+"MonEnabled",currentSche->isMonEnabled());
            this->_Settings.setValue(IndexStr+"TueEnabled",currentSche->isTueEnabled());
            this->_Settings.setValue(IndexStr+"WedEnabled",currentSche->isWedEnabled());
            this->_Settings.setValue(IndexStr+"ThurEnabled",currentSche->isThurEnabled());
            this->_Settings.setValue(IndexStr+"FriEnabled",currentSche->isFriEnabled());
            this->_Settings.setValue(IndexStr+"SatEnabled",currentSche->isSatEnabled());
            this->_Settings.setValue(IndexStr+"SunEnabled",currentSche->isSunEnabled());
            this->_Settings.setValue(IndexStr+"Bastard",currentSche->isBastard());
            this->_Settings.setValue(IndexStr+"Time",currentSche->GetTime());
            this->_Settings.setValue(IndexStr+"CustEnabled",currentSche->GetCustomEnabled());
            this->_Settings.setValue(IndexStr+"CustDate",currentSche->GetCustomDate());
            this->_Settings.setValue(IndexStr+"CustomSoundEnabled",currentSche->GetCustomSoundEnabled());
            this->_Settings.setValue(IndexStr+"CustomSound",currentSche->GetCustomSound());
            this->_Settings.sync();
            index++;
        }
    }
    catch(...)
    {
        return false;
    }

    return true;
}

//static lazy loaded methods


int FileIO::LoadVolume()
{
    QSettings settings;
    return settings.value("Volume").toInt();
}

void FileIO::SaveVolume(int vol)
{
    QSettings settings;
    settings.setValue("Volume",vol);
}

bool FileIO::LoadWindowShow()
{
    QSettings settings;
    return settings.value("ShowWindowDefault").toBool();
}


void FileIO::SaveWindowShow(bool showWindow)
{
    QSettings settings;
    settings.setValue("ShowWindowDefault",showWindow);
}


bool FileIO::isMilTime()
{
    QSettings settings;
    return settings.value("isMilTime").toBool();
}

bool FileIO::LoadisMono()
{
    QSettings settings;
    return settings.value("isMono").toBool();
}

void FileIO::SaveisMono(bool isMono)
{
    QSettings settings;
    settings.setValue("isMono",isMono);
}

void FileIO::SaveisMilTime(bool isMilTime)
{
    QSettings settings;
    settings.setValue("isMilTime",isMilTime);
}


bool FileIO::LoadWarnOnPm()
{
    QSettings settings;
    return settings.value("WarnOnPm").toBool();
}

bool FileIO::LoadSeenSolveText()
{
    QSettings settings;
    return settings.value("SeenSolvedText").toBool();
}

void FileIO::SaveWarnOnPm(bool warn)
{
    QSettings settings;
    settings.setValue("WarnOnPm",warn);
}

void FileIO::SaveSeenSolveText()
{
    QSettings settings;
    settings.setValue("SeenSolvedText",true);
}
