
class Fun_Runtime::cSafeDeletable { /* Size=0x14 */
  /* 0x0004 */ public: Fun_Runtime::cSafeDeletablePointerBase m_SafeDeletablePointerListHead;
  
  public: cSafeDeletable(const Fun_Runtime::cSafeDeletable&);
  public: cSafeDeletable();
  public: virtual ~cSafeDeletable();
  public: void NullifySafeDeletablePointers();
  public: Fun_Runtime::cSafeDeletable& operator=(const Fun_Runtime::cSafeDeletable&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
};
