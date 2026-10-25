
class Vehicle::cAgencySUV : public Vehicle::cAgencyCar { /* Size=0x2fc0 */
  /* 0x0000: fields for Vehicle::cAgencyCar */
  /* 0x2fb0 */ private: float m_fChargeTimer;
  /* 0x2fb4 */ private: unsigned char m_nASUVFlags;
  private: static const unsigned char nNUM_ASUV_FLAG_BITS;
  public: static const char m_cAgencySUV_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAgencySUVClass;
  public: static const char* pcAgencySUVClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgencySUV(const Vehicle::cAgencySUV&);
  public: cAgencySUV(GOM::cObjectPrototype*);
  public: virtual void TickUpdate(float);
  public: virtual Fun_Runtime::RetVal TermForReuse();
  public: virtual void ApplyCollisionDamageEffect(Damage::cDamage&);
  protected: void HandleJump(float);
  protected: void SetASUVFlags(unsigned char);
  protected: virtual unsigned int GetMaxReplicatedFields() const;
  protected: virtual void ReplicateInitialFields();
  protected: virtual void ReplicateFields();
  public: virtual ~cAgencySUV();
  public: Vehicle::cAgencySUV& operator=(const Vehicle::cAgencySUV&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
