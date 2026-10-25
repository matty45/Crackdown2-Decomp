
class VFX::cTracers : public cNonGameBase, public GDb::cDebugPageHandler { /* Size=0x184 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac: fields for GDb::cDebugPageHandler */
  /* 0x00d0 */ private: Fun_Runtime::cVector<VFX::TracerData *,Fun_Runtime::cAllocator<VFX::TracerData *,3,&VFX::cTracers::cTracerVec_FL> > m_vTracers;
  /* 0x00e0 */ private: Fun_Runtime::cVector<VFX::TracerData *,Fun_Runtime::cAllocator<VFX::TracerData *,3,&VFX::cTracers::m_vActiveTracers_FL> > m_vActiveTracers;
  /* 0x00f0 */ private: Fun_Runtime::cVector<VFX::TrailData,Fun_Runtime::cAllocator<VFX::TrailData,3,&VFX::cTracers::m_vTrails_FL> > m_vTrails;
  /* 0x0100 */ private: Fun_Runtime::cVector<VFX::TrailData *,Fun_Runtime::cAllocator<VFX::TrailData *,3,&VFX::cTracers::m_vActiveTrails_FL> > m_vActiveTrails;
  /* 0x0110 */ private: Fun_Runtime::cVector<VFX::TrailData *,Fun_Runtime::cAllocator<VFX::TrailData *,3,&VFX::cTracers::m_vFreeTrails_FL> > m_vFreeTrails;
  /* 0x0120 */ private: Fun_Runtime::cVector<VFX::TrailData *,Fun_Runtime::cAllocator<VFX::TrailData *,3,&VFX::cTracers::m_vNewTrails_FL> > m_vNewTrails;
  /* 0x0130 */ private: unsigned int m_NumActiveTrails;
  /* 0x0134 */ private: VFX::cShader* m_pTracerShader;
  /* 0x0138 */ private: D3DTexture* m_pTracerTexture;
  /* 0x013c */ private: unsigned int m_nMaxTracers;
  /* 0x0140 */ private: unsigned int m_nMaxTrails;
  /* 0x0144 */ private: Cmd::cConsoleCommand m_SetTracers;
  /* 0x0164 */ private: Cmd::cConsoleCommand m_SetTrails;
  public: static const char m_cTracers_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcTracersClass;
  public: static const char* pcTracersClassID;
  private: static Fun_Runtime::cPool<VFX::TracerData,1000> m_aTracerPool;
  private: static bool m_bRenderTracers;
  private: static bool m_bRenderTrails;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: cTracers(const VFX::cTracers&);
  public: cTracers(const RWS::CAttributePacket&);
  public: virtual ~cTracers();
  public: Fun_Runtime::Vec3 UpdateTracer(VFX::TracerData*);
  public: bool UpdateVaporTrail(VFX::TrailData*, float);
  public: void Render();
  public: void GetTracer(VFX::TracerData**);
  public: void ReturnTracer(VFX::TracerData**);
  public: float SpawnTrail(const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&, bool, bool, float, unsigned long, float, float, float);
  public: void SpawnTrailSegment(const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&, unsigned long, float, float, float, float, float, float, float);
  public: void ProcessNewlySpawnedTracers();
  private: void InitializeTracerVertexDecl(D3DDevice*);
  private: virtual void RenderDebugPage(int, int);
  public: VFX::cTracers& operator=(const VFX::cTracers&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  private: static Fun_Runtime::cFileLine cTracerVec_FL();
  private: static Fun_Runtime::cFileLine m_vActiveTracers_FL();
  private: static Fun_Runtime::cFileLine m_vTrails_FL();
  private: static Fun_Runtime::cFileLine m_vActiveTrails_FL();
  private: static Fun_Runtime::cFileLine m_vFreeTrails_FL();
  private: static Fun_Runtime::cFileLine m_vNewTrails_FL();
  private: static void SetTrails(void*, wchar_t*);
  private: static void SetTracers(void*, wchar_t*);
};
