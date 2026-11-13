// SaveGame::cSaveStream: interface and layout from RuffKing's source object;
// CD2's typed writers share Write_Direct with cVOAZone::Save.
#include "SaveGame/cSaveStream.h"

namespace SaveGame
{
    void cSaveStream::Write(const void *data, unsigned int size)
    {
        if (m_bValid)
        {
            Write_Direct(data, size);
            m_nChunkSize += size;
        }
    }

    void cSaveStream::WriteUInt16(unsigned short value)
    {
        if (m_bValid)
        {
            Write_Direct(&value, sizeof(value));
            m_nChunkSize += sizeof(value);
        }
    }
}
