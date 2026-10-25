
class WorldManager::cLOD4Environment : public cGameBase, public WorldManager::cFadeInOutInterface { /* Size=0x2e0 */
  /* 0x0000: fields for cGameBase */
  /* 0x0140: fields for WorldManager::cFadeInOutInterface */
  /* 0x0158 */ private: ResourceManager::cResourceCatalogueEntry* m_pResCatEntry;
  /* 0x0160 */ private: Fun_Runtime::cVectorip<Fun_Runtime::cSafeDeletablePointer<WorldManager::cStaticEnvironment>,21> m_vpEnvBlocks;
  /* 0x02c0 */ private: Editor::cGUIDEventHandler<WorldManager::cLOD4Environment> m_EventHandler;
  /* 0x02d4 */ private: bool m_bBlockIsDisabled;
  public: static const char m_cLOD4Environment_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcLOD4EnvironmentClass;
  public: static const char* pcLOD4EnvironmentClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLOD4Environment(const WorldManager::cLOD4Environment&);
  public: cLOD4Environment(const RWS::CAttributePacket&);
  public: virtual ~cLOD4Environment();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: void LoadLOD3s(WorldManager::cLOD4Environment*, bool, ResourceManager::cResourceBlock*);
  public: eResourceLoadStatus RetLOD3LoadStatus();
  public: wchar_t* RetLOD3LoadStatusString();
  public: const wchar_t* RetResCatEntryName() const;
  public: void FadeDown(float);
  public: void FadeUp(float);
  public: void SetFullyVisible();
  public: void SetInvisible();
  public: void SetPriority(float);
  public: void SetBlockDisableFlag(bool);
  public: bool BlockIsDisabled() const;
  public: bool AnyLOD3Fading() const;
  public: ResourceManager::cResourceCatalogueEntry* RetResCatEntry();
  private: void LockLOD(WorldManager::cStaticEnvironment*);
  private: void UnlockLOD(WorldManager::cStaticEnvironment*);
  public: WorldManager::cLOD4Environment& operator=(const WorldManager::cLOD4Environment&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  private: static void SetupPointerToEnvBlock(ResourceManager::cStreamingResource*, void*);
};
