/* Auto generated atdna implementation */
#include <Athena/Global.hpp>
#include <Athena/IStreamReader.hpp>
#include <Athena/IStreamWriter.hpp>

#include "DNA_dat.hpp"

void FootEntryCommon::read(Athena::io::IStreamReader& reader)
{
    reader.setEndian(Athena::BigEndian);
    /* offset */
    offset = reader.readUint64();
    /* length */
    length = reader.readUint64();
    /* unknown */
    unknown = reader.readUint64();
    /* loadFlags */
    loadFlags = reader.readUint64();
}

void FootEntryCommon::write(Athena::io::IStreamWriter& writer) const
{
    writer.setEndian(Athena::BigEndian);
    /* offset */
    writer.writeUint64(offset);
    /* length */
    writer.writeUint64(length);
    /* unknown */
    writer.writeUint64(unknown);
    /* loadFlags */
    writer.writeUint64(loadFlags);
}

void SR2_DAT::read(Athena::io::IStreamReader& reader)
{
    reader.setEndian(Athena::BigEndian);
    /* footOff */
    footOff = reader.readUint64();
    /* footSz */
    footSz = reader.readUint64();
    /* footSeek */
    reader.seek(footOff, Athena::Begin);
    /* footEntries */
    footEntries.clear();
    footEntries.reserve(footSz / 64);
    for (size_t i=0 ; i<(footSz / 64) ; ++i)
    {
        footEntries.emplace_back();
        footEntries.back().read(reader);
    }
}

void SR2_DAT::write(Athena::io::IStreamWriter& writer) const
{
    writer.setEndian(Athena::BigEndian);
    /* footOff */
    writer.writeUint64(footOff);
    /* footSz */
    writer.writeUint64(footSz);
    /* footSeek */
    writer.seek(footOff, Athena::Begin);
    /* footEntries */
    for (auto elem : footEntries)
        elem.write(writer);
}

void SR2_DAT::FootEntry::read(Athena::io::IStreamReader& reader)
{
    /* common */
    common.read(reader);
    /* name */
    name = reader.readString(32);
}

void SR2_DAT::FootEntry::write(Athena::io::IStreamWriter& writer) const
{
    /* common */
    common.write(writer);
    /* name */
    writer.writeString(name, 32);
}

void SR3_DAT::read(Athena::io::IStreamReader& reader)
{
    reader.setEndian(Athena::BigEndian);
    /* footOff */
    footOff = reader.readUint64();
    /* footSz */
    footSz = reader.readUint64();
    /* footSeek */
    reader.seek(footOff, Athena::Begin);
    /* footEntries */
    footEntries.clear();
    footEntries.reserve(footSz / 160);
    for (size_t i=0 ; i<(footSz / 160) ; ++i)
    {
        footEntries.emplace_back();
        footEntries.back().read(reader);
    }
}

void SR3_DAT::write(Athena::io::IStreamWriter& writer) const
{
    writer.setEndian(Athena::BigEndian);
    /* footOff */
    writer.writeUint64(footOff);
    /* footSz */
    writer.writeUint64(footSz);
    /* footSeek */
    writer.seek(footOff, Athena::Begin);
    /* footEntries */
    for (auto elem : footEntries)
        elem.write(writer);
}

void SR3_DAT::FootEntry::read(Athena::io::IStreamReader& reader)
{
    /* common */
    common.read(reader);
    /* name */
    name = reader.readString(128);
}

void SR3_DAT::FootEntry::write(Athena::io::IStreamWriter& writer) const
{
    /* common */
    common.write(writer);
    /* name */
    writer.writeString(name, 128);
}

void GroupOffsets::read(Athena::io::IStreamReader& reader)
{
    reader.setEndian(Athena::BigEndian);
    /* count */
    count = reader.readUint32();
    /* elements */
    elements.clear();
    elements.reserve(count);
    for (size_t i=0 ; i<(count) ; ++i)
        elements.push_back(reader.readUint32());
}

void GroupOffsets::write(Athena::io::IStreamWriter& writer) const
{
    writer.setEndian(Athena::BigEndian);
    /* count */
    writer.writeUint32(count);
    /* elements */
    for (auto elem : elements)
        writer.writeUint32(elem);
}

void GroupHead::read(Athena::io::IStreamReader& reader)
{
    reader.setEndian(Athena::BigEndian);
    /* poolOff */
    poolOff = reader.readUint32();
    /* poolLen */
    poolLen = reader.readUint32();
    /* projOff */
    projOff = reader.readUint32();
    /* projLen */
    projLen = reader.readUint32();
    /* sdirOff */
    sdirOff = reader.readUint32();
    /* sdirLen */
    sdirLen = reader.readUint32();
    /* sampOff */
    sampOff = reader.readUint32();
    /* sampLen */
    sampLen = reader.readUint32();
}

void GroupHead::write(Athena::io::IStreamWriter& writer) const
{
    writer.setEndian(Athena::BigEndian);
    /* poolOff */
    writer.writeUint32(poolOff);
    /* poolLen */
    writer.writeUint32(poolLen);
    /* projOff */
    writer.writeUint32(projOff);
    /* projLen */
    writer.writeUint32(projLen);
    /* sdirOff */
    writer.writeUint32(sdirOff);
    /* sdirLen */
    writer.writeUint32(sdirLen);
    /* sampOff */
    writer.writeUint32(sampOff);
    /* sampLen */
    writer.writeUint32(sampLen);
}

