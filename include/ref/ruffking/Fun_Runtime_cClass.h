
class Fun_Runtime::cClass { /* Size=0x5c */
  /* 0x0000 */ private: unsigned int m_nID;
  /* 0x0004 */ private: const char* m_sName;
  /* 0x0008 */ private: unsigned int m_nSize;
  /* 0x000c */ private: Fun_Runtime::cVector<Fun_Runtime::cClass *,Fun_Runtime::cAllocator<Fun_Runtime::cClass *,3,&Fun_Runtime::cClass::ClassList_FL> > m_lParents;
  /* 0x001c */ private: Fun_Runtime::cVector<Fun_Runtime::cClass *,Fun_Runtime::cAllocator<Fun_Runtime::cClass *,3,&Fun_Runtime::cClass::ClassList_FL> > m_lChildren;
  /* 0x002c */ private: bool m_bBitParentsCalced;
  /* 0x002d */ private: unsigned char m_bitIDsForParents[40];
  /* 0x0058 */ private: int m_nBitID;
  private: static int ms_nBitForClass;
  
  public: cClass(const Fun_Runtime::cClass&);
  public: cClass();
  public: cClass(unsigned int, const char*, unsigned int);
  public: unsigned int operator unsigned int() const;
  public: bool operator==(const Fun_Runtime::cClass&) const;
  public: bool operator==(const char*) const;
  public: bool HasAncestor(const Fun_Runtime::cClass&) const;
  public: bool IsA(const Fun_Runtime::cClass&) const;
  public: unsigned int RetSize() const;
  public: unsigned int RetMaxChildSize() const;
  public: const char* RetName() const;
  public: const Fun_Runtime::cVector<Fun_Runtime::cClass *,Fun_Runtime::cAllocator<Fun_Runtime::cClass *,3,&Fun_Runtime::cClass::ClassList_FL> >& RetChildren() const;
  public: const Fun_Runtime::cVector<Fun_Runtime::cClass *,Fun_Runtime::cAllocator<Fun_Runtime::cClass *,3,&Fun_Runtime::cClass::ClassList_FL> >& RetParents() const;
  private: void RecursivelyAddParent(const Fun_Runtime::cClass&);
  public: ~cClass();
  public: Fun_Runtime::cClass& operator=(const Fun_Runtime::cClass&);
  public: void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cFileLine ClassList_FL();
  private: static int GetNextBitForClass();
};
