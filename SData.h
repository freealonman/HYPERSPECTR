#ifndef SDATA_H
#define SDATA_H



enum SPECTR_COMMANDS {NOP, GET_ID, SET_EXP, GET_EXP, GET_SP, SET_TIME, GET_TIME, SET_MOTOR, GET_MOTOR, SET_MODE, GET_MODE};
#define MARK_START   0xA5
#define MARK_END     0x5A
#define SETIDATASIZE 12
#define SPECDATASIZE 3600
#define SPECHEADSIZE 10
typedef unsigned char  byte;
typedef unsigned short WORD;
typedef unsigned long  DWORD;

struct SExposition
{
    byte m1;
    byte command;
    WORD exposition;
    WORD reserved;
    byte controll_sum;
    byte m2;
    SExposition (const WORD &Exposition, const SPECTR_COMMANDS& Command):exposition(Exposition),
                                                                        m1(MARK_START),command(Command),
                                                                        reserved(0),
                                                                        controll_sum(0),
                                                                        m2(MARK_END){};
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
                                                                        m1(MARK_START),command(Command),
                                                                        reserved(0),
                                                                        controll_sum(0),
                                                                        m2(MARK_END){};
};
struct SId
{
    byte m1;
    byte command;
    WORD id;
    WORD reserved;
    byte controll_sum;
    byte m2;
    SId():id(0),m1(MARK_START),command(GET_ID),controll_sum(0),m2(MARK_END){};
};
struct SSpectr
{
    byte m1;
    byte command;
    WORD reserved1;
    WORD reserved2;
    byte controll_sum;
    byte m2;
    SSpectr():m1(MARK_START),command(GET_SP),controll_sum(0),m2(MARK_END), reserved1(0),reserved2(0){};
};
struct STime
{
    byte m1;
    byte command;
    DWORD _time;
    byte controll_sum;
    byte m2;
    STime(const DWORD &Time, const SPECTR_COMMANDS& Command):_time(Time),
                                                                        m1(MARK_START),command(Command),
                                                                        controll_sum(0),
                                                                        m2(MARK_END){};
};

struct SMode
{
    byte m1;
    byte command;
    byte mode;
    byte reserved1;
    byte reserved2;
    byte reserved3;
    byte controll_sum;
    byte m2;
    STime(const byte &mode, const SPECTR_COMMANDS& Command):mode(Mode),reserved1(0), reserved2(0), reserved3(0),
                                                                        m1(MARK_START),command(Command),
                                                                        controll_sum(0),
                                                                        m2(MARK_END){};
};


struct SSpectrHeader
{
    WORD  exposition;
    WORD  drive_position;
    DWORD current_time;
    byte  offset;
    byte  device_mode;
};
struct SSpectrBytes
{
    byte dark_pixels[7];
    byte good_pixels[3600];
    byte dark_end[7];
};

struct SSpectrData
{
    SSpectrHeader header;
    SSpectrBytes  bytes;
};



#endif // SDATA_H
