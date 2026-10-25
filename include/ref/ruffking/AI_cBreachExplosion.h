
class AI::cBreachExplosion : public RWS::CSystemCommands, public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy { /* Size=0x90 */
  /* 0x001c: fields for RWS::CSystemCommands */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001d: fields for RWS::DynamicAllocationPolicy */
  /* 0x001e */ private: unsigned short m_nProfileID;
  /* 0x0020 */ private: bool m_bActive;
  /* 0x0024 */ private: float m_fActivationTimer;
  /* 0x0028 */ private: float m_fCurrentTimer;
  /* 0x002c */ private: unsigned short m_nExplosionLevel;
  /* 0x0030 */ private: Fun_Runtime::Mtx m_mMat;
  /* 0x0070 */ private: Editor::cGUIDEventHandler<AI::cBreachExplosion> m_EventHandler;
  public: static const char m_cBreachExplosion_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcBreachExplosionClass;
  public: static const char* pcBreachExplosionClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cBreachExplosion(const AI::cBreachExplosion&);
  public: cBreachExplosion(const RWS::CAttributePacket&);
  public: virtual ~cBreachExplosion();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleSystemCommands(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: void Activate();
  public: void Deactivate();
  public: bool IsActive();
  public: void TickUpdate();
  public: Fun_Runtime::Mtx RetMatrix() const;
  private: void SetMat(const Fun_Runtime::Mtx&);
  public: AI::cBreachExplosion& operator=(const AI::cBreachExplosion&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
