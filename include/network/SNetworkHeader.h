// STAND-IN for the nested enum used in cReplicatedClass signatures (RuffKing NetReplicationCD2.h).
// Packet fields are not modelled; no code allocates or accesses a packet through this declaration.
#ifndef CD2_NETWORK_SNETWORKHEADER_H
#define CD2_NETWORK_SNETWORKHEADER_H
struct SNetworkHeader
{
    enum etNetworkDataType { };
};
#endif
