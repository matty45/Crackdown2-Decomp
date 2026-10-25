
class GangManager::cPedestrainDataPrototype : public RWS::CAttributeHandler { /* Size=0x44 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ public: GOM::cObjectPrototype* m_pPrototype;
  /* 0x001c */ public: int m_nMinLevel;
  /* 0x0020 */ public: int m_nMaxLevel;
  /* 0x0024 */ public: float m_fProbability;
  /* 0x0028 */ public: bool m_bEnforcer;
  /* 0x002c */ public: int m_nGangStorageIndex;
  /* 0x0030 */ public: Editor::cGUIDEventHandler<GangManager::cPedestrainDataPrototype> m_EventHandler;
  public: static const char* pcPedestrainDataPrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPedestrainDataPrototype(const GangManager::cPedestrainDataPrototype&);
  public: cPedestrainDataPrototype(const RWS::CAttributePacket&);
  public: virtual ~cPedestrainDataPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: int GetGangStorageIndex();
  public: void SetGangStorageIndex(int);
  public: GangManager::cPedestrainDataPrototype& operator=(const GangManager::cPedestrainDataPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
