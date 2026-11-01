// g_nBehaviourClassID (Crackdown 2): the next runtime class ID for the AI behaviour classes (the name is ours). CD2
// 0x832B6A4C: their StaticCreateClass functions (cChaseBehaviour's, 0x824CE608, and about 30 more) pass its value to
// the cClass constructor and increment it.
#ifndef AI_BEHAVIOURCLASSID_H
#define AI_BEHAVIOURCLASSID_H

extern int g_nBehaviourClassID;     // 0x832B6A4C

#endif // AI_BEHAVIOURCLASSID_H
