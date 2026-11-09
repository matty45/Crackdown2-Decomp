// STAND-IN: opaque Havok entity declaration for external calls only. CD2's beacon hook at 0x8245C5C8
// passes its rigid body and entity-listener subobject to addEntityListener (0x82BD1778).
// No object size, fields or virtual interface are asserted here; this type is used only through pointers.
#ifndef HAVOK_HKENTITY_H
#define HAVOK_HKENTITY_H
class hkEntityListener;
class hkEntity
{
public:
    void addEntityListener(hkEntityListener *);
};
#endif
