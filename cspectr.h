#ifndef CSPECTR_H
#define CSPECTR_H

#include "SData.h"
#include <chrono>
#include <QSerialPort>

class CSpectr:public QObject
{
    Q_OBJECT
public:
    CSpectr();
    ~CSpectr();
    bool            ConnectDevice     (const QString& PortName);
    void            DisconnectDevice  ();
    void            SaveSingleSpectr  (QString FileName);
    void            SaveMultiplySpectr(QString FileNameMask);

signals:
    void            DataRecived       (const SPECTR_COMMANDS& DataType);

private:
//data
    std::vector<SSpectrBytes>  spectres;
//device config
    WORD            device_exposition;
    byte            device_mode;
    WORD            device_id;
    WORD            device_drive;
    DWORD           device_time;
    WORD            exposition;
    WORD            drive;
    WORD            mode;
//port config
    QSerialPort     *com_port;
    bool            is_port_open;
//
    SPECTR_COMMANDS state;
    QByteArray      *data_readed;

    void            GetSpectr();
    void            GetID();
    void            GetExposition();
    void            GetTime();
    void            GetDrive();
    void            GetSwitch();
    DWORD           GetCurrentTime();
    void            SetExposition(const WORD& Exposition);
    void            SetTime      (const DWORD& Time);
    void            SetDrive();
    void            SetMode();
    void            SetState(const SPECTR_COMMANDS& State);
    void            ReadData(QByteArray** Data);

private slots:
    void            DataOnPort();
};

#endif // CSPECTR_H
