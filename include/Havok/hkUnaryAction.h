// Havok unary action: reference-named entity pointer follows the complete hkAction base.
#ifndef HAVOK_HKUNARYACTION_H
#define HAVOK_HKUNARYACTION_H
#include "Havok/hkAction.h"
class hkUnaryAction : public hkAction
{
public:
    virtual ~hkUnaryAction();
    virtual void getEntities(hkArray<hkEntity *> &);
    virtual void entityRemovedCallback(hkEntity *);
protected:
    hkEntity *m_entity;
    CD2_LAYOUT_CHECKS(hkUnaryAction,
        CD2_SIZE(hkUnaryAction, 0x1C)
        CD2_OFFSET(hkUnaryAction, m_entity, 0x18))
};
#endif
