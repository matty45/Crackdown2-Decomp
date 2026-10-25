
class WorldManager::cStaticEnvironment : public PHYSICS::cStaticBody, public ResourceManager::cStreamingResourceClient, public WorldManager::cFadeInOutInterface { /* Size=0x320 */
  /* 0x0000: fields for PHYSICS::cStaticBody */
  /* 0x02a0: fields for ResourceManager::cStreamingResourceClient */
  /* 0x02ac: fields for WorldManager::cFadeInOutInterface */
  /* 0x02c4 */ public: bool m_bDebugInitialised;
  /* 0x02c5 */ public: bool m_bRenderable;
  /* 0x02c6 */ public: bool m_bBlockIsDisabled;
  /* 0x02c7 */ public: bool m_bInActiveRenderRegion;
  /* 0x02c8 */ public: unsigned char m_nResourceState;
  /* 0x02cc */ public: const char* m_sEnvBlockName;
  /* 0x02d0 */ public: Fun_Runtime::cSafeDeletablePointer<RWS::CResource> m_apResources[4];
  /* 0x0310 */ public: GameRenderer::cClumpInfo* m_pClumpInfo;
  /* 0x0314 */ public: hkAabbPhantom* m_pAABBPhantom;
  public: static const char m_cStaticEnvironment_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcStaticEnvironmentClass;
  public: static const char* pcStaticEnvironmentClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cStaticEnvironment(const WorldManager::cStaticEnvironment&);
  public: cStaticEnvironment(const RWS::CAttributePacket&);
  public: virtual ~cStaticEnvironment();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void FindCollisionResource(GOM::cObjectPrototype*);
  public: virtual void TickUpdate(float);
  public: virtual bool EnterRenderableState(eResourcesType);
  public: virtual bool EnterPhysicalState();
  public: virtual void LeaveRenderableState();
  public: virtual void LeavePhysicalState();
  public: virtual Fun_Runtime::RetVal InitClump();
  public: virtual void TermClump();
  public: virtual bool RequestResources(eResourcesType, bool);
  public: virtual eResourceLoadStatus CheckResources(eResourcesType);
  public: virtual bool HasLoadedResources(eResourcesType);
  public: void SetInstancePriority(float, bool);
  public: virtual void NotifyResourceUnload(RWS::CResource&);
  public: virtual void NotifyResourceLoaded(RWS::CResource&);
  public: virtual void ReCalculateResourceState();
  public: const char* RetEnvBlockName() const;
  public: virtual unsigned char RetResourceState();
  public: void StartRenderCollision();
  public: void StopRenderCollision();
  public: void RenderCollision();
  public: void UpdateRendered();
  public: void SetBlockDisableFlag(bool);
  public: void SetVisibility(bool);
  public: bool IsVisible() const;
  public: bool IsPhysicsLoaded();
  protected: virtual bool LocateCollisionModel(PHYSICS::cBodyCinfo*, PHYSICS::cColData*);
  public: void CreateCollectorPhantom();
  public: void DeleteCollectorPhantom();
  public: void RepositionCollectorPhantom(Fun_Runtime::tAABB&);
  public: WorldManager::cStaticEnvironment& operator=(const WorldManager::cStaticEnvironment&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
