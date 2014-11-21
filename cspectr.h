#ifndef CSPECTR_H
#define CSPECTR_H

#include <Windows.h>

class CSpectr
{
public:
    CSpectr();

private:
    WORD exposition;
    int  current_time;
    byte device_mode;
    int  device_id;
};

#endif // CSPECTR_H
