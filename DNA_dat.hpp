#ifndef DNA_DAT_HPP
#define DNA_DAT_HPP

#include <Athena/DNA.hpp>
typedef Athena::io::DNA<Athena::BigEndian> BigDNA;

struct FootEntryCommon : BigDNA
{
    DECL_DNA
    Value<atUint64> offset;
    Value<atUint64> length;
    Value<atUint64> unknown;
    Value<atUint64> loadFlags;
};

struct SR2_DAT : BigDNA
{
    DECL_DNA
    Value<atUint64> footOff;
    Value<atUint64> footSz;

    Seek<DNA_COUNT(footOff), Athena::Begin> footSeek;

    struct FootEntry : BigDNA
    {
        DECL_DNA
        FootEntryCommon common;
        String<32> name;
    };

    Vector<FootEntry, DNA_COUNT(footSz / 64)> footEntries;
};

struct SR3_DAT : BigDNA
{
    DECL_DNA
    Value<atUint64> footOff;
    Value<atUint64> footSz;

    Seek<DNA_COUNT(footOff), Athena::Begin> footSeek;

    struct FootEntry : BigDNA
    {
        DECL_DNA
        FootEntryCommon common;
        String<128> name;
    };

    Vector<FootEntry, DNA_COUNT(footSz / 160)> footEntries;
};

struct GroupOffsets : BigDNA
{
    DECL_DNA
    Value<atUint32> count;
    Vector<atUint32, DNA_COUNT(count)> elements;
};

struct GroupHead : BigDNA
{
    DECL_DNA
    Value<atUint32> poolOff;
    Value<atUint32> poolLen;
    Value<atUint32> projOff;
    Value<atUint32> projLen;
    Value<atUint32> sdirOff;
    Value<atUint32> sdirLen;
    Value<atUint32> sampOff;
    Value<atUint32> sampLen;
};

struct SDirA : BigDNA
{
    DECL_DNA
    Value<atUint16> soundId;
    Value<atUint16> padding1;
    Value<atUint32> audioOffset;
    Value<atUint32> padding2;
    Value<atUint8> pitch;
    Value<atUint8> padding3;
    Value<atUint16> sampleRate;
    Value<atUint32> numSamples;
    Value<atUint32> loopStartSample;
    Value<atUint32> loopLengthSamples;
    Value<atUint32> SDirBOffset;
};

struct SDirB : BigDNA
{
    DECL_DNA
    Value<atUint16> unknown1;
    Value<atUint8> initialPS;
    Value<atUint8> loopPS;
    Value<atInt16> hist1;
    Value<atInt16> hist2;
    Value<atInt16> coefs[16];
};

#endif // DNA_DAT_HPP

