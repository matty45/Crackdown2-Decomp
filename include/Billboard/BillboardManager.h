// STAND-IN prefix for the resource lookup. RuffKing names m_BillboardMap and the
// singleton. CD2 HandleAttributes uses the map at +0x38, with its end node at +0x3C.
#ifndef BILLBOARD_BILLBOARDMANAGER_H
#define BILLBOARD_BILLBOARDMANAGER_H
#include "rws/eventhandler.h"
#include "rws/attributes.h"
#include "fun_runtime/allocator.h"
#include <map>
namespace RWS { class CResource; }
namespace Billboard
{
    class BillboardManager : public RWS::CEventHandler
    {
        unsigned char m_unmodelled4[0x38 - 4];
        typedef std::map<RWS::RWSGUID, RWS::CResource *, std::less<RWS::RWSGUID>,
            Fun_Runtime::cAllocator<std::pair<const RWS::RWSGUID, RWS::CResource *> > > ResourceMap;
        ResourceMap m_BillboardMap;
    public:
        RWS::CResource *FindBillboardResource(const RWS::RWSGUID &guid)
        {
            ResourceMap::iterator it = m_BillboardMap.find(guid);
            if (it != m_BillboardMap.end())
                return it->second;
            return 0;
        }
        CD2_LAYOUT_CHECKS(BillboardManager,
            CD2_OFFSET(BillboardManager, m_BillboardMap, 0x38))
    };
    extern BillboardManager *g_pBillboardManager;
}
#endif
