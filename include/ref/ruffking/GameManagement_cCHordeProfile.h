
class GameManagement::cCHordeProfile : public RWS::CAttributeHandler { /* Size=0x20 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ public: GameManagement::cCHordeWave** m_apWaves;
  /* 0x001c */ public: unsigned int m_nNumWaves;
  public: static const char* pcCHordeProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCHordeProfile(const GameManagement::cCHordeProfile&);
  public: cCHordeProfile(const RWS::CAttributePacket&);
  public: virtual ~cCHordeProfile();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GameManagement::cCHordeProfile& operator=(const GameManagement::cCHordeProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
