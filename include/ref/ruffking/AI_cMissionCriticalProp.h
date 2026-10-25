
class AI::cMissionCriticalProp : public Prop::cProp { /* Size=0xeb0 */
  /* 0x0000: fields for Prop::cProp */
  /* 0x0ea0 */ private: bool m_bInteractable;
  public: static const char m_cMissionCriticalProp_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcMissionCriticalPropClass;
  public: static const char* pcMissionCriticalPropClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cMissionCriticalProp(const AI::cMissionCriticalProp&);
  public: cMissionCriticalProp(GOM::cObjectPrototype*);
  public: virtual ~cMissionCriticalProp();
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual float TakeDamage(Damage::cDamage&);
  public: virtual void OnKilled(Damage::cDamage&);
  public: virtual void SetSpawner(Activity::cSpawnPointBase*);
  public: virtual bool IsUsable() const;
  public: virtual bool CanBeginInteraction() const;
  public: virtual void OnReceivedInteractionEvent1();
  public: virtual void OnReceivedInteractionEvent2();
  public: virtual unsigned int RetInteractionAnimID() const;
  public: virtual void OnApproachedByLocalPlayer();
  public: void SetInteractable(bool);
  protected: AI::cMissionCriticalProp::cMissionCriticalPropPrototype* RetMCPPrototype();
  protected: AI::cMissionCriticalPropSpawnPoint* RetMCPSpawner() const;
  public: AI::cMissionCriticalProp& operator=(const AI::cMissionCriticalProp&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
