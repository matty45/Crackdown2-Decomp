
class VFX::cDepthOfField : public RWS::CAttributeHandler { /* Size=0x88 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: VFX::cShader* m_pShaderDOFCalcBlur;
  /* 0x001c */ private: VFX::cShader* m_pShaderDOF;
  /* 0x0020 */ private: D3DTexture m_ScreenBuffer;
  /* 0x0054 */ private: void* m_pTextureMemory;
  /* 0x0058 */ private: bool m_Enabled;
  /* 0x005c */ private: float m_NearDistance;
  /* 0x0060 */ private: float m_FarDistance;
  /* 0x0064 */ private: float m_BlurRadius;
  /* 0x0068 */ private: Cmd::cConsoleCommand m_DOFToggleCmd;
  private: static VFX::cDepthOfField* ms_pInstance;
  public: static const char* pcDepthOfFieldClassID;
  
  private: virtual void HandleAttributes(const RWS::CAttributePacket&);
  private: void InitShaders();
  private: void TermShaders();
  private: void InitDynamicTextures();
  private: void TermDynamicTextures();
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cDepthOfField(const VFX::cDepthOfField&);
  public: cDepthOfField(const RWS::CAttributePacket&);
  public: virtual ~cDepthOfField();
  public: void Render();
  public: VFX::cDepthOfField& operator=(const VFX::cDepthOfField&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  private: static void ToggleDOF(void*, wchar_t*);
  private: static void SetDOFBlur(void*, wchar_t*);
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static VFX::cDepthOfField* GetInstance();
};
