// GameManagement::cArenaCameraContainer: the camera markers of an arena. Member name and type from RuffKing
// (Fun_Runtime::cVector of Cam::cCameraMarker pointers at 0x18; 0x28 bytes, the size CD2's registrar gives).
// CD2's MakeNew (0x8284DB50) inlines the constructor; the destructor (0x8284DBD0) is out of line and frees the vector.
#ifndef GameManagement_cArenaCameraContainer_H
#define GameManagement_cArenaCameraContainer_H

#include "rws/attributes.h"
#include "fun_runtime/vector.h"
#include "cd2/layout.h"

namespace Cam { class cCameraMarker; }

namespace GameManagement
{
    class cArenaCameraContainer : public RWS::CAttributeHandler
    {
    public:
        cArenaCameraContainer(const RWS::CAttributePacket &) {}
        virtual ~cArenaCameraContainer();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    protected:
        Fun_Runtime::cVector<Cam::cCameraMarker *> m_vCameraMarkers; // 0x18

        CD2_LAYOUT_CHECKS(cArenaCameraContainer,
            CD2_SIZE(cArenaCameraContainer, 0x28)
            CD2_OFFSET(cArenaCameraContainer, m_vCameraMarkers, 0x18))
    };
}

#endif
