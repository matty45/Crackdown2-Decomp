// Global operator new/delete as CD2's game code sees them: plain XCreateHeapBlock / XDestroyHeapBlock calls, inlined
// at every new/delete. RuffKing's version took a memory type, file and line; CD2 retail has none of that.
// Confirmed byte-exact in CHARACTER/cNPCTintProfile.cpp (MakeNew, scalar deleting destructor).
// They are declared inline here so every source file inlines them, as the original build did.
#ifndef CD2_MEMORY_H
#define CD2_MEMORY_H

#include <stddef.h>

void *XCreateHeapBlock(unsigned int);
void XDestroyHeapBlock(void *);

inline void *operator new(size_t n) { return XCreateHeapBlock(n); }
inline void operator delete(void *p) { XDestroyHeapBlock(p); }

#endif // CD2_MEMORY_H
