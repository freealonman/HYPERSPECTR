#include "cspectr.h"

CSpectr::CSpectr()
{
    is_port_open      = false;
    device_exposition = 0;
    device_drive      = 0;
    device_id         = 0;
    device_mode       = 0;
    device_time       = 0;
    exposition        = 0;
    drive             = 0;
    mode              = 0;
    com_port          = NULL;
    SetState(NOP);
}

CSpectr::~CSpectr()
{
    if (is_port_opened) DisconnectDevice();
}

bool CSpectr::ConnectDevice(const QString &PortName)
{
    com_port = new QSerialPort(this);
    com_port->setPortName(PortName);
    com_port->setDataBits(QSerialPort::Data8);
    com_port->setStopBits(QSerialPort::OneStop);
    com_port->setBaudRate(QSerialPort::Baud115200);
    com_port->setParity(QSerialPort::NoParity);

    connect(com_port, SIGNAL(readyRead()), this, SLOT(DataOnPort()));

    if (!com_port->open(QIODevice::ReadWrite))
    {
        is_port_open = true;
        return true;
    }
    else
    {
        is_port_open = false;
        return false;
    }

}

void CSpectr::DisconnectDevice()
{
    com_port->close();
}

void CSpectr::DataRecived(const SPECTR_COMMANDS &DataType)
{

}

void CSpectr::GetSpectr()
{
    if (is_port_open)
    {
        com_port->write((char*)(&SSpectr()));
        SetState(GET_SP);
    }
}

void CSpectr::GetID()
{
    if (is_port_open)
    {
        com_port->write((char*)(&SId()));
        SetState(GET_ID);
    }
}

void CSpectr::GetExposition()
{
    if (is_port_open)
    {
        com_port->write((char*)(&SExposition(0, GET_EXP)));
    }
}

void CSpectr::GetTime()
{
    if (is_port_open)
    {
        com_port->write((char*)(&STime(0, GET_TIME)));
        SetState(GET_TIME);
    }
}

void &CSpectr::GetDrive()
{
    if (is_port_open)
    {
        com_port->write((char*)(&SDrive(0, GET_MOTOR)));
        SetState(GET_MODE);
    }

}

void CSpectr::GetSwitch()
{

}

DWORD CSpectr::GetCurrentTime()
{
    using namespace std::chrono;

    milliseconds ms = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());


    return 0;
}

void CSpectr::SetExposition(const WORD &Exposition)
{
    if (is_port_open)
    {
        com_port->write((char*)(&SExposition(exposition, SET_EXP)));
        SetState(SET_EXP);
    }
}

void CSpectr::SetTime(const DWORD &Time)
{
    if (is_port_open)
    {
        com_port->write((char*)(&STime(GetCurrentTime(), SET_TIME)));
        SetState(SET_TIME);
    }
}

void CSpectr::SetDrive()
{
    if (is_port_open)
    {
        com_port->write((char*)(&SDrive(drive, SET_MOTOR)));
        SetState(SET_MOTOR);
    }
}

void CSpectr::SetMode()
{
    if (is_port_open)
    {
        com_port->write((char*)(&SMode(mode, SET_MODE)));
        SetState(SET_MODE);
    }
}

void CSpectr::SetState(const SPECTR_COMMANDS &State)
{
    state = State;
    if(State == NOP)
    {
        bytes_readed = 0;
        if(data_readed != NULL)
        {
            delete data_readed;
        }
    }
}

void CSpectr::ReadData(QByteArray **Data)
{
    qint64 buf_readed = com_port->readBufferSize();
    for (int i=0; i < buf_readed; i++)
    {
        (*Data)->append(com_port->read(1));
    }
}



void CSpectr::DataOnPort()
{
    if (data_readed == NULL)
    {
        data_readed = new QByteArray();
    }

    ReadData(&data_readed);

    switch(state)
    {
    case NOP:{break;}
    case GET_ID:
    {
        if (data_readed->size() < SETIDATASIZE) {return;}

        device_id = ((SId*)(data_readed->data()))->id;
        break;
    }
    case (GET_EXP,SET_EXP):
    {
        if (data_readed->size() < SETIDATASIZE) {return;}

        device_exposition = ((SExposition*)(data_readed->data()))->exposition;
        break;
    }
    case (GET_TIME,SET_TIME):
    {
        if (data_readed->size() < SETIDATASIZE) {return;}

        device_time = ((STime*)(data_readed->data()))->_time;
        break;
    }
    case (GET_MOTOR, SET_MOTOR):
    {
        if (data_readed->size() < SETIDATASIZE) {return;}

        device_drive = ((SDrive*)(data_readed->data()))->drive;
        break;
    }
    case (GET_MODE, SET_MODE):
    {
        if (data_readed->size() < SETIDATASIZE) {return;}

        device_mode = ((SMode*)(data_readed->data()))->mode;
        break;
    }
    case GET_SP:
    {
        if (data_readed->size() < (SPECDATASIZE + SPECHEADSIZE)) {return;}

        SSpectrData spectr_data;
        memset(&spectr_data, 0, sizeof(SSpectrData));
        memcpy(&spectr_data, data_readed->data(),sizeof(SSpectrData));
        spectres.push_back(spectr_data);
        break;
    }
    }
    SetState(NOP);
}
