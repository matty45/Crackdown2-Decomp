
class Equip::cHWGrenadeProjectile : public Equip::cHWProjectile { /* Size=0xae0 */
  /* 0x0000: fields for Equip::cHWProjectile */
  /* 0x0980 */ protected: Audio::cPhysicsBodyGameObject m_GrenadePhysicsAudio;
  /* 0x0ad0 */ private: float m_fLastGrenadeSoundTime;
  /* 0x0ad4 */ private: bool m_bMadeContact;
  public: static const char m_cHWGrenadeProjectile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcHWGrenadeProjectileClass;
  public: static const char* pcHWGrenadeProjectileClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cHWGrenadeProjectile(const Equip::cHWGrenadeProjectile&);
  protected: cHWGrenadeProjectile(GOM::cObjectPrototype*);
  protected: virtual ~cHWGrenadeProjectile();
  protected: virtual void HandleAttributes(GOM::cObjectPrototype*);
  protected: Fun_Runtime::Vec3 CalculateLaunchVelocity(const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&, float, float, float);
  protected: virtual bool HasExploded();
  protected: virtual bool IsLive();
  protected: virtual void EventCollision(PHYSICS::cBody*, const hkContactPoint*);
  protected: virtual void EventCollision(PHYSICS::cBody*, const PHYSICS::cCustomMaterial&, const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&);
  protected: virtual void UpdateExplosionTimer(float);
  protected: virtual int SetupCollisionFilter();
  protected: virtual void ImpactAudio(float);
  protected: virtual int RetNetworkLOD(CHARACTER::cCharacter*, int);
  public: virtual void Launch(float, const Fun_Runtime::Vec3&, float);
  public: float RetLobHeight() const;
  public: float RetMinDistance() const;
  public: float RetMaxDistance() const;
  public: int RetDetonationDelay() const;
  public: float RetGrenadeSoundVolume() const;
  public: Equip::cHWGrenadeProjectile& operator=(const Equip::cHWGrenadeProjectile&);
  protected: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
