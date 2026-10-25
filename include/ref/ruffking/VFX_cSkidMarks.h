
class VFX::cSkidMarks : public cNonGameBase, public GDb::cDebugPageHandler { /* Size=0x318 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac: fields for GDb::cDebugPageHandler */
  /* 0x00d0 */ private: unsigned int m_FadeTime;
  /* 0x00d4 */ private: unsigned int m_VertexBufferSize;
  /* 0x00d8 */ private: unsigned int m_IndexBufferSize;
  /* 0x00dc */ private: unsigned int m_VertexBufferMask;
  /* 0x00e0 */ private: unsigned int m_IndexBufferMask;
  /* 0x00e4 */ private: unsigned int m_NextVertex;
  /* 0x00e8 */ private: unsigned int m_Time;
  /* 0x00ec */ private: unsigned int m_RenderTime;
  /* 0x00f0 */ private: VFX::SkidMarkVertex* m_pVertices;
  /* 0x00f4 */ private: D3DVertexBuffer m_VertexBuffer;
  /* 0x0114 */ private: VFX::cShader* m_pShader;
  /* 0x0118 */ private: VFX::cSkidMarks::SkidMarkTextureBuffer m_TextureBuffer[8];
  /* 0x02f8 */ private: unsigned int m_QuadBufferUsed;
  /* 0x02fc */ private: unsigned int m_QuadBufferHead;
  /* 0x0300 */ private: unsigned int m_QuadBufferTail;
  /* 0x0304 */ private: unsigned int m_QuadBufferSize;
  /* 0x0308 */ private: unsigned int m_QuadBufferMask;
  /* 0x030c */ private: unsigned int* m_pQuadTime;
  /* 0x0310 */ private: unsigned char* m_pQuadTexture;
  /* 0x0314 */ private: float* m_pVertexV;
  private: static const unsigned int msc_MaxSkidMarkTextures;
  private: static Fun_Runtime::cMap<Fun_Runtime::cString,unsigned int,std::less<Fun_Runtime::cString>,Fun_Runtime::cAllocator<std::pair<Fun_Runtime::cString,unsigned int>,46,&VFX::cSkidMarks::cTextureMap_FL> > ms_TextureMap;
  private: static D3DTexture* ms_pTextures[8];
  private: static unsigned int ms_NumTextures;
  public: static const char m_cSkidMarks_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcSkidMarksClass;
  public: static const char* pcSkidMarksClassID;
  
  private: void AllocBuffers();
  private: void FreeBuffers();
  private: void InitShaders();
  private: void TermShaders();
  private: void InitTextureBuffer(const unsigned int);
  private: void TermTextureBuffer(const unsigned int);
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSkidMarks(const VFX::cSkidMarks&);
  public: cSkidMarks(const RWS::CAttributePacket&);
  public: virtual ~cSkidMarks();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void Update(const float);
  public: void Render();
  public: void Synchronise();
  public: void AddPoint(unsigned int*, const unsigned int, const float, const Fun_Runtime::Vec3, const Fun_Runtime::Vec3, const float);
  public: virtual void RenderDebugPage(int, int);
  public: VFX::cSkidMarks& operator=(const VFX::cSkidMarks&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  private: static Fun_Runtime::cFileLine cTextureMap_FL();
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static unsigned int GetTextureID(const char*);
};
