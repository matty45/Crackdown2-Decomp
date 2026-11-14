// Network debug switches. Burn defines both in Network/netcrackdown.cpp (RuffKing: g_EnableNewVehicleInterp in
// Core/SystemDebugCommands.cpp, g_CullVehicleInterpOnCollision in Vehicle/cvehicle.cpp); CD2 toggles them from the
// adjacent functions 0x825D9598 and 0x825D95F0. cVehicle's UpdateNetworkInterpolation (0x826DC888) passes the first
// (CD2 0x83800B34) to cNetDynamicBody's, and EndInterpolationOptional (0x826DAA40) tests the second (0x83800E06).
#ifndef NETWORK_NETCRACKDOWN_H
#define NETWORK_NETCRACKDOWN_H
extern bool g_EnableNewVehicleInterp;
extern bool g_CullVehicleInterpOnCollision;
#endif
