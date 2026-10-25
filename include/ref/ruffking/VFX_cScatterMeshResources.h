
class VFX::cScatterMeshResources : public RWS::CAttributeHandler { /* Size=0x1c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: VFX::ScatterMesh* m_pMeshes;
  private: static const unsigned int msc_MaxMaskBits;
  private: static Fun_Runtime::cMap<unsigned int,VFX::ScatterMesh,std::less<unsigned int>,Fun_Runtime::cAllocator<std::pair<unsigned int,VFX::ScatterMesh>,50,&VFX::cScatterMeshResources::ScatterMeshMap_FL> > ms_MeshMap;
  private: static VFX::ScatterMesh* ms_pMaskBitMesh[32];
  private: static float ms_LODMaxDistance;
  private: static unsigned int ms_NextMaskBit;
  public: static const char* pcScatterMeshResourcesClassID;
  
  private: bool ProcessResource(const RWS::RWSGUID&);
  private: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cScatterMeshResources(const VFX::cScatterMeshResources&);
  public: cScatterMeshResources(const RWS::CAttributePacket&);
  public: virtual ~cScatterMeshResources();
  public: VFX::cScatterMeshResources& operator=(const VFX::cScatterMeshResources&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  private: static Fun_Runtime::cFileLine ScatterMeshMap_FL();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static const VFX::ScatterMesh* GetMesh(const unsigned int);
  public: static const VFX::ScatterMesh* GetMeshForMaskBit(const unsigned int);
  public: static float GetLODMaxDistance();
};
