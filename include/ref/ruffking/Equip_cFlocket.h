
class Equip::cFlocket : public Equip::cHWProjectile { /* Size=0x9c0 */
  /* 0x0000: fields for Equip::cHWProjectile */
  /* 0x0980 */ private: Fun_Runtime::Vec3 m_vecTargetPos;
  /* 0x0990 */ private: float m_fFlightTime;
  /* 0x09a0 */ private: Fun_Runtime::Vec3 m_vMovementHint;
  /* 0x09b0 */ private: float m_fVertAcc;
  /* 0x09b4 */ private: float m_fHorizAcc;
  /* 0x09b8 */ private: VFX::cGlobalLight* m_pFlockLight;
  public: static const char m_cFlocket_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcFlocketClass;
  public: static const char* pcFlocketClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: Equip::cFlocket::cFlocketPrototype* RetFlocketPrototype();
  public: cFlocket(const Equip::cFlocket&);
  public: cFlocket(GOM::cObjectPrototype*);
  public: virtual ~cFlocket();
  public: virtual bool EnterRenderableState(eResourcesType);
  public: virtual void TickUpdate(float);
  public: virtual void Launch(float, const Fun_Runtime::Vec3&, float);
  public: virtual void ReplicateInitialFields();
  public: virtual void ReplicateFields();
  public: virtual unsigned int GetMaxReplicatedFields() const;
  protected: void MoveProjectile(const Fun_Runtime::Vec3&, float);
  protected: void CreateFlocketLight();
  protected: void UpdateFlocketLight(float);
  protected: void DestroyFlocketLight();
  protected: virtual void UpdateAttachedEffect(float);
  protected: virtual void ReleaseEffect();
  public: Equip::cFlocket& operator=(const Equip::cFlocket&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
