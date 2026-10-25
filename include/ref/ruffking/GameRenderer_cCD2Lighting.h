
class GameRenderer::cCD2Lighting : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy, public VFX::cParameterHandler { /* Size=0x2000 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x0020: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c: fields for VFX::cParameterHandler */
  /* 0x0020 */ private: float m_Phase;
  /* 0x0030 */ private: GameRenderer::cCD2Lighting::LightParams m_Params[8];
  /* 0x06b0 */ private: GameRenderer::cCD2Lighting::LightParams m_Current;
  /* 0x0780 */ private: GameRenderer::cCD2Lighting::LightParams m_Interior[8];
  /* 0x0e00 */ private: GameRenderer::cCD2Lighting::LightParams m_InteriorOffset[8];
  /* 0x1480 */ private: __vector4 m_FogParams[8];
  /* 0x1500 */ private: __vector4 m_CurrentFogParams;
  /* 0x1510 */ private: __vector4 m_InteriorFogParams[8];
  /* 0x1590 */ private: __vector4 m_StreetglowColour[8];
  /* 0x1610 */ private: __vector4 m_CurrentStreetglowColour;
  /* 0x1620 */ private: __vector4 m_InteriorLightDirection[8];
  /* 0x16a0 */ private: __vector4 m_ShadowColour;
  /* 0x16b0 */ private: __vector4 m_AOParams;
  /* 0x16c0 */ private: __vector4 m_ShadowDir;
  /* 0x16d0 */ private: GameRenderer::cCD2Lighting::WaterReflectionParams m_WaterReflectParams[8];
  /* 0x17d0 */ private: GameRenderer::cCD2Lighting::WaterReflectionParams m_CurrentWaterReflectParams;
  /* 0x17f0 */ private: GameRenderer::cCD2Lighting::BloomParams m_BloomParams[8];
  /* 0x18f0 */ private: GameRenderer::cCD2Lighting::BloomParams m_CurrentBloomParams;
  /* 0x1910 */ private: GameRenderer::cCD2Lighting::LightAttributes m_Attributes[8];
  /* 0x1c70 */ private: GameRenderer::cCD2Lighting::LightAttributes m_InteriorAttributes[8];
  /* 0x1fd0 */ private: float m_MinSunAngle;
  /* 0x1fd4 */ private: float m_MinShadowAngle;
  /* 0x1fd8 */ private: float m_SunInclination;
  /* 0x1fdc */ private: float m_MoonAngle;
  /* 0x1fe0 */ private: float m_MoonInclination;
  /* 0x1fe4 */ private: float m_DayToNightTime;
  /* 0x1fe8 */ private: float m_NightToDayTime;
  /* 0x1fec */ private: float m_DayNightTransition;
  /* 0x1ff0 */ private: float m_Overcast;
  /* 0x1ff4 */ private: float m_NightLightBlend;
  private: static const unsigned int msc_NumParams;
  private: static const unsigned int msc_NumInteriorParams;
  private: static GameRenderer::cCD2Lighting* ms_pCD2Lighting;
  public: static const char* pcCD2LightingClassID;
  
  private: __vector4 ConvertToPSFogParams(const __vector4);
  private: void BuildLightParams();
  private: void BuildLightParams(const GameRenderer::cCD2Lighting::LightAttributes*, GameRenderer::cCD2Lighting::LightParams*, __vector4*, __vector4*, GameRenderer::cCD2Lighting::WaterReflectionParams*, GameRenderer::cCD2Lighting::BloomParams*);
  private: void Update();
  private: virtual VFX::cParameterHandler::ParamType GetParameter(const unsigned int, void*) const;
  private: virtual void SetParameter(const unsigned int, void*);
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCD2Lighting(const GameRenderer::cCD2Lighting&);
  public: cCD2Lighting(const RWS::CAttributePacket&);
  public: virtual ~cCD2Lighting();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: float Phase() const;
  public: const GameRenderer::cCD2Lighting::LightParams& GetLightParams() const;
  public: const __vector4 GetMainLightDirection() const;
  public: const __vector4 GetFogParams() const;
  public: const GameRenderer::cCD2Lighting::LightParams& GetInteriorLightParams(const unsigned int) const;
  public: const __vector4 GetInteriorFogParams(const unsigned int) const;
  public: const GameRenderer::cCD2Lighting::LightParams& GetInteriorOffsetParams(const unsigned int) const;
  public: const __vector4 GetStreetglowColour() const;
  public: const GameRenderer::cCD2Lighting::WaterReflectionParams& GetWaterReflectionParams() const;
  public: const GameRenderer::cCD2Lighting::BloomParams& GetBloomParams() const;
  public: const __vector4 GetShadowColour() const;
  public: const __vector4 GetShadowDirection() const;
  public: const __vector4 GetAOParams() const;
  public: const float GetNightLightBlend() const;
  public: GameRenderer::cCD2Lighting& operator=(const GameRenderer::cCD2Lighting&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static GameRenderer::cCD2Lighting* RetCD2Lighting();
};
