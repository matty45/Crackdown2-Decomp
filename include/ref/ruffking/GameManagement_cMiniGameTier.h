
class GameManagement::cMiniGameTier : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x64 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ private: Fun_Runtime::cList<GameManagement::cGameModeStartZone *,Fun_Runtime::cAllocator<GameManagement::cGameModeStartZone *,3,&GameManagement::cMiniGameTier::tMiniGameList_FL> > m_lMiniGames;
  /* 0x0024 */ private: Fun_Runtime::cStringc m_sName;
  /* 0x0040 */ private: unsigned int m_nTierID;
  /* 0x0044 */ private: unsigned int m_nTierIndex;
  /* 0x0048 */ private: bool m_bUnlocked;
  /* 0x0049 */ private: bool m_bComplete;
  /* 0x004c */ private: GameManagement::cMiniGameTier* m_pNextTier;
  /* 0x0050 */ private: Editor::cGUIDEventHandler<GameManagement::cMiniGameTier> m_EventHandler;
  public: static const char* pcMiniGameTierClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cMiniGameTier(const GameManagement::cMiniGameTier&);
  public: cMiniGameTier(const RWS::CAttributePacket&);
  public: virtual ~cMiniGameTier();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void AddMiniGame(GameManagement::cGameModeStartZone*);
  public: void Unlock();
  public: void UpdateCompletionStatus();
  public: bool IsUnlocked() const;
  public: bool IsComplete() const;
  public: const char* RetName() const;
  public: unsigned int RetTierID() const;
  public: unsigned int RetTierIndex() const;
  public: void SetNextTier(GameManagement::cMiniGameTier*);
  public: GameManagement::cMiniGameTier* RetNextTier() const;
  public: unsigned int RetNumMiniGames() const;
  public: GameManagement::cGameModeStartZone* RetMiniGame(unsigned int) const;
  protected: void SetTierID(unsigned int);
  public: GameManagement::cMiniGameTier& operator=(const GameManagement::cMiniGameTier&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  private: static Fun_Runtime::cFileLine tMiniGameList_FL();
};
