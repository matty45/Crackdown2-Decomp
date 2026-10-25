
class GameManagement::cMultiPlayerTriggerZone : public RWS::CSystemCommands, public RWS::CAttributeHandler { /* Size=0x70 */
  /* 0x0018: fields for RWS::CSystemCommands */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0020 */ protected: Fun_Runtime::Mtx m_mTransform;
  /* 0x0060 */ protected: float m_fRadius;
  /* 0x0064 */ protected: bool m_bActive;
  public: static const char* pcMultiPlayerTriggerZoneClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cMultiPlayerTriggerZone(const GameManagement::cMultiPlayerTriggerZone&);
  public: cMultiPlayerTriggerZone(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void InitTriggerZone();
  public: virtual void TermTriggerZone();
  public: unsigned char RetNumPlayersInZone();
  public: const Fun_Runtime::Mtx& RetTransform() const;
  protected: virtual bool CanTrigger(PLAYER::cPlayer*);
  public: virtual ~cMultiPlayerTriggerZone();
  public: GameManagement::cMultiPlayerTriggerZone& operator=(const GameManagement::cMultiPlayerTriggerZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
