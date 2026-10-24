
class Fun_Runtime::cRandGen { /* Size=0x8 */
  /* 0x0000 */ protected: unsigned long m_nNext;
  /* 0x0004 */ protected: unsigned int m_nSeed;
  
  public: ~cRandGen();
  public: cRandGen(unsigned int);
  public: cRandGen();
  public: void Reset();
  public: void Seed(unsigned int);
  public: unsigned int Rand(unsigned int, unsigned int);
  public: unsigned int Rand(unsigned int);
  public: unsigned int Rand();
  public: float FRand(float, float);
  public: float FRand(float);
  public: float FRand();
  public: float FRandx();
  public: bool BRand();
  public: void VRand(Fun_Runtime::Vec3&);
  public: Fun_Runtime::Vec3 RandV();
  public: void* __vecDelDtor(unsigned int);
};
