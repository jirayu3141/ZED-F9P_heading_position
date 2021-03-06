// File lang/cpp/src/messages/ESF.h
// Auto-generated by pyUBX generateCpp.py v0.1 on 2020-09-09T14:11:58.938137
// See https://github.com/mayeranalytics/pyUBX
// DO NOT MODIFY THIS FILE!

#ifndef __ESF_H__
#define __ESF_H__

#include <stdint.h>
#include "../UBX.h"

/* Message class ESF.
 */
struct ESF
{
    struct MEAS;
};

struct ESF::MEAS : public Message
{
    uint32_t timeTag;
    uint16_t flags;
    uint16_t id;

    struct Repeated {
        uint32_t data;
    };
    typedef _iterator<ESF::MEAS::Repeated> iterator;
    static _iterator<Repeated> iter(char*data, size_t size) {
        return _iterator<Repeated>(data+sizeof(ESF::MEAS), size-sizeof(ESF::MEAS));
    }
    static _iterator<Repeated> iter(ESF::MEAS& msg, size_t size) {
        return iter((char*)(&msg), size);
    }
    static size_t size(size_t n) { return sizeof(ESF::MEAS) + n*sizeof(ESF::MEAS::Repeated); }

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t ESF::MEAS::classID   = 0x10;
uint8_t ESF::MEAS::messageID = 0x02;

#endif // ifndef __ESF_H__
