/* Auto generated atdna implementation */
#include <Athena/Global.hpp>
#include <Athena/IStreamReader.hpp>
#include <Athena/IStreamWriter.hpp>

#include "DNA_pc.hpp"

void PC_DAT::read(Athena::io::IStreamReader& __dna_reader)
{
    __dna_reader.setEndian(Athena::LittleEndian);
    /* fstOff */
    fstOff = __dna_reader.readUint32();
    /* fstSz */
    fstSz = __dna_reader.readUint32();
    /* seekToFST */
    __dna_reader.seek(fstOff, Athena::Begin);
    /* fileNodes */
    fileNodes.clear();
    fileNodes.reserve(fstSz / 32);
    for (size_t i=0 ; i<(fstSz / 32) ; ++i)
    {
        fileNodes.emplace_back();
        fileNodes.back().read(__dna_reader);
    }
}

void PC_DAT::write(Athena::io::IStreamWriter& __dna_writer) const
{
    __dna_writer.setEndian(Athena::LittleEndian);
    /* fstOff */
    __dna_writer.writeUint32(fstOff);
    /* fstSz */
    __dna_writer.writeUint32(fstSz);
    /* seekToFST */
    __dna_writer.seek(fstOff, Athena::Begin);
    /* fileNodes */
    for (auto elem : fileNodes)
        elem.write(__dna_writer);
}

void PC_DAT::FSTEntry::read(Athena::io::IStreamReader& __dna_reader)
{
    __dna_reader.setEndian(Athena::LittleEndian);
    /* offset */
    offset = __dna_reader.readUint32();
    /* size */
    size = __dna_reader.readUint32();
    /* padding */
    padding = __dna_reader.readUint32();
    /* type */
    type = __dna_reader.readUint16();
    /* childCount */
    childCount = __dna_reader.readUint16();
    /* name */
    name = __dna_reader.readString(16);
}

void PC_DAT::FSTEntry::write(Athena::io::IStreamWriter& __dna_writer) const
{
    __dna_writer.setEndian(Athena::LittleEndian);
    /* offset */
    __dna_writer.writeUint32(offset);
    /* size */
    __dna_writer.writeUint32(size);
    /* padding */
    __dna_writer.writeUint32(padding);
    /* type */
    __dna_writer.writeUint16(type);
    /* childCount */
    __dna_writer.writeUint16(childCount);
    /* name */
    __dna_writer.writeString(name, 16);
}

void PC_SDIREntry::read(Athena::io::IStreamReader& __dna_reader)
{
    __dna_reader.setEndian(Athena::LittleEndian);
    /* soundId */
    soundId = __dna_reader.readUint16();
    /* padding1 */
    padding1 = __dna_reader.readUint16();
    /* audioOffset */
    audioOffset = __dna_reader.readUint32();
    /* sampleRate */
    sampleRate = __dna_reader.readUint16();
    /* padding2 */
    padding2 = __dna_reader.readUByte();
    /* pitch */
    pitch = __dna_reader.readUByte();
    /* numSamples */
    numSamples = __dna_reader.readUint32();
    /* loopStartSample */
    loopStartSample = __dna_reader.readUint32();
    /* loopLengthSamples */
    loopLengthSamples = __dna_reader.readUint32();
}

void PC_SDIREntry::write(Athena::io::IStreamWriter& __dna_writer) const
{
    __dna_writer.setEndian(Athena::LittleEndian);
    /* soundId */
    __dna_writer.writeUint16(soundId);
    /* padding1 */
    __dna_writer.writeUint16(padding1);
    /* audioOffset */
    __dna_writer.writeUint32(audioOffset);
    /* sampleRate */
    __dna_writer.writeUint16(sampleRate);
    /* padding2 */
    __dna_writer.writeUByte(padding2);
    /* pitch */
    __dna_writer.writeUByte(pitch);
    /* numSamples */
    __dna_writer.writeUint32(numSamples);
    /* loopStartSample */
    __dna_writer.writeUint32(loopStartSample);
    /* loopLengthSamples */
    __dna_writer.writeUint32(loopLengthSamples);
}

