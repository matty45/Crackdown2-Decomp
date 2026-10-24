
class CAttributeTableEntry;
class RWS::RWSGUID;
class RWS::CAttributeDataChunk;
class RWS::CAttributeHandler;
class RWS::CAttributePacket;
class Editor::cGUIDLinkerBase;
class Editor::cGUIDEventHandlerBase;
class GangManager::cFactionConfigData;
class AI::cFactionTargetingProfile;
struct AI::tAIFactionTargetData;
struct AI::tAITargetData;
class Editor::cGUIDEventHandler<AI::cFactionTargetingProfile>;

class RWS::RWSGUID { /* Size=0x10 */
  /* 0x0000 */ public: unsigned int m_Data[4];
  
  public: void Clear();
  public: bool operator==(const RWS::RWSGUID&) const;
  public: RWS::RWSGUID& operator=(const RWS::RWSGUID&);
  public: bool operator!=(const RWS::RWSGUID&) const;
  public: bool operator<(const RWS::RWSGUID&) const;
};

class RWS::DynamicAllocationPolicy { /* Size=0x1 */
  
  public: static bool UseLinearMemory();
};

enum GangManager::eFactions : int {
  FACTION_CIVILIANS = 0x0000,
  FACTION_FREAKS = 0x0001,
  FACTION_AGENCY = 0x0002,
  FACTION_CELL = 0x0003,
  FACTION_AGENT = 0x0004,
  FACTION_AGENT_ROGUE = 0x0005,
  FACTION_NUM = 0x0006,
};

class RWS::CAttributeHandler { /* Size=0x18 */
  /* 0x0004 */ protected: unsigned int m_Flags;
  /* 0x0008 */ protected: RWS::RWSGUID m_InstanceId;
  private: static void (* sm_pNewAttributeHandlerCallBack)();
  
  public: virtual ~CAttributeHandler();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void PropagateAttributes();
  public: virtual CAttributeTableEntry* GetAttributeTable(const char*, unsigned int&, void*&, bool);
  public: virtual void (*GetAttrPostUpdateFunc(void*&))(void*);
  public: void Add(const RWS::RWSGUID&);
  public: void AddToListOnly();
  public: void Lock();
  public: void UnLock();
  public: bool IsLocked();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual bool EnterPhysicalState();
  public: virtual bool EnterRenderableState();
  public: const RWS::RWSGUID* InqInstanceId();
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual bool AllocatedFromFixedPool();
  protected: void RemoveMultipleInstances();
  private: CAttributeHandler(const RWS::CAttributeHandler&);
  protected: CAttributeHandler();
  private: RWS::CAttributeHandler& operator=(const RWS::CAttributeHandler&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static void Remove(const RWS::RWSGUID&);
  public: static RWS::CAttributeHandler* Find(const RWS::RWSGUID&);
  public: static void Purge();
  public: static void PurgeAll();
  public: static void Open(void (*)());
  public: static void Close();
  public: static void RegisterStreamChunkHandlers();
  public: static void UnRegisterStreamChunkHandlers();
  public: static void NewAttributeHandlerCreated();
  protected: static bool IsAPrototype(const RWS::CAttributePacket&);
  protected: static RWS::CAttributeHandler* CreatePrototype(const RWS::CAttributePacket&);
};

class GangManager::cFactionConfigData : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x34 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ public: float m_afLevelTriggers[5];
  /* 0x002c */ public: GangManager::eFactions m_Faction;
  /* 0x0030 */ public: AI::cFactionTargetingProfile* m_pTargetingProfile;
  public: static const char* pcFactionConfigDataClassID;
  public: static const int nNUM_AR_LEVEL_TRIGGERS;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cFactionConfigData(const GangManager::cFactionConfigData&);
  public: cFactionConfigData(const RWS::CAttributePacket&);
  public: virtual ~cFactionConfigData();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GangManager::cFactionConfigData& operator=(const GangManager::cFactionConfigData&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
