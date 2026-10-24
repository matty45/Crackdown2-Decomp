// Fun_Runtime::cRandGen: linear congruential generator, inline in CD2. Names and layout from the RuffKing PDB.
// NOT YET VERIFIED: no function using it is byte-exact yet (VFX::cAmbientVFXSpawner::CalcRand*,
// GameManagement::cGameModeArena::GetRandSpawnPointInList). Both batch-1 agents saw the same shape independently:
// each Rand clears m_nSeed and steps m_nNext; the seeding constructor stores the seed into both words.
#ifndef FUN_RUNTIME_RANDGEN_H
#define FUN_RUNTIME_RANDGEN_H

namespace Fun_Runtime
{
    class cRandGen
    {
    protected:
        unsigned long m_nNext;
        unsigned int m_nSeed;

    public:
        cRandGen();
        cRandGen(unsigned int seed) : m_nNext(seed), m_nSeed(seed) {}
        ~cRandGen() {}
        unsigned int Rand()
        {
            m_nSeed = 0;
            m_nNext = m_nNext * 1103515245 + 12345;
            return (m_nNext >> 16) & 0x7FFF;
        }
        unsigned int Rand(unsigned int max) { return Rand() % max; }
    };
}

#endif // FUN_RUNTIME_RANDGEN_H
