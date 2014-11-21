#ifndef SDATA_H
#define SDATA_H

#include <Windows.h>

enum SPECTR_COMMANDS {NOP, GET_ID, SET_EXP, GET_EXP, GET_SP, SET_TIME, GET_TIME, SET_MOTOR, GET_MOTOR, SET_MODE, GET_MODE};

struct SExposition
{
    byte m1;
    byte command;
    WORD exposition;
    WORD reserved;
    byte controll_sum;
    byte m2;
    SExposition (const WORD &Exposition, const SPECTR_COMMANDS& Command):exposition(Exposition),
                                                                        m1(0xA5),command(Command),
                                                                        reserved(0),
                                                                        controll_sum(0),
                                                                        m2(0x5A){};
};
struct SDrive
{
    byte m1;
    byte command;
    WORD drive;
    WORD reserved;
    byte controll_sum;
    byte m2;
    SDrive(const WORD &Drive, const SPECTR_COMMANDS& Command):drive(Drive),
                                                                        m1(0xA5),command(Command),
                                                                        reserved(0),
                                                                        controll_sum(0),
                                                                        m2(0x5A){};
};
struct SId
{
    byte m1;
    byte command;
    WORD id;
    WORD reserved;
    byte controll_sum;
    byte m2;
    SId():id(0),m1(0xA5),command(GET_ID),controll_sum(0),m2(0x5A){};
};
struct SSpectr
{
    byte m1;
    byte command;
    WORD reserved1;
    WORD reserved2;
    byte controll_sum;
    byte m2;
    SSpectr():m1(0xA5),command(GET_SP),controll_sum(0),m2(0x5A), reserved1(0),reserved2(0){};
};
struct STime
{
    byte m1;
    byte command;
    DWORD _time;
    byte controll_sum;
    byte m2;
    STime(const DWORD &Time, const SPECTR_COMMANDS& Command):_time(Time),
                                                                        m1(0xA5),command(Command),
                                                                        controll_sum(0),
                                                                        m2(0x5A){};
};

struct SSpectrHeader
{
    WORD  exposition;
    WORD  drive_position;
    DWORD current_time;
    byte  offset;
    byte  device_mode;
};


#endif // SDATA_H
