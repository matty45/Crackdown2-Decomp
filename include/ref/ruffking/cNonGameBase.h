
class cNonGameBase : public ActionIO::cActionIOInterface, public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy, public Fun_Runtime::cSafeDeletable, public Fun_Runtime::cRegisteredClass, public Network::cNetRoleObject { /* Size=0xac */
  /* 0x0000: fields for ActionIO::cActionIOInterface */
  /* 0x0044: fields for RWS::CAttributeHandler */
  /* 0x005c: fields for RWS::CEventHandler */
  /* 0x0080: fields for RWS::DynamicAllocationPolicy */
  /* 0x0060: fields for Fun_Runtime::cSafeDeletable */
  /* 0x0074: fields for Fun_Runtime::cRegisteredClass */
  /* 0x0078: fields for Network::cNetRoleObject */
  /* 0x0080 */ private: cNonGameBase* m_pOwner;
  /* 0x0084 */ private: cNonGameBase* m_pFirstChild;
  /* 0x0088 */ private: cNonGameBase* m_pNextSibling;
  /* 0x008c */ private: AI::Squad* m_pSquad;
  /* 0x0090 */ protected: GOM::cObjectPrototype* m_pPrototype;
  /* 0x0094 */ protected: GOM::cMemoryBlock* m_pPreallocatedBlock;
  /* 0x0098 */ protected: const Fun_Runtime::cClass* m_pPrincipalType;
  /* 0x009c */ protected: Activity::cSpawnPointBase* m_pSpawner;
  /* 0x00a0 */ protected: int m_nUniqueID;
  /* 0x00a4 */ protected: float m_fPriority;
  /* 0x00a8 */ protected: unsigned char m_nAVFlags;
  /* 0x00a9 */ protected: unsigned char m_nGameImportance;
  /* 0x00aa */ protected: unsigned char m_nNGBFlags;
  public: static const char m_cNonGameBase_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcNonGameBaseClass;
  public: static const char* pcNonGameBaseClassID;
  public: static Fun_Runtime::cMap<unsigned int,void (__cdecl cNonGameBase::*)(ActionIO::cActionIOEventData const &),std::less<unsigned int>,Fun_Runtime::cAllocator<std::pair<unsigned int,void (__cdecl cNonGameBase::*)(ActionIO::cActionIOEventData const &)>,3,&cNonGameBase::cNonGameBaseInputMap_FL> > sm_cNonGameBaseInputMap;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void FireInputInternal(unsigned int, const ActionIO::cActionIOEventData&);
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
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal TermForReuse();
  public: GOM::cObjectPrototype* RetPrototypePtr() const;
  public: const char* RetProtoTypeName() const;
  public: virtual const char* RetName();
  public: virtual void SetSpawner(Activity::cSpawnPointBase*);
  public: virtual void SetSquad(AI::Squad*);
  public: void FireOutput(unsigned int, cNonGameBase*);
  public: Activity::cSpawnPointBase* RetSpawner() const;
  public: AI::Squad* RetSquad() const;
  public: const Fun_Runtime::cClass& RetPrincipalTypeClass();
  public: virtual void PreTickUpdate(float);
  public: virtual void TickUpdate(float);
  public: virtual void PostTickUpdate(float);
  public: virtual void PreRenderTick(float);
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
  public: virtual void GetActivityVolumeAttachMtx(Fun_Runtime::Mtx&);
  public: eGameImportance RetGameImportance() const;
  public: virtual void SetGameImportance(eGameImportance);
  public: virtual float RetPriority() const;
  public: void SetPriority(float);
  public: void SetRenderPriority(float);
  public: virtual int RetUniqueID();
  public: void SetUniqueID(int);
  public: void UnuseUniqueID();
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
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cFileLine cNonGameBaseInputMap_FL();
  public: static bool IsAPrototype(const RWS::CAttributePacket&);
};
