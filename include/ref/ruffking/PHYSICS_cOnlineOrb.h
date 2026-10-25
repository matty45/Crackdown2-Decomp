
class PHYSICS::cOnlineOrb : public PHYSICS::cPickupBase { /* Size=0x160 */
  /* 0x0000: fields for PHYSICS::cPickupBase */
  /* 0x0140 */ protected: Fun_Runtime::Vec3 m_vBobOffset;
  /* 0x0150 */ protected: float m_fRequiredPlayerDistance;
  /* 0x0154 */ protected: float m_fBobTimer;
  /* 0x0158 */ protected: unsigned char m_nNumPlayersToCollect;
  /* 0x0159 */ protected: unsigned char m_nCurrentNumPlayers;
  public: static const char m_cOnlineOrb_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcOnlineOrbClass;
  public: static const char* pcOnlineOrbClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cOnlineOrb(const PHYSICS::cOnlineOrb&);
  public: cOnlineOrb();
  public: cOnlineOrb(const RWS::CAttributePacket&);
  public: virtual ~cOnlineOrb();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void GetVFXData(int&, float&, float&);
  public: virtual bool CanAutoPickup() const;
  public: virtual void GetLocPickupString(Fun_Runtime::cString&, bool&) const;
  public: virtual void Use(PLAYER::cPlayer*);
  public: virtual void Collect(PLAYER::cPlayer*);
  public: virtual void SetActive(bool);
  public: PHYSICS::cOnlineOrb& operator=(const PHYSICS::cOnlineOrb&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
