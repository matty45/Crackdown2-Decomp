
class GameManagement::cCHordeCaptureProfile : public RWS::CAttributeHandler { /* Size=0x48 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: Editor::cGUIDEventHandler<GameManagement::cCHordeCaptureProfile> m_EventHandler;
  /* 0x002c */ public: float m_fIncreaseDelay;
  /* 0x0030 */ public: float m_fIncreaseRate;
  /* 0x0034 */ public: float m_fDecreaseDelay;
  /* 0x0038 */ public: float m_fDecreaseRate;
  /* 0x003c */ public: int m_nActiveVFXID;
  /* 0x0040 */ public: int m_nCapturingVFXID;
  /* 0x0044 */ public: int m_nCompleteVFXID;
  public: static const char* pcCHordeCaptureProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCHordeCaptureProfile(const GameManagement::cCHordeCaptureProfile&);
  public: cCHordeCaptureProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cCHordeCaptureProfile();
  public: GameManagement::cCHordeCaptureProfile& operator=(const GameManagement::cCHordeCaptureProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
