
class VFX::cRopes : public cNonGameBase, public GDb::cDebugPageHandler { /* Size=0x118 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac: fields for GDb::cDebugPageHandler */
  /* 0x00d0 */ private: Fun_Runtime::cVector<VFX::RopeSegmentData *,Fun_Runtime::cAllocator<VFX::RopeSegmentData *,3,&VFX::cRopes::vSegments_FL> > m_lSegments;
  /* 0x00e0 */ private: Fun_Runtime::cVector<VFX::RopeSegmentData *,Fun_Runtime::cAllocator<VFX::RopeSegmentData *,3,&VFX::cRopes::vSegments_FL> > m_lActiveSegments;
  /* 0x00f0 */ private: VFX::cShader* m_pSegmentShader;
  /* 0x00f4 */ private: float m_fSegmentWidth;
  /* 0x00f8 */ private: Cmd::cConsoleCommand m_ShowRopeSegments;
  public: static const char m_cRopes_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcRopesClass;
  public: static const char* pcRopesClassID;
  private: static Fun_Runtime::cPool<VFX::RopeSegmentData,600> m_SegmentPool;
  private: static bool m_bRenderRopes;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cRopes(const VFX::cRopes&);
  public: cRopes(const RWS::CAttributePacket&);
  public: virtual ~cRopes();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void Render();
  public: void GetRopeSegment(VFX::RopeSegmentData**);
  public: void ReturnRopeSegment(VFX::RopeSegmentData**);
  public: void ProcessNewlySpawnedSegments();
  private: virtual void RenderDebugPage(int, int);
  public: VFX::cRopes& operator=(const VFX::cRopes&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  private: static Fun_Runtime::cFileLine vSegments_FL();
  private: static void ShowRopeSegments(void*, wchar_t*);
};
