// STAND-IN: member names and layout from RuffKing's SaveGame/cSaveStream.h.
// CD2 cVOAZone::Save (0x8280EE30) inlines the one-byte writer: validity at
// +0x3C, chunk size at +0x34 and Write_Direct at 0x8231E3C8.
#ifndef SAVEGAME_CSAVESTREAM_H
#define SAVEGAME_CSAVESTREAM_H

#include "fun_runtime/string.h"
#include "SaveGame/save_types.h"
#include "cd2/layout.h"

namespace SaveGame
{
    class cSaveStream
    {
    public:
        void Write(const void *data, unsigned int size);
        void WriteUInt16(unsigned short value);
        void WriteBool(bool value)
        {
            if (m_bValid)
            {
                Write_Direct(&value, sizeof(value));
                m_nChunkSize += sizeof(value);
            }
        }

    private:
        unsigned int m_nVersion;
        Fun_Runtime::cString m_sFilename;
        bool m_bFile;
        unsigned char *m_pBuffer;
        unsigned int m_nBufferSize;
        unsigned int m_nTotalSize;
        eSaveChunk m_CurrentChunk;
        unsigned int m_nChunkSize;
        eSaveType m_nType;
        bool m_bValid;

        void Write_Direct(const void *data, unsigned int size);

        CD2_LAYOUT_CHECKS(cSaveStream,
            CD2_SIZE(cSaveStream, 0x40)
            CD2_OFFSET(cSaveStream, m_sFilename, 0x4)
            CD2_OFFSET(cSaveStream, m_nChunkSize, 0x34)
            CD2_OFFSET(cSaveStream, m_bValid, 0x3C))
    };
}

#endif
