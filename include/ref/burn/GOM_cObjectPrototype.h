
class GOM::cObjectPrototype : public RWS::CAttributeHandler, public ResourceManager::cStreamingResourceClient { /* Size=0x70 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for ResourceManager::cStreamingResourceClient */
  /* 0x0024 */ private: Fun_Runtime::cVector<RWS::CResource *,Fun_Runtime::cAllocator<RWS::CResource *,19,&GOM::cObjectPrototype::cResourcesVec_FL> > m_Resources;
  /* 0x0040 */ private: Fun_Runtime::tAABB m_LocalAABB;
  /* 0x0060 */ private: const char* m_pName;
  /* 0x0064 */ private: const Fun_Runtime::cClass* m_pSpawnClass;
  /* 0x0068 */ private: const Fun_Runtime::cClass* m_pActualClass;
  /* 0x006c */ private: unsigned char m_nResourceState;
  /* 0x006d */ private: unsigned char m_nProtoFlags;
  
  public: cObjectPrototype(const GOM::cObjectPrototype&);
  public: cObjectPrototype();
  public: cObjectPrototype(const RWS::CAttributePacket&);
  public: virtual ~cObjectPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void PropagateAttributes();
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual bool RequestResources(eResourcesType, bool);
  public: virtual eResourceLoadStatus CheckResources(eResourcesType);
  public: virtual bool HasLoadedResources(eResourcesType);
  public: void AddInstancePriority(float);
  public: virtual void NotifyResourceUnload(RWS::CResource&);
  public: virtual void NotifyResourceLoaded(RWS::CResource&);
  public: virtual void ReCalculateResourceState();
  public: bool HasResourceWithCatEntryID(unsigned int);
  public: const Fun_Runtime::tAABB& RetLocalAABB() const;
  public: void GetWorldAABB(const Fun_Runtime::Mtx&, Fun_Runtime::tAABB&);
  public: const char* RetName() const;
  public: const Fun_Runtime::cClass* RetSpawnClass() const;
  public: const Fun_Runtime::cClass* RetActualClass() const;
  public: unsigned char RetResourceState() const;
  public: void SetProtoFlags(unsigned char);
  public: void ClearProtoFlags(unsigned char);
  public: bool HasProtoFlags(unsigned char) const;
  protected: void GenerateName(const RWS::CAttributePacket&);
  public: GOM::cObjectPrototype& operator=(const GOM::cObjectPrototype&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static bool IsAPrototype(const RWS::CAttributePacket&);
  private: static Fun_Runtime::cFileLine cResourcesVec_FL();
};