void SDirA::read(Athena::io::IStreamReader& reader)
{
    reader.setEndian(Athena::BigEndian);
    /* soundId */
    soundId = reader.readUint16();
    /* padding1 */
    padding1 = reader.readUint16();
    /* audioOffset */
    audioOffset = reader.readUint32();
    /* padding2 */
    padding2 = reader.readUint32();
    /* pitch */
    pitch = reader.readUByte();
    /* padding3 */
    padding3 = reader.readUByte();
    /* sampleRate */
    sampleRate = reader.readUint16();
    /* numSamples */
    numSamples = reader.readUint32();
    /* loopStartSample */
    loopStartSample = reader.readUint32();
    /* loopLengthSamples */
    loopLengthSamples = reader.readUint32();
    /* SDirBOffset */
    SDirBOffset = reader.readUint32();
}

void SDirA::write(Athena::io::IStreamWriter& writer) const
{
    writer.setEndian(Athena::BigEndian);
    /* soundId */
    writer.writeUint16(soundId);
    /* padding1 */
    writer.writeUint16(padding1);
    /* audioOffset */
    writer.writeUint32(audioOffset);
    /* padding2 */
    writer.writeUint32(padding2);
    /* pitch */
    writer.writeUByte(pitch);
    /* padding3 */
    writer.writeUByte(padding3);
    /* sampleRate */
    writer.writeUint16(sampleRate);
    /* numSamples */
    writer.writeUint32(numSamples);
    /* loopStartSample */
    writer.writeUint32(loopStartSample);
    /* loopLengthSamples */
    writer.writeUint32(loopLengthSamples);
    /* SDirBOffset */
    writer.writeUint32(SDirBOffset);
}

void SDirB::read(Athena::io::IStreamReader& reader)
{
    reader.setEndian(Athena::BigEndian);
    /* unknown1 */
    unknown1 = reader.readUint16();
    /* initialPS */
    initialPS = reader.readUByte();
    /* loopPS */
    loopPS = reader.readUByte();
    /* hist1 */
    hist1 = reader.readUint16();
    /* hist2 */
    hist2 = reader.readUint16();
    /* coefs[0] */
    coefs[0] = reader.readUint16();
    /* coefs[1] */
    coefs[1] = reader.readUint16();
    /* coefs[2] */
    coefs[2] = reader.readUint16();
    /* coefs[3] */
    coefs[3] = reader.readUint16();
    /* coefs[4] */
    coefs[4] = reader.readUint16();
    /* coefs[5] */
    coefs[5] = reader.readUint16();
    /* coefs[6] */
    coefs[6] = reader.readUint16();
    /* coefs[7] */
    coefs[7] = reader.readUint16();
    /* coefs[8] */
    coefs[8] = reader.readUint16();
    /* coefs[9] */
    coefs[9] = reader.readUint16();
    /* coefs[10] */
    coefs[10] = reader.readUint16();
    /* coefs[11] */
    coefs[11] = reader.readUint16();
    /* coefs[12] */
    coefs[12] = reader.readUint16();
    /* coefs[13] */
    coefs[13] = reader.readUint16();
    /* coefs[14] */
    coefs[14] = reader.readUint16();
    /* coefs[15] */
    coefs[15] = reader.readUint16();
}

void SDirB::write(Athena::io::IStreamWriter& writer) const
{
    writer.setEndian(Athena::BigEndian);
    /* unknown1 */
    writer.writeUint16(unknown1);
    /* initialPS */
    writer.writeUByte(initialPS);
    /* loopPS */
    writer.writeUByte(loopPS);
    /* hist1 */
    writer.writeUint16(hist1);
    /* hist2 */
    writer.writeUint16(hist2);
    /* coefs[0] */
    writer.writeUint16(coefs[0]);
    /* coefs[1] */
    writer.writeUint16(coefs[1]);
    /* coefs[2] */
    writer.writeUint16(coefs[2]);
    /* coefs[3] */
    writer.writeUint16(coefs[3]);
    /* coefs[4] */
    writer.writeUint16(coefs[4]);
    /* coefs[5] */
    writer.writeUint16(coefs[5]);
    /* coefs[6] */
    writer.writeUint16(coefs[6]);
    /* coefs[7] */
    writer.writeUint16(coefs[7]);
    /* coefs[8] */
    writer.writeUint16(coefs[8]);
    /* coefs[9] */
    writer.writeUint16(coefs[9]);
    /* coefs[10] */
    writer.writeUint16(coefs[10]);
    /* coefs[11] */
    writer.writeUint16(coefs[11]);
    /* coefs[12] */
    writer.writeUint16(coefs[12]);
    /* coefs[13] */
    writer.writeUint16(coefs[13]);
    /* coefs[14] */
    writer.writeUint16(coefs[14]);
    /* coefs[15] */
    writer.writeUint16(coefs[15]);
}

