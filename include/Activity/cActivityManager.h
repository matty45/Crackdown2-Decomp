// STAND-IN for the deletion interface only. Names from RuffKing's
// ActivityManager/cActivityManager.h and .cpp; CD2 0x823CC5D8 queues a safe
// pointer for deletion. CD2 singleton creation is 0x822C4D18 and its pointer
// is read by cGasCanister::NotifyDetonation (0x82743D58).
#ifndef ACTIVITY_CACTIVITYMANAGER_H
#define ACTIVITY_CACTIVITYMANAGER_H

class cNonGameBase;
namespace Activity
{
    class cActivityManager;
    extern cActivityManager *g_pActivityManager;

    class cActivityManager
    {
    public:
        static cActivityManager &CreateActivityManager();
        static cActivityManager &RetActivityManager()
        {
            if (!g_pActivityManager)
                CreateActivityManager();
            return *g_pActivityManager;
        }
        bool RequestDelete(cNonGameBase *);
    };
}

#endif
