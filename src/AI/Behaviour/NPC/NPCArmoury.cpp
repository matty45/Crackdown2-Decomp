// AI/Behaviour/NPC/NPCArmoury.cpp: RuffKing's Libraries/Shared/AI/Behaviour/NPC/NPCArmoury.cpp.
//
// This object has no code of its own, in CD2 as in RuffKing and Burn. Its one class, cNPCArmourySetup (1 byte: the
// class-ID string "cNPCArmourySetup", a static RetRWSClassName and the CMD_PrimaryWeapon/CMD_SecondaryWeapons command
// IDs), only tags the weapon block of an NPC prototype's editor attributes; NPCBehaviourPrototype's armoury setup
// (CD2 0x82372280, in NPCBehaviour.obj's code) reads that block under the class ID. Every function the object compiles
// to comes from its headers: the initializers of the header constants below (each file that includes them has its own
// copies; nothing here reads them) and gRandGen's at-exit destructor. Both reference PDBs list only those functions
// for NPCArmoury.obj, and CD2 has its initializer run (0x82F916C0..0x82F919B8, its own g_GlobalConstants copy) between
// NPCArmedBehaviour's and NPCBehaviour's. In CD2's .rdata its class-ID string (0x82108BE0) lies between
// NPCArmedBehaviour's tables and NPCBehaviour's name and table, and only the armoury setup uses it (0x82372280 is
// NPCBehaviourPrototype's: it fills mPrimary at +0x70 and mSecondaries at +0x80); its header constants
// (0x8381E778..0x8381E810) are touched only by their own initializers. config/splits.txt gives it an empty text range
// at its place in the link order (docs/matching-notes.md, "An object with no code of its own").

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
