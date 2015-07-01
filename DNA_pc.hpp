#ifndef DNA_PC_HPP
#define DNA_PC_HPP

#include <Athena/DNA.hpp>
typedef Athena::io::DNA<Athena::LittleEndian> LittleDNA;

struct PC_DAT : public LittleDNA
{
    DECL_DNA
    Value<atUint32> fstOff;
    Value<atUint32> fstSz;
    Seek<DNA_COUNT(fstOff), Athena::Begin> seekToFST;

    struct FSTEntry : public LittleDNA
    {
        DECL_DNA
        Value<atUint32> offset;
        Value<atUint32> size;
        Value<atUint32> padding;
        Value<atUint16> type;
        Value<atUint16> childCount;
        String<16> name;
    };
    Vector<FSTEntry, DNA_COUNT(fstSz / 32)> fileNodes;
};

struct PC_SDIREntry : public LittleDNA
{
    DECL_DNA
    Value<atUint16> soundId;
    Value<atUint16> padding1;
    Value<atUint32> audioOffset;
    Value<atUint16> sampleRate;
    Value<atUint8> padding2;
    Value<atUint8> pitch;
    Value<atUint32> numSamples;
    Value<atUint32> loopStartSample;
    Value<atUint32> loopLengthSamples;
};

#endif // DNA_PC_HPP
