#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "DNA_dat.hpp"
#include <Athena/FileReader.hpp>
#include <Athena/MemoryReader.hpp>
#include <memory>

#if _WIN32
#include <direct.h>
#define mkdir(dir, mode) _mkdir(dir)
#define snprintf _snprintf
#endif

typedef unsigned char TADPCMFrame[8];

static const int nibble_to_int[16] = {0,1,2,3,4,5,6,7,-8,-7,-6,-5,-4,-3,-2,-1};

static inline short samp_clamp(int val) {
    if (val < -32768) val = -32768;
    if (val > 32767) val = 32767;
    return val;
}

struct SampleLoop {
    atUint32 dwIdentifier;
    atUint32 dwType;
    atUint32 dwStart;
    atUint32 dwEnd;
    atUint32 dwFraction;
    atUint32 dwPlayCount;
};

struct SamplerChunk {
    union {
        char idname[4];
        atUint32 fourcc;
    };
    atUint32 chunkSize;

    atUint32 dwManufacturer;
    atUint32 dwProduct;
    atUint32 dwSamplePeriod;
    atUint32 dwMIDIUnityNote;
    atUint32 dwMIDIPitchFraction;
    atUint32 dwSMPTEFormat;
    atUint32 dwSMPTEOffset;
    atUint32 cSampleLoops;
    atUint32 cbSamplerData;
    struct SampleLoop Loop;
};

