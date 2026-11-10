// Input action IDs (Burn: Input/InputInitialisation.cpp defines `__int32 GA_*` globals). CD2's input initialisation
// (0x8267E7F8) registers each action by its key and display names and stores the ID: 0x8377AB20 is
// "character_objectinteract" / "Object Interact", 0x8377AB1C "character_objectdrop" / "Object Drop".
// Only the IDs used by matched code are declared.
#ifndef INPUT_INPUTINITIALISATION_H
#define INPUT_INPUTINITIALISATION_H

extern int GA_CHARACTER_OBJECTINTERACT;
extern int GA_CHARACTER_OBJECTDROP;

#endif // INPUT_INPUTINITIALISATION_H
