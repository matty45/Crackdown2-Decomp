// STAND-IN: RuffKing names/layout; CD2 common prop table at +0x7A4.
#ifndef CD2_AI_CDYNAMICOBSTACLEOWNER_H
#define CD2_AI_CDYNAMICOBSTACLEOWNER_H
#include "cd2/layout.h"
namespace AI
{
    class cDynamicObstacle;
    class cDynamicObstacleOwner
    {
    public:
        // RuffKing's non-virtual destructor; CD2's vehicle and prop destructors (0x826CE0E8, 0x82729538) inline it as
        // the table store alone.
        ~cDynamicObstacleOwner() {}
        virtual void CreateDynamicObstacle();
        virtual void DestroyDynamicObstacle();
        virtual void ActivateDynamicObstacle();
        virtual void DeactivateDynamicObstacle();
        virtual unsigned char GetDynamicObstacleInput();
    protected:
        cDynamicObstacle *m_pDynamicObstacle;
        CD2_LAYOUT_CHECKS(cDynamicObstacleOwner, CD2_SIZE(cDynamicObstacleOwner, 8)
            CD2_OFFSET(cDynamicObstacleOwner, m_pDynamicObstacle, 4))
    };
}
#endif
