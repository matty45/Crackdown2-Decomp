
class cNonGameBase : public RWS::CAttributeHandler, public RWS::CEventHandler, public Fun_Runtime::cSafeDeletable, public Fun_Runtime::cRegisteredClass, public Network::cNetRoleObject, public ResourceManager::IResourceStreaming { /* Size=0x60 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c: fields for Fun_Runtime::cSafeDeletable */
  /* 0x0030: fields for Fun_Runtime::cRegisteredClass */
  /* 0x0034: fields for Network::cNetRoleObject */
  /* 0x003c: fields for ResourceManager::IResourceStreaming */
  /* 0x003c */ protected: GOM::cObjectPrototype* m_pPrototype;
  /* 0x0040 */ protected: Activity::cSpawnPointBase* m_pSpawner;
  /* 0x0044 */ protected: int m_nUniqueID;
  /* 0x0048 */ protected: float m_fPriority;
  /* 0x004c */ protected: unsigned char m_nAVFlags;
  /* 0x004d */ protected: unsigned char m_nGameImportance;
  /* 0x004e */ protected: unsigned char m_nNGBFlags;
  /* 0x0050 */ private: cNonGameBase* m_pOwner;
  /* 0x0054 */ private: cNonGameBase* m_pFirstChild;
  /* 0x0058 */ private: cNonGameBase* m_pNextSibling;
  /* 0x005c */ private: AI::Squad* m_pSquad;
  public: static const char m_cNonGameBase_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcNonGameBaseClass;
  public: static const char* pcNonGameBaseClassID;
  public: static unsigned int _cNonGameBaseClassIDHash;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual void Destruct();
  public: cNonGameBase(const cNonGameBase&);
  public: cNonGameBase(GOM::cObjectPrototype*);
  public: cNonGameBase(const RWS::CAttributePacket&);
  public: cNonGameBase();
  public: virtual ~cNonGameBase();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(GOM::cObjectPrototype*);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandlePhysicalResources(GOM::cObjectPrototype*);
  public: virtual bool HandleRenderableResources(GOM::cObjectPrototype*);
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal Term();
  public: GOM::cObjectPrototype* RetPrototype() const;
  public: const char* RetPrototypeName() const;
  public: virtual const char* RetName() const;
  public: virtual void SetSpawner(Activity::cSpawnPointBase*);
  public: virtual void SetSquad(AI::Squad*);
  public: Activity::cSpawnPointBase* RetSpawner() const;
  public: AI::Squad* RetSquad() const;
  public: virtual void PreTickUpdate(float);
  public: virtual void TickUpdate(float);
  public: virtual void PostTickUpdate(float);
  public: virtual void UpdateRenderMatrix();
  public: virtual void RenderPausedDebugInfo();
  public: virtual bool EnterPhysicalState();
  public: virtual void LeavePhysicalState();
  public: bool IsInPhysicalState() const;
  public: virtual bool CanEnterPhysicalState();
  public: virtual bool EnterRenderableState(eResourcesType);
  public: virtual void LeaveRenderableState();
  public: bool IsInRenderableState() const;
  public: virtual bool IsMovingEnoughForDeletion();
  public: virtual unsigned char RetResourceState();
  public: virtual Fun_Runtime::Vec3 RetPosition() const;
  public: virtual bool IsAlive() const;
  public: eGameImportance RetGameImportance() const;
  public: void SetGameImportance(eGameImportance);
  public: float RetPriority() const;
  public: void SetPriority(float);
  public: int RetUniqueID() const;
  public: void SetUniqueID(int);
  public: cNonGameBase* RetOwner() const;
  public: void SetOwner(cNonGameBase*);
  public: cNonGameBase* RetFirstChild() const;
  public: cNonGameBase* RetNextSibling() const;
  public: void SetEnteredAV(unsigned char);
  public: void SetExitedAV(unsigned char);
  public: virtual unsigned char RetAVFlags() const;
  public: virtual bool TestIsWithinRadius(Fun_Runtime::Vec2, float);
  public: void SetNGBFlags(unsigned char);
  public: void ClearNGBFlags(unsigned char);
  public: bool HasNGBFlags(unsigned char) const;
  protected: void ConstructCommon();
  protected: virtual void AutoAssignUniqueID();
  private: void AddChild(cNonGameBase*);
  private: void RemoveChild(cNonGameBase*);
  public: cNonGameBase& operator=(const cNonGameBase&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static unsigned int RetRWSClassNameHash();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static cNonGameBase* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
