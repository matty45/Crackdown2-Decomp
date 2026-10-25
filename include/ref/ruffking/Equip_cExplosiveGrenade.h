
class Equip::cExplosiveGrenade : public Equip::cGrenade, public ExplosionManager::cExplosionCallback { /* Size=0xa80 */
  /* 0x0000: fields for Equip::cGrenade */
  /* 0x0a70: fields for ExplosionManager::cExplosionCallback */
  /* 0x0a74 */ protected: ExplosionManager::cExplosive* m_pExplosive;
  /* 0x0a78 */ protected: VFX::cParticleEffectInstance* m_pFuseDelayVFX;
  /* 0x0a7c */ protected: unsigned char m_nOrdinal;
  public: static const char m_cExplosiveGrenade_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcExplosiveGrenadeClass;
  public: static const char* pcExplosiveGrenadeClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cExplosiveGrenade(const Equip::cExplosiveGrenade&);
  public: cExplosiveGrenade(GOM::cObjectPrototype*);
  public: virtual ~cExplosiveGrenade();
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void Launched(cGameBase*);
  public: virtual bool IsTargetAreaClear(CHARACTER::cCharacter*, cGameBase*, const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&) const;
  public: virtual bool IsTargetTooClose(CHARACTER::cCharacter*, cGameBase*, const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&) const;
  public: virtual float RetDamageRadius() const;
  public: virtual void InitiateOrdinalDetonation(unsigned char);
  public: virtual void NotifyDetonation(cGameBase*, CHARACTER::cCharacterInterface*, unsigned char);
  public: virtual void SetLive(bool);
  protected: unsigned char RetExplosiveLevel() const;
  protected: virtual unsigned char RetExplosiveLevelForOwner(const cNonGameBase*) const;
  protected: virtual void SetExplosiveLevel(unsigned int);
  protected: virtual unsigned short RetExplosionSurfaceID() const;
  protected: virtual const Fun_Runtime::Mtx RetExplosiveOrientation() const;
  protected: virtual void BeginDetonation();
  protected: virtual void ProcessDetonation();
  protected: virtual void SetupForDetonation(cGameBase*);
  protected: virtual ExplosionManager::eDetonationType RetDetonationType() const;
  protected: virtual void BeginFuseDelay();
  protected: virtual void UpdateFuseDelay(float);
  protected: virtual void ReplicateInitialFields();
  protected: virtual void ReplicateFields();
  protected: virtual unsigned int GetMaxReplicatedFields() const;
  protected: virtual Fun_Runtime::cString GetNetDebugString();
  public: Equip::cExplosiveGrenade& operator=(const Equip::cExplosiveGrenade&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
