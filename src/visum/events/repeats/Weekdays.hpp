/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

enum Weekdays
: uint8_t
{
    Sunday    = 0x01,
    Monday    = 0x02,
    Tuesday   = 0x04,
    Wednesday = 0x08,
    Thursday  = 0x10,
    Friday    = 0x20,
    Saturday  = 0x40,
};

inline Weekdays operator|(Weekdays a, Weekdays b)
{
    return static_cast<Weekdays>(static_cast<uint8_t>(a)|
                                 static_cast<uint8_t>(b));
}
