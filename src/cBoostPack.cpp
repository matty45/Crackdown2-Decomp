// src/cBoostPack.cpp
//
// Class: cBoostPack (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cBoostPack.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Equip/cGrenade.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "unknown/cBoostPack.h"
#include "unknown/cBoostPackPrototype.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"
#include <new>
#include "rw/rwmem.h"

namespace unknown
{
    RWS::CAttributeHandler *cBoostPack::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBoostPackPrototype(packet);
    }

    const Fun_Runtime::cClass *cBoostPack::ms_pcBoostPackClass = &cBoostPack::StaticCreateClass();

    Fun_Runtime::cClass &cBoostPack::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBoostPackClass = new Fun_Runtime::cClass(0x10141, "cBoostPack", 0x9D0);
        return *cBoostPackClass;
    }

    static RWS::CClassFactory::CRegistrar cBoostPackRegistrar(
        "cBoostPack", cBoostPack::MakeNew, 0x9D0, false);

    // CD2 0x82FCC368: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cBoostPackSpawningRegistrar(
        cBoostPack::StaticCreateClass(), cBoostPack::SpawnFromPrototype);

    // CD2 0x82FCC2B0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cBoostPackcGrenadeInheritRegistrar(
        unknown::cBoostPack::StaticCreateClass(), Equip::cGrenade::StaticCreateClass());

    const char *cBoostPack::RetClassName() const
    {
        return "cBoostPack";
    }

    float cBoostPack::vf427()
    {
        return static_cast<const cBoostPackPrototype *>(m_pPrototype)->m_fField370;
    }

    float cBoostPack::vf428()
    {
        return static_cast<const cBoostPackPrototype *>(m_pPrototype)->m_fField374;
    }

    float cBoostPack::vf430()
    {
        return static_cast<const cBoostPackPrototype *>(m_pPrototype)->m_fField37C;
    }

    bool cBoostPack::vf431()
    {
        return static_cast<const cBoostPackPrototype *>(m_pPrototype)->m_bField380;
    }

    void cBoostPack::vf432(bool b)
    {
        m_bField9C0 = b;
    }

    void cBoostPack::vf434(float f)
    {
        m_fField9C4 = f;
    }

    float cBoostPack::GetField9C4() const
    {
        return m_fField9C4;
    }

    Fun_Runtime::RetVal cBoostPack::Term()
    {
        return Equip::cGrenade::Term();
    }

    bool cBoostPack::vf433()
    {
        bool b = m_bField9C0;
        m_bField9C0 = false;
        return b;
    }

    // CD2 0x8260AED8 has no derived cleanup beyond vtable restoration.
    cBoostPack::~cBoostPack()
    {
    }

    void cBoostPackPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        Equip::cGrenade::cGrenadePrototype::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cBoostPack"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fField374 = value;
                }
                break;
            case 1:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fField378 = value;
                }
                break;
            case 2:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fField37C = value;
                }
                break;
            case 3:
                m_bField380 = rwSwap32(it->GetAs_UInt32()) != 0;
                break;
            }
        }
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cBoostPack> cBoostPackScriptRegistrar(
        "cBoostPack", "cGrenade");

    RWS::CAttributeHandler *cBoostPack::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cBoostPack;
        return 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cBoostPack::RetScriptTypeRegistration() const
    {
        return &cBoostPackScriptRegistrar;
    }
}
