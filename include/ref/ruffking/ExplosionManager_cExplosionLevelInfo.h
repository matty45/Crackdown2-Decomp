
class ExplosionManager::cExplosionLevelInfo : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x80 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ private: unsigned int m_nLevel;
  /* 0x001c */ private: float m_fExplosionTime;
  /* 0x0020 */ private: float m_fVFXScale;
  /* 0x0024 */ private: float m_fFreakDeathVFXScale;
  /* 0x0028 */ private: float m_fAcidVFXScale;
  /* 0x002c */ private: float m_fAccumulationRadius;
  /* 0x0030 */ private: float m_fMaxDamage;
  /* 0x0034 */ private: float m_fMinDamage;
  /* 0x0038 */ private: float m_fMaxForce;
  /* 0x003c */ private: float m_fDamageRadius;
  /* 0x0040 */ private: float m_fDecalRadius;
  /* 0x0044 */ private: int m_nExplosionEffectLevel;
  /* 0x0050 */ private: Fun_Runtime::Vec3 m_vDirectionOffset;
  /* 0x0060 */ private: float m_fExplosionSoundVolume;
  /* 0x0064 */ private: int m_nWaterExplosionVFXID;
  /* 0x0068 */ private: int m_nUVExplosionVFXID;
  /* 0x006c */ private: int m_nAcidExplosionVFXID;
  /* 0x0070 */ private: int m_nFreakDeathExplosionVFXID;
  /* 0x0074 */ private: float m_fCameraShakeAmount;
  private: static Fun_Runtime::cVector<PHYSICS::cDynamicBody *,Fun_Runtime::cAllocator<PHYSICS::cDynamicBody *,5,&PHYSICS::cPhysicsUniverse::tBodies_FL> > ms_vBodies;
  public: static const char* pcExplosionLevelInfoClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: cExplosionLevelInfo(const ExplosionManager::cExplosionLevelInfo&);
  public: cExplosionLevelInfo(const RWS::CAttributePacket&);
  public: virtual ~cExplosionLevelInfo();
  public: float RetAccumulationRadius() const;
  public: float RetDamageRadius() const;
  public: float RetExplosionSoundVolume() const;
  public: unsigned int RetLevel();
  public: float RetMaxDamage();
  public: float RetMinDamage();
  public: float RetClearRadius(CHARACTER::cCharacter*, cGameBase*) const;
  public: bool IsTargetAreaClear(CHARACTER::cCharacter*, cGameBase*, const Fun_Runtime::Vec3&) const;
  public: bool IsTargetTooClose(CHARACTER::cCharacter*, cGameBase*, const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&) const;
  public: bool IsInDangerZone(const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&) const;
  public: int RetWaterExplosionVFXID() const;
  public: int RetUVExplosionVFXID() const;
  public: int RetAcidExplosionVFXID() const;
  public: int RetFreakDeathExplosionVFXID() const;
  public: ExplosionManager::cExplosionEffect* CreateExplosionInstance(ExplosionManager::cExplosionEffectManager&, const ExplosionManager::tExplosionData&);
  public: ExplosionManager::cExplosionLevelInfo& operator=(const ExplosionManager::cExplosionLevelInfo&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
