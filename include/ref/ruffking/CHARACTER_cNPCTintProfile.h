
class CAttributeTableEntry;
class RWS::RWSGUID;
class RWS::CAttributeDataChunk;
class RWS::CAttributeHandler;
class RWS::CAttributePacket;
class Editor::cGUIDLinkerBase;
class Editor::cGUIDEventHandlerBase;
class CHARACTER::cNPCTintProfile;
class Editor::cGUIDEventHandler<CHARACTER::cNPCTintProfile>;

class RWS::RWSGUID { /* Size=0x10 */
  /* 0x0000 */ public: unsigned int m_Data[4];
  
  public: void Clear();
  public: bool operator==(const RWS::RWSGUID&) const;
  public: RWS::RWSGUID& operator=(const RWS::RWSGUID&);
  public: bool operator!=(const RWS::RWSGUID&) const;
  public: bool operator<(const RWS::RWSGUID&) const;
};

class Editor::cGUIDLinkerBase { /* Size=0x4 */
  
  protected: virtual ~cGUIDLinkerBase();
  protected: void* FindEntityInMap(const RWS::RWSGUID&);
  public: cGUIDLinkerBase(const Editor::cGUIDLinkerBase&);
  public: cGUIDLinkerBase();
  public: Editor::cGUIDLinkerBase& operator=(const Editor::cGUIDLinkerBase&);
  public: void __local_vftable_ctor_closure();
  protected: virtual void* __vecDelDtor(unsigned int);
};

class Editor::cGUIDEventHandlerBase : public Editor::cGUIDLinkerBase { /* Size=0x14 */
  /* 0x0000: fields for Editor::cGUIDLinkerBase */
  /* 0x0004 */ private: RWS::RWSGUID m_GUID;
  
  public: cGUIDEventHandlerBase(const Editor::cGUIDEventHandlerBase&);
  protected: cGUIDEventHandlerBase();
  protected: virtual ~cGUIDEventHandlerBase();
  protected: void AddEntityToMap(const RWS::RWSGUID&, void*);
  public: Editor::cGUIDEventHandlerBase& operator=(const Editor::cGUIDEventHandlerBase&);
  public: void __local_vftable_ctor_closure();
  protected: virtual void* __vecDelDtor(unsigned int);
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

struct _XMCOLOR { /* Size=0x4 */
  union {
    struct {
      /* 0x0000 */ public: unsigned int b : 8; /* BitPos=0 */
      /* 0x0000 */ public: unsigned int g : 8; /* BitPos=8 */
      /* 0x0000 */ public: unsigned int r : 8; /* BitPos=16 */
      /* 0x0000 */ public: unsigned int a : 8; /* BitPos=24 */
    };
    /* 0x0000 */ public: unsigned int c;
  };
};

class Editor::cGUIDEventHandler<CHARACTER::cNPCTintProfile> : public Editor::cGUIDEventHandlerBase { /* Size=0x14 */
  /* 0x0000: fields for Editor::cGUIDEventHandlerBase */
  
  public: void Register(CHARACTER::cNPCTintProfile*, RWS::RWSGUID);
  public: cGUIDEventHandler<CHARACTER::cNPCTintProfile>(const Editor::cGUIDEventHandler<CHARACTER::cNPCTintProfile>&);
  public: cGUIDEventHandler<CHARACTER::cNPCTintProfile>();
  public: virtual ~cGUIDEventHandler<CHARACTER::cNPCTintProfile>();
  public: Editor::cGUIDEventHandler<CHARACTER::cNPCTintProfile>& operator=(const Editor::cGUIDEventHandler<CHARACTER::cNPCTintProfile>&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
};

class CHARACTER::cNPCTintProfile : public RWS::CAttributeHandler { /* Size=0x50 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: Editor::cGUIDEventHandler<CHARACTER::cNPCTintProfile> m_EventHandler;
  /* 0x002c */ private: _XMCOLOR m_anPalette[8];
  /* 0x004c */ private: unsigned char m_nPaletteSize;
  private: static const unsigned char nPALETTE_CAPACITY;
  public: static const char* pcNPCTintProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cNPCTintProfile(const CHARACTER::cNPCTintProfile&);
  public: cNPCTintProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: _XMCOLOR CalcTintColour(unsigned int) const;
  public: unsigned char RetNumTints() const;
  public: _XMCOLOR RetTintColour(unsigned char) const;
  public: virtual ~cNPCTintProfile();
  public: CHARACTER::cNPCTintProfile& operator=(const CHARACTER::cNPCTintProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
