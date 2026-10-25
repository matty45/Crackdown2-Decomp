
class Prop::cExplosiveBarrel : public Prop::cProp { /* Size=0xeb0 */
  /* 0x0000: fields for Prop::cProp */
  /* 0x0ea0 */ private: unsigned int m_nDeleteTime;
  public: static const char m_cExplosiveBarrel_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcExplosiveBarrelClass;
  public: static const char* pcExplosiveBarrelClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cExplosiveBarrel(const Prop::cExplosiveBarrel&);
  public: cExplosiveBarrel(GOM::cObjectPrototype*);
  public: virtual void TickUpdate(float);
  public: virtual void TriggerEnterWater(float);
  public: virtual void EventCollision(PHYSICS::cBody*, const hkContactPoint*);
  public: virtual bool HasHandle() const;
  public: virtual bool CanHaveAttachedSatchelCharge(const Fun_Runtime::Vec3&) const;
  private: void TriggerBarrelFade();
  private: void UpdateBarrelFade();
  private: Prop::cExplosiveBarrelPrototype& RetExBarrelProto() const;
  private: virtual void ReplicateInitialFields();
  private: virtual void ReplicateFields();
  public: virtual ~cExplosiveBarrel();
  public: Prop::cExplosiveBarrel& operator=(const Prop::cExplosiveBarrel&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