static void parseAudData(const FootEntryCommon& entry,
                         Athena::io::FileReader& datReader,
                         const char* dirRoot)
{
    datReader.seek(entry.offset, Athena::Begin);
    std::unique_ptr<atUint8[]> audBuf(new atUint8[entry.length]);
    datReader.readBytesToBuf(audBuf.get(), entry.length);
    Athena::io::MemoryReader audReader(audBuf.get(), entry.length);
    audReader.setEndian(Athena::BigEndian);

    atUint32 poolLen = audReader.readUint32();
    (void)poolLen;
    atUint32 indexOff = audReader.readUint32();
    audReader.seek(indexOff, Athena::Begin);
    GroupOffsets groupOffs;
    groupOffs.read(audReader);

    mkdir(dirRoot, 0755);
    for (atUint32 i=0 ; i<groupOffs.count ; ++i)
    {
        GroupHead head;
        audReader.seek(groupOffs.elements[i], Athena::Begin);
        head.read(audReader);

        char dirName[64];
        snprintf(dirName, 64, "%s/%03d", dirRoot, i);
        mkdir(dirName, 0755);

        std::vector<SDirA> sdirA;
        audReader.seek(head.sdirOff, Athena::Begin);
        atUint32 word = audReader.readUint32();
        while (word != 0xFFFFFFFF)
        {
            audReader.seek(-4);
            sdirA.emplace_back();
            sdirA.back().read(audReader);
            word = audReader.readUint32();
        }

        const atUint8* sampBase = audBuf.get() + head.sampOff;
        for (const SDirA& sfx : sdirA)
        {
            atUint32 numSamples = sfx.numSamples & 0xFFFFFF;
            atUint8 loops = sfx.numSamples >> 24;

            SDirB sdirB;
            audReader.seek(head.sdirOff + sfx.SDirBOffset, Athena::Begin);
            sdirB.read(audReader);

            char filename[128];
            snprintf(filename, 128, "%s/SFX_%04X.wav", dirName, sfx.soundId);

            FILE* wavef = fopen(filename, "wb");
            fwrite("RIFF", 1, 4, wavef);
            atUint32 dataSize = numSamples * 2;
            atUint32 chunkSize = 36 + dataSize;
            if (loops)
                chunkSize += 68; /* smpl chunk */
            fwrite(&chunkSize, 1, 4, wavef);
            fwrite("WAVE", 1, 4, wavef);

            fwrite("fmt ", 1, 4, wavef);
            atUint32 sixteen = 16;
            fwrite(&sixteen, 1, 4, wavef);
            atUint16 audioFmt = 1;
            fwrite(&audioFmt, 1, 2, wavef);
            atUint16 chCount = 1;
            fwrite(&chCount, 1, 2, wavef);
            atUint32 sampRate = sfx.sampleRate;
            fwrite(&sampRate, 1, 4, wavef);
            atUint16 blockAlign = 2;
            atUint32 byteRate = sampRate * blockAlign;
            fwrite(&byteRate, 1, 4, wavef);
            fwrite(&blockAlign, 1, 2, wavef);
            atUint16 bps = 16;
            fwrite(&bps, 1, 2, wavef);

            fwrite("data", 1, 4, wavef);
            fwrite(&dataSize, 1, 4, wavef);

            const TADPCMFrame* adpcmBlock = (TADPCMFrame*)(sampBase + sfx.audioOffset);
            unsigned blockFrame = 0;
            short pcmBlock[14];
            unsigned long samplescompleted = 0;
            short hist[2] = {0, 0};
            while (samplescompleted < numSamples)
            {
                unsigned samplesremaining = numSamples - samplescompleted;

                unsigned char cIdx = (adpcmBlock[blockFrame][0]>>4) & 0xf;
                short factor1 = sdirB.coefs[cIdx*2];
                short factor2 = sdirB.coefs[cIdx*2+1];
                unsigned char exp = adpcmBlock[blockFrame][0] & 0xf;
                unsigned s;
                for (s=0 ; s<14 && s<samplesremaining ; ++s) {
                    int sample_data = (s&1)?
                    nibble_to_int[(adpcmBlock[blockFrame][s/2+1])&0xf]:
                    nibble_to_int[(adpcmBlock[blockFrame][s/2+1]>>4)&0xf];
                    sample_data <<= exp;
                    sample_data <<= 11;
                    sample_data += 1024;
                    sample_data +=
                    factor1 * hist[0] +
                    factor2 * hist[1];
                    sample_data >>= 11;
                    sample_data = samp_clamp(sample_data);
                    pcmBlock[s] = sample_data;
                    hist[1] = hist[0];
                    hist[0] = sample_data;
                }
                fwrite(pcmBlock, 2, s, wavef);
                samplescompleted += s;
                ++blockFrame;
            }

            if (loops) {

                /* Build smpl chunk */
                struct SamplerChunk smpl = {
                    {{}},
                    60,
                    0,
                    0,
                    1000000000 / (atUint32)sfx.sampleRate,
                    60, /* Middle C */
                    0,
                    0,
                    0,
                    1,
                    0,
                    {
                        0x00020000,
                        0,
                        sfx.loopStartSample,
                        sfx.loopStartSample + sfx.loopLengthSamples - 1,
                        0,
                        0
                    }
                };
                memcpy(smpl.idname, "smpl", 4);

                fwrite(&smpl, 1, sizeof(smpl), wavef);

            }

            fclose(wavef);

        }

    }

}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: swrs_extract <game-num (2 or 3)> <dat-file>\n");
        return -1;
    }

    int rel = atoi(argv[1]);
    if (rel != 2 && rel != 3)
    {
        fprintf(stderr, "Bad game-num\nUsage: swrs_extract <game-num (2 or 3)> <dat-file>\n");
        return -1;
    }

    if (rel == 2)
    {
        SR2_DAT dat;
        Athena::io::FileReader datReader(argv[2]);
        dat.read(datReader);
        for (const SR2_DAT::FootEntry& entry : dat.footEntries)
            if (!entry.name.compare("data"))
                parseAudData(entry.common, datReader, "AUDIO_RS2");
    }
    else if (rel == 3)
    {
        SR3_DAT dat;
        Athena::io::FileReader datReader(argv[2]);
        dat.read(datReader);
        for (const SR3_DAT::FootEntry& entry : dat.footEntries)
            if (!entry.name.compare("data"))
                parseAudData(entry.common, datReader, "AUDIO_RS3");
    }

    return 0;
}

