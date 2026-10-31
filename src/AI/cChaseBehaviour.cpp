// AI/cChaseBehaviour.cpp: cChaseBehaviour of Crackdown 2.
// All 28 mapped functions are byte-exact (checked 2026-10-26; config/matched_functions.json).
// Unknown bases and callees are stand-ins named in the header; out-of-line
// callees without a known name are declared as Ext_<address>.
// AI/cChaseBehaviour.cpp: cChaseBehaviour, the vehicle chase behaviour of Crackdown 2 (measurement batch 2, round 2).
#include "AI/cChaseBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

inline void *operator new(size_t, void *p) { return p; }

// Out-of-line functions of other files (unknown names).
void *g_pBehaviourTable;     // global pointer variable at 0x83800988
unsigned int Ext_8243F860(void *, unsigned int);
void Ext_824A8848(void *proto, AI::NPCHost *host);
void Ext_823E97B8(AI::NPCHost *host, int id);
void Ext_823F1610(AI::NPCHost *host, int handle, int flag);
void Ext_8244CF18(AI::NPCRegistry *, AI::TgtSubA *, const AI::TargetInfo &, int);
void Ext_823E9640(AI::NPCHost *, AI::NPCTarget *, int);
void Ext_823F16E8(AI::NPCHost *, void *);
void Ext_823E9738(AI::NPCHost *);
void Ext_8244D038(AI::NPCRegistry *);
unsigned int Ext_8276F1B8(Fun_Runtime::cSafeDeletable *, int, AI::XSub *, void *);

namespace AI
{
    const char *const cChaseBehaviour::pcChaseBehaviourClassID = "cChaseBehaviour";
    Fun_Runtime::cClass *const cChaseBehaviour::ms_pcChaseBehaviourClass = &cChaseBehaviour::StaticCreateClass();

    const char *cChaseBehaviour::RetClassName() const
    {
        return pcChaseBehaviourClassID;
    }

    cChaseBehaviour::cChaseBehaviour() : m_hD0(0), m_nF0(-1), m_bF4(false), m_bF5(false), m_bF6(true)
    {
    }

    RWS::CAttributeHandler *cChaseBehaviour::SpawnFromPrototype(void *, void *mem)
    {
        if (mem)
            return new (mem) cChaseBehaviour;
        return 0;
    }

    void cChaseBehaviour::OnEnter()
    {
        Ext_824A8848(m_pPrototype, m_pHost);
        m_pHost->m_nMode = 0x41;
        Ext_823E97B8(m_pHost, 0xBF);
        m_hD0 = 0;
        SetState(1);
    }

    void cChaseBehaviour::OnExit()
    {
        if (m_hD0)
            m_hD0 = Ext_8243F860(g_pBehaviourTable, m_hD0);
    }

    void cChaseBehaviour::V106()
    {
        Ext_823F1610(m_pHost, m_nF0, 0);
        m_nF0 = -1;
    }

    void cChaseBehaviour::V111(float dt)
    {
        m_fD4 += dt;
        if (m_fD4 > 5.0f)
            SetState(6);
    }

    void cChaseBehaviour::OnEvent74(NPCTarget *t)
    {
        if (m_fTimer <= 0.0001f && !m_bF5)
        {
            SetTarget(t);
            V118();
        }
    }

    void cChaseBehaviour::SetTarget(NPCTarget *t)
    {
        if (t)
        {
            TgtSubA *sub = t;
            NPCRegistry *reg = &m_pHost->m_Registry;
            int id = GetTargetId();
            Ext_8244CF18(reg, sub, sub->GetInfo(), id);
            Ext_823E9640(m_pHost, t, 4);
        }
    }

    bool cChaseBehaviour::TryBindTarget()
    {
        NPCTarget *t = GetTarget();
        if (t && t->IsA(*g_pTargetClass) && t->IsAliveLike())
        {
            SetTarget(t);
            return true;
        }
        return false;
    }

    void cChaseBehaviour::V117()
    {
        SetState(6);
    }

    void cChaseBehaviour::V118()
    {
        if (m_bF4)
            SetState(3);
        else
            SetState(2);
    }

