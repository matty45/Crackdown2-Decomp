
class AI::cBeaconProp : public AI::cMissionCriticalProp, public hkEntityListener { /* Size=0xec0 */
  /* 0x0000: fields for AI::cMissionCriticalProp */
  /* 0x0eb0: fields for hkEntityListener */
  /* 0x0eb4 */ protected: AI::cBeaconMission* m_pBeaconMission;
  public: static const char m_cBeaconProp_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcBeaconPropClass;
  public: static const char* pcBeaconPropClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cBeaconProp(const AI::cBeaconProp&);
  public: cBeaconProp(GOM::cObjectPrototype*);
  public: virtual ~cBeaconProp();
  public: virtual float TakeDamage(Damage::cDamage&);
  public: virtual void PreAddToPhysicsWorld();
  public: virtual void entityAddedCallback(hkEntity*);
  public: void DebugOutputMessage(wchar_t*);
  public: unsigned int GetPropID();
  public: virtual void SetupForBeaconReplication();
  public: virtual void entityRemovedCallback(hkEntity*);
  public: virtual void entityDeletedCallback(hkEntity*);
  public: virtual bool EnterPhysicalState();
  public: void SetBeaconMission(AI::cBeaconMission*);
  public: AI::cBeaconProp& operator=(const AI::cBeaconProp&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
