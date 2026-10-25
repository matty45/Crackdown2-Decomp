
class Equip::cSmokeGrenade : public Equip::cGrenade { /* Size=0xa80 */
  /* 0x0000: fields for Equip::cGrenade */
  /* 0x0a70 */ protected: VFX::cParticleEffectInstance* m_pSmokeVFX;
  /* 0x0a74 */ protected: int m_nSmokeTime_msec;
  /* 0x0a78 */ protected: bool m_bDeleteOnDetonationEnd;
  public: static const char m_cSmokeGrenade_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcSmokeGrenadeClass;
  public: static const char* pcSmokeGrenadeClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSmokeGrenade(const Equip::cSmokeGrenade&);
  public: cSmokeGrenade(GOM::cObjectPrototype*);
  public: virtual ~cSmokeGrenade();
  protected: int RetSmokeEffectID() const;
  protected: int RetMaxSmokeTime_msec() const;
  protected: virtual void BeginDetonation();
  protected: virtual void ProcessDetonation();
  protected: virtual void EndDetonation();
  protected: virtual void TickUpdate(float);
  protected: virtual void SetAttachedVFXAlpha(float);
  public: Equip::cSmokeGrenade& operator=(const Equip::cSmokeGrenade&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
