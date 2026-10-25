
class AI::Peacekeeper : public AI::CellGuard { /* Size=0x220 */
  /* 0x0000: fields for AI::CellGuard */
  /* 0x01e0 */ private: VFX::cParticleEffectInstance* m_pRappelRopeVFX;
  /* 0x01f0 */ private: Fun_Runtime::Vec3 m_vCurrentMissionPos;
  /* 0x0200 */ private: Fun_Runtime::Vec3 m_vRappelPos;
  /* 0x0210 */ private: float m_fRappelTime;
  /* 0x0214 */ private: bool m_bCanRapel;
  /* 0x0215 */ private: bool m_bPlayingEncourage;
  /* 0x0216 */ private: bool m_bMidRappel;
  public: static const char* pPeacekeeperClassID;
  public: static const char m_Peacekeeper_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pPeacekeeperClass;
  private: static Fun_Runtime::cRandGen m_sRandomGenerator;
  private: static unsigned int ms_nEncourageTimeStamp;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: Peacekeeper(const AI::Peacekeeper&);
  public: Peacekeeper(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void OnCharacterEvent(unsigned char, unsigned char, unsigned char);
  public: virtual void OnAnimationEvent(unsigned char, int, short);
  public: void Rappel();
  public: virtual void RenderDebugInfo();
  protected: AI::PeacekeeperPrototype& RetPeacekeeperPrototype();
  protected: virtual void DoEnterEncourageAgent();
  protected: virtual void DoUpdateEncourageAgent();
  protected: virtual void DoIdleUpdate(const float);
  protected: virtual void StartRappelling();
  protected: virtual void DoRappelling();
  protected: virtual void DoPostRappelling();
  protected: void SetRappelPoint();
  protected: void UpdateRope();
  protected: virtual void ExitRapelling();
  protected: void StartRappel();
  public: virtual ~Peacekeeper();
  public: AI::Peacekeeper& operator=(const AI::Peacekeeper&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
