
class GameManagement::cCHordeArena : public GameManagement::cGameModeArena { /* Size=0xfc */
  /* 0x0000: fields for GameManagement::cGameModeArena */
  /* 0x00f8 */ private: GameManagement::cCHordeProfile* m_pProfile;
  public: static const char* pcCHordeArenaClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCHordeArena(const GameManagement::cCHordeArena&);
  public: cCHordeArena(const RWS::CAttributePacket&);
  public: virtual bool IsCHordeArena() const;
  public: void SetProfile(GameManagement::cCHordeProfile*);
  public: GameManagement::cCHordeProfile* RetProfile() const;
  public: virtual ~cCHordeArena();
  public: GameManagement::cCHordeArena& operator=(const GameManagement::cCHordeArena&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
