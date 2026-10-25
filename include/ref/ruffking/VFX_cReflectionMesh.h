
class VFX::cReflectionMesh : public RWS::CAttributeHandler { /* Size=0x20 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: VFX::ReflMeshHeader* m_pMeshes;
  /* 0x001c */ private: VFX::cReflectionMesh* m_pNext;
  private: static VFX::cReflectionMesh* ms_pRoot;
  private: static unsigned int ms_ShaderInitCount;
  private: static VFX::cShader* ms_pShader;
  public: static const char* pcReflectionMeshClassID;
  
  private: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cReflectionMesh(const VFX::cReflectionMesh&);
  public: cReflectionMesh(const RWS::CAttributePacket&);
  public: virtual ~cReflectionMesh();
  public: VFX::cReflectionMesh& operator=(const VFX::cReflectionMesh&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  private: static void InitShaders();
  private: static void TermShaders();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static void Render(const float);
};
