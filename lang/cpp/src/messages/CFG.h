// File lang/cpp/src/messages/CFG.h
// Auto-generated by pyUBX generateCpp.py v0.1 on 2020-09-09T14:11:58.936625
// See https://github.com/mayeranalytics/pyUBX
// DO NOT MODIFY THIS FILE!

#ifndef __CFG_H__
#define __CFG_H__

#include <stdint.h>
#include "../UBX.h"

/* Message class CFG.
 */
struct CFG
{
    struct GNSS;
    struct PM2;
    struct PMS;
    struct PRT;
    struct PRT_GET;
    struct RATE;
    struct RXM;
    struct TP5;
    struct TP5_GET;
};

/* GNSS system configuration. §31.11.10.
 */
struct CFG::GNSS : public Message
{
    uint8_t msgVer;
    uint8_t numTrkChHw;
    uint8_t numTrkChUse;
    uint8_t numConfigBlocks;

    struct Repeated {
        uint8_t gnssId;
        uint8_t resTrkCh;
        uint8_t maxTrkCh;
        uint8_t reserved;
        uint32_t flags;
    };
    typedef _iterator<CFG::GNSS::Repeated> iterator;
    static _iterator<Repeated> iter(char*data, size_t size) {
        return _iterator<Repeated>(data+sizeof(CFG::GNSS), size-sizeof(CFG::GNSS));
    }
    static _iterator<Repeated> iter(CFG::GNSS& msg, size_t size) {
        return iter((char*)(&msg), size);
    }
    static size_t size(size_t n) { return sizeof(CFG::GNSS) + n*sizeof(CFG::GNSS::Repeated); }

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::GNSS::classID   = 0x06;
uint8_t CFG::GNSS::messageID = 0x3E;

/* §31.11.20 Extended Power Management configuration.
 */
struct CFG::PM2 : public Message
{
    uint8_t version;
    uint8_t reserved1;
    uint8_t maxStartupStartupDur;
    uint8_t reserved2;
    uint32_t flags;
    uint32_t updatePeriod;
    uint32_t searchPeriod;
    uint32_t gridOffset;
    uint16_t onTime;
    uint16_t minAcqTime;
    uint8_t reserved3[20];
    uint32_t extintInactivityMs;

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::PM2::classID   = 0x06;
uint8_t CFG::PM2::messageID = 0x3B;

struct CFG::PMS : public Message
{
    uint8_t version;
    uint8_t powerSetupValue;
    uint16_t period;
    uint16_t onTime;
    uint16_t reserved;

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::PMS::classID   = 0x06;
uint8_t CFG::PMS::messageID = 0x86;

/* §31.11.22.4 Port Configuration.
 */
struct CFG::PRT : public Message
{
    uint8_t portID;
    uint8_t reserved1;
    uint16_t txReady;
    uint32_t mode;
    uint32_t reserved2;
    uint16_t inProtoMask;
    uint16_t outProtoMask;
    uint16_t flags;
    uint16_t reserved3;

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::PRT::classID   = 0x06;
uint8_t CFG::PRT::messageID = 0x00;

/* §31.11.22.4 Port Configuration.
 */
struct CFG::PRT_GET : public Message
{
    uint8_t portID;

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::PRT_GET::classID   = 0x06;
uint8_t CFG::PRT_GET::messageID = 0x00;

/* §31.11.24 Navigation/Measurement Rate Settings.
 */
struct CFG::RATE : public Message
{
    uint16_t measRate;
    uint16_t navRate;
    uint16_t timeRef;

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::RATE::classID   = 0x06;
uint8_t CFG::RATE::messageID = 0x08;

/* §31.11.27 RXM configuration.
 * 
 *         For a detailed description see section 'Power Management'.
 *         
 */
struct CFG::RXM : public Message
{
    uint8_t reserved1;
    uint8_t lpMode;

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::RXM::classID   = 0x06;
uint8_t CFG::RXM::messageID = 0x11;

/* §31.11.32.3 Time Pulse Parameters.
 */
struct CFG::TP5 : public Message
{
    uint8_t tpIdx;
    uint8_t version;
    uint16_t reserved2;
    int16_t antCableDelay;
    int16_t rfGroupDelay;
    uint32_t freqPeriod;
    uint32_t freqPeriodLock;
    uint32_t pulseLenRatio;
    uint32_t pulseLenRatioLock;
    int32_t userConfigDelay;
    uint32_t flags;

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::TP5::classID   = 0x06;
uint8_t CFG::TP5::messageID = 0x31;

/* §31.11.32.2 Poll Time Pulse Parameters.
 */
struct CFG::TP5_GET : public Message
{
    uint8_t tpIdx;

    static uint8_t classID;
    static uint8_t messageID;
};

uint8_t CFG::TP5_GET::classID   = 0x06;
uint8_t CFG::TP5_GET::messageID = 0x00;

#endif // ifndef __CFG_H__
