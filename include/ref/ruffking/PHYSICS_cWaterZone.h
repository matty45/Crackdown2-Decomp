
class PHYSICS::cWaterZone : public RWS::CSystemCommands, public cNonGameBase { /* Size=0x150 */
  /* 0x00ad: fields for RWS::CSystemCommands */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00b0 */ public: int m_nID;
  /* 0x00b4 */ protected: PHYSICS::cColData* m_pCollisionData;
  /* 0x00b8 */ protected: PHYSICS::cWaterZonePhantom* m_pWaterPhantom;
  /* 0x00bc */ protected: bool m_bIsAntiWater;
  /* 0x00c0 */ protected: Fun_Runtime::Mtx m_Transform;
  /* 0x0100 */ protected: PHYSICS::cOBBox m_OBBox;
  public: static const char m_cWaterZone_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcWaterZoneClass;
  public: static const char* pcWaterZoneClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cWaterZone(const PHYSICS::cWaterZone&);
  public: cWaterZone(const RWS::CAttributePacket&);
  public: virtual ~cWaterZone();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void OnGameObjectEnter(cGameBase*);
  public: virtual void OnGameObjectLeave(cGameBase*);
  public: virtual void TickUpdate(float);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual const PHYSICS::cOBBox* GetOBBox();
  public: bool GetIsAntiWater();
  public: PHYSICS::cWaterZone& operator=(const PHYSICS::cWaterZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
