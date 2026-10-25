
class GameManagement::cGameModeVFXProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  public: static const char* pcGameModeVFXProfileClassID;
  protected: static int m_aVFXID[13];
  protected: static float m_fMaxHeightScale;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGameModeVFXProfile(const GameManagement::cGameModeVFXProfile&);
  public: cGameModeVFXProfile(const RWS::CAttributePacket&);
  public: virtual ~cGameModeVFXProfile();
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GameManagement::cGameModeVFXProfile& operator=(const GameManagement::cGameModeVFXProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static int RetVFXID(GameManagement::eGameModeVFX);
  public: static float RetMaxHeightScale();
};
