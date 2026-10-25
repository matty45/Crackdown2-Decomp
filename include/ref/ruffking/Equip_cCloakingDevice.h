
class Equip::cCloakingDevice : public Equip::cGrenade { /* Size=0xa70 */
  /* 0x0000: fields for Equip::cGrenade */
  public: static const char m_cCloakingDevice_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcCloakingDeviceClass;
  public: static const char* pcCloakingDeviceClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCloakingDevice(const Equip::cCloakingDevice&);
  public: cCloakingDevice(GOM::cObjectPrototype*);
  public: virtual ~cCloakingDevice();
  public: virtual void HandleAttributes(GOM::cObjectPrototype*);
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual bool BeginAttack();
  public: virtual void ProcessAttack();
  public: virtual void EndAttack();
  public: virtual bool CanAttack();
  public: virtual bool ShouldBeForceStored();
  public: virtual bool CanItemUseAmmo() const;
  public: virtual bool IsItemActive() const;
  protected: bool IsCloakAllowed();
  protected: void DeCloak();
  protected: const Equip::cCloakingDevice::cCloakingDevicePrototype* RetCloakPrototype() const;
  public: Equip::cCloakingDevice& operator=(const Equip::cCloakingDevice&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
