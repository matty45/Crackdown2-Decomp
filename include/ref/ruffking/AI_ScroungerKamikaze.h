
class AI::ScroungerKamikaze : public AI::Scrounger { /* Size=0x430 */
  /* 0x0000: fields for AI::Scrounger */
  /* 0x0420 */ private: unsigned int m_nFuseTimeout;
  public: static const char* pScroungerKamikazeClassID;
  public: static const char m_ScroungerKamikaze_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pScroungerKamikazeClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: ScroungerKamikaze(const AI::ScroungerKamikaze&);
  public: ScroungerKamikaze(GOM::cObjectPrototype*);
  public: virtual void STATE_Enter_Chasing();
  public: virtual void STATE_Update_Chasing(float);
  public: virtual void STATE_Enter_Alerted();
  public: virtual void STATE_AnimEvent_Detonate(unsigned char, int, short);
  public: virtual void OnTookDamage(AI::cAIEvent*);
  public: virtual void ActiveAgentComplete(unsigned int);
  private: AI::ScroungerKamikaze::ScroungerKamikazePrototype* RetKamikazePrototype() const;
  private: virtual void OnAcidSackHit(CHARACTER::cCharacterInterface*);
  private: virtual void SpawnAcidSackVFX();
  public: virtual ~ScroungerKamikaze();
  public: AI::ScroungerKamikaze& operator=(const AI::ScroungerKamikaze&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
