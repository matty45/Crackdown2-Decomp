// Crackdown 2 (Xbox 360, title update build) - byte-exact match
// Target : 0x822F33C8, 156 bytes
// Author : Haiku 5.5 (agent pilot P4), 7 harness runs
// Notes  : Lazily created static class object for Equip::cCloakingDevice (RuffKing's counterpart, StaticCreateClass, was rewritten later). Needed the static-guard shape and a single store through a local result.
// Types below are minimal stand-ins written for this one function, not real headers.
// Verify : py -I verify.py <path to extracted default.exe>

extern unsigned int g_cloakInitFlags;
extern void* g_cloakingDevice;

extern void* XCreateHeapBlock(unsigned int size);
extern void* sub_8264A890(void* heap, unsigned int flags, const char* name, unsigned int size);

void* GetCloakingDevice()
{
    if ((g_cloakInitFlags & 1) == 0) {
        g_cloakInitFlags |= 1;
        void* v0 = XCreateHeapBlock(92);
        void* result;
        if (v0 != 0) {
            result = sub_8264A890(v0, 65856, "cCloakingDevice", 2496);
        } else {
            result = 0;
        }
        g_cloakingDevice = result;
        return result;
    }
    return g_cloakingDevice;
}

