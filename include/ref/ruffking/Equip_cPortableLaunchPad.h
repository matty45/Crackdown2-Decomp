
class Equip::cPortableLaunchPad : public Equip::cCWSatchelCharge { /* Size=0xc90 */
  /* 0x0000: fields for Equip::cCWSatchelCharge */
  /* 0x0b80 */ private: Fun_Runtime::cSafeDeletablePointer<Equip::cPortableLaunchPad> m_pTarget;
  /* 0x0b90 */ private: unsigned int m_nReplicatedTargetID;
  /* 0x0ba0 */ private: PHYSICS::cLaunchPad m_LaunchPad;
  public: static const char m_cPortableLaunchPad_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcPortableLaunchPadClass;
  public: static const char* pcPortableLaunchPadClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPortableLaunchPad(const Equip::cPortableLaunchPad&);
  public: cPortableLaunchPad(GOM::cObjectPrototype*);
  public: void SetTargetPad(Equip::cPortableLaunchPad*);
  public: Equip::cPortableLaunchPad* RetTargetPad();
  protected: virtual Fun_Runtime::RetVal Term();
  protected: virtual void NowStuck();
  protected: virtual void TickUpdate(float);
  protected: virtual void NotifyTracked(Equip::cEquipment*);
  protected: virtual void OnAttachedToObject(Equip::cSatchelChargeTarget*, const Fun_Runtime::Mtx&);
  protected: void RenderDebugJumpPad();
  protected: void RenderDebugChevron(const Fun_Runtime::Mtx&, unsigned char, unsigned char, unsigned char, Fun_Runtime::Vec3);
  protected: virtual void ReplicateInitialFields();
  protected: virtual void ReplicateFields();
  protected: void ProxyFixupTarget();
  protected: void UpdateReplicatedTargetID();
  public: virtual ~cPortableLaunchPad();
  public: Equip::cPortableLaunchPad& operator=(const Equip::cPortableLaunchPad&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
