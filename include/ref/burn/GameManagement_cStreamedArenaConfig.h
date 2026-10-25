
class GameManagement::cStreamedArenaConfig : public RWS::CAttributeHandler { /* Size=0x28 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ public: GameManagement::cGameModeArena* m_pArena;
  /* 0x001c */ public: Fun_Runtime::cList<Activity::cSpawnPoint *,Fun_Runtime::cAllocator<Activity::cSpawnPoint *,39,&GameManagement::cStreamedArenaConfig::tLRPropList_FL> > m_lLRPropSpawners;
  public: static const char* pcStreamedArenaConfigClassID;
  public: static unsigned int _cStreamedArenaConfigClassIDHash;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cStreamedArenaConfig(const GameManagement::cStreamedArenaConfig&);
  public: cStreamedArenaConfig(const RWS::CAttributePacket&);
  public: virtual ~cStreamedArenaConfig();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GameManagement::cStreamedArenaConfig& operator=(const GameManagement::cStreamedArenaConfig&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static unsigned int RetRWSClassNameHash();
  public: static Fun_Runtime::cFileLine tLRPropList_FL();
};
