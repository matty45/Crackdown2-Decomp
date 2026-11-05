// RWS::CSystemCommands: empty command-name mixin in the RuffKing header.
// CD2's cBasePatrolRouteEvent has the same base order and no data in this base.
#ifndef RWS_SYSTEMCOMMANDS_H
#define RWS_SYSTEMCOMMANDS_H

namespace RWS
{
    class CSystemCommands
    {
    public:
        static const char *pCSystemCommandsClassID;
        enum LoadParameterTypes
        {
            CMD_AttachResource = 0,
            CMD_LoadMatrix = 1
        };
    };
}

#endif
