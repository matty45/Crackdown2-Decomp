#ifndef AUDIO_CWORLDGAMEOBJECTPOSITION_H
#define AUDIO_CWORLDGAMEOBJECTPOSITION_H

#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace Audio
{
    class cWorldGameObject;
    // CD2's table (0x8215A508) has RWS::CAttributeHandler's eleven slots, then RetClass, IsA, RetClassName and Destruct in slots
    // 11 to 14, as Burn declares the class: a CAttributeHandler and RWS::CSystemCommands (RuffKing adds RWS::DynamicAllocationPolicy).
    class cWorldGameObjectPosition : public RWS::CAttributeHandler, public RWS::CSystemCommands
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x83013AD8);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cWorldGameObjectPositionClass = new Fun_Runtime::cClass(0x677, "cWorldGameObjectPosition", 0x50);
            return *cWorldGameObjectPositionClass;
        }
        static const Fun_Runtime::cClass *ms_pcWorldGameObjectPositionClass;

        // CD2 initializes both vectors, then the created flag, world-object pointer and ID.
        __forceinline cWorldGameObjectPosition(const RWS::CAttributePacket &)
            : m_bCreated(false), m_pWorldObject(0), m_nID(-1)
        {
            m_vDirection.y = 1.0f;
        }
        virtual ~cWorldGameObjectPosition() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        // CD2: cWorldGameObjectPosition's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82838028
    private:
        // Names and types from Burn/RuffKing; CD2 factory stores confirm each offset.
        Fun_Runtime::Vec3 m_vPosition;
        Fun_Runtime::Vec3 m_vDirection;
        bool m_bCreated;
        cWorldGameObject *m_pWorldObject;
        int m_nID;
        CD2_LAYOUT_CHECKS(cWorldGameObjectPosition,
            CD2_SIZE(cWorldGameObjectPosition, 0x50)
            CD2_OFFSET(cWorldGameObjectPosition, m_vPosition, 0x20)
            CD2_OFFSET(cWorldGameObjectPosition, m_vDirection, 0x30)
            CD2_OFFSET(cWorldGameObjectPosition, m_bCreated, 0x40)
            CD2_OFFSET(cWorldGameObjectPosition, m_pWorldObject, 0x44)
            CD2_OFFSET(cWorldGameObjectPosition, m_nID, 0x48))
    };
}

#endif

