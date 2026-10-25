
class VFX::cSkyDome : public RWS::CAttributeHandler, public RWS::CEventHandler, public VFX::cParameterHandler { /* Size=0x4d0 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c: fields for VFX::cParameterHandler */
  /* 0x0020 */ public: VFX::cSkyDome::TODData m_todDataArray[12];
  /* 0x04a0 */ public: VFX::cSkyDome::TODData* m_tod;
  /* 0x04a4 */ public: VFX::cSkyDome::TODData* m_todNext;
  /* 0x04a8 */ public: float m_todBlend;
  /* 0x04ac */ public: VFX::cShader* m_atmosphereShader;
  /* 0x04b0 */ public: VFX::cShader* m_moonShader;
  /* 0x04b4 */ public: VFX::cShader* m_starsShader;
  /* 0x04b8 */ public: VFX::cShader* m_cloudsShader;
  /* 0x04bc */ public: VFX::cShader* m_smallCloudsShader;
  /* 0x04c0 */ private: bool m_enabled;
  private: static VFX::cSkyDome* ms_pSkyDome;
  public: static const char* pcSkyDomeClassID;
  public: static const unsigned int m_TODUpto;
  
  private: void InitShaders();
  private: void TermShaders();
  private: void Update();
  private: virtual VFX::cParameterHandler::ParamType GetParameter(const unsigned int, void*) const;
  private: virtual void SetParameter(const unsigned int, void*);
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSkyDome(const VFX::cSkyDome&);
  public: cSkyDome(const RWS::CAttributePacket&);
  public: virtual ~cSkyDome();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: void Render();
  public: void RenderSmallCloud();
  public: void RenderCloudsToAlpha(float);
  public: void ReloadShaders();
  public: D3DXVECTOR3 GetLightDirection();
  public: float GetDomeRadius();
  public: float GetDaytime();
  public: float GetLatitude();
  public: float GetBearing();
  public: float GetCloudMoveSpeedU();
  public: float GetCloudMoveSpeedV();
  public: VFX::cSkyDome::TODData* GetTODData();
  public: VFX::cSkyDome::TODData* GetTODDataNext();
  public: float GetTodBlend();
  public: float GetWindDirection();
  public: float GetWindSpeed();
  public: float GetPhaseDelta();
  public: bool Enabled() const;
  public: void Enable(bool);
  public: VFX::cSkyDome& operator=(const VFX::cSkyDome&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static VFX::cSkyDome* RetInstance();
  public: static void GetAsColour(__vector4*, RWS::CAttributeCommandIterator&);
};