    Fun_Runtime::cClass &cChaseBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cChaseBehaviour_Class =
            new Fun_Runtime::cClass(g_nBehaviourClassID++, "cChaseBehaviour", 0x100);
        return *cChaseBehaviour_Class;
    }

    const Fun_Runtime::cClass &cChaseBehaviour::RetClass() const
    {
        return *ms_pcChaseBehaviourClass;
    }

    bool cChaseBehaviour::IsA(const Fun_Runtime::cClass &test) const
    {
        return ms_pcChaseBehaviourClass->IsA(test);
    }

    void cChaseBehaviour::cChaseBehaviourPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        HandleAttributesBase(packet);
        HandleAttributesNPC(packet);
        for (RWS::CAttributeCommandIterator it(packet, pcChaseBehaviourClassID); !it.IsFinished(); ++it)
        {
        }
    }

    RWS::CAttributeHandler *cChaseBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cChaseBehaviourPrototype(packet);
    }

    static RWS::CClassFactory::CRegistrar cChaseBehaviourRegistrar("cChaseBehaviour", cChaseBehaviour::MakeNew, 0x100, false);

    void cChaseBehaviour::V104()
    {
        Player *player = static_cast<Player *>(m_pHost->m_Links.m_pPlayerSub);
        XSub *xs = player->m_pX;
        X *x = xs ? static_cast<X *>(xs) : 0;
        {
            if (x)
            {
                m_fD4 = 0.0f;
                Ext_823F16E8(m_pHost, &m_vTarget);
                YSub *ys = x->m_pY;
                Y *y = ys ? static_cast<Y *>(ys) : 0;
                {
                    if (y)
                        y->SetV(y->GetV() < 60.0f ? y->GetV() : 60.0f);
                }
            }
        }
    }

    void cChaseBehaviour::V107()
    {
        HostLinks *links = &m_pHost->m_Links;
        Player *player = static_cast<Player *>(links->m_pPlayerSub);
        XSub *xs = player->m_pX;
        X *x = xs ? static_cast<X *>(xs) : 0;
        if (x)
        {
            if (m_hD0 == 0)
            {
                Player *player2 = static_cast<Player *>(links->m_pPlayerSub);
                XSub *xs2 = player2->m_pX;
                X *x2 = xs2 ? static_cast<X *>(xs2) : 0;
                XSub *arg = x2;
                m_hD0 = Ext_8276F1B8(this, 106, arg, g_p830BBDB4);
            }
        }
        else if (m_hD0 != 0)
            m_hD0 = Ext_8243F860(g_pBehaviourTable, m_hD0);
    }

    void cChaseBehaviour::Update(float dt)
    {
        V107();
        if (m_bC4 && !m_pHost->IsAliveLike())
            SetState(0);
        if (m_fTimer > 0.0001f)
        {
            float t = m_fTimer - dt;
            if (t < 0.0001f)
                t = 0.0f;
            m_fTimer = t;
        }
        Player *player = static_cast<Player *>(m_pHost->m_Links.m_pPlayerSub);
        if (!player->m_p1524->O4())
        {
            if (TryBindTarget())
            {
                m_bF5 = true;
                V118();
            }
            else
                m_bF5 = false;
        }
        HostReg *reg = m_pHost->m_Registry.m_pReg;
        if ((int)reg && ((!reg->m_b37 && m_bF6) || reg->m_b38))
        {
            Ext_823E9738(m_pHost);
            Ext_8244D038(&m_pHost->m_Registry);
            m_bF5 = false;
            V117();
        }
    }

    void cChaseBehaviour::V108()
    {
        Player *player = m_pHost->m_Links.RetPlayer();
        if (player->m_p1524->O5())
        {
            V118();
            return;
        }
        player = m_pHost->m_Links.RetPlayer();
        XSub *xs = player->m_pX;
        X *x = xs ? static_cast<X *>(xs) : 0;
        if (x)
        {
            Player *player2 = m_pHost->m_Links.RetPlayer();
            X *x2 = static_cast<X *>(player2->m_pX);
            YSub *ys = x2->m_pY;
            Y *y = ys ? static_cast<Y *>(ys) : 0;
            if (y)
                SetState(6);
        }
    }

    // Pointers to virtual members (the behaviour-state callbacks); taking their address makes the compiler emit the
    // "vcall" thunks F51-F57.
    typedef void (cChaseBehaviour::*StateFn)();
    StateFn g_ChaseStateFns[] =
    {
        &cChaseBehaviour::Slot112, &cChaseBehaviour::Slot105, &cChaseBehaviour::Slot113, &cChaseBehaviour::V106,
        &cChaseBehaviour::Slot110, &cChaseBehaviour::Slot114, &cChaseBehaviour::Slot103
    };
}
