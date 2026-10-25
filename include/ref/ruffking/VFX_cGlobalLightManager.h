
class VFX::cGlobalLightManager : public cNonGameBase, public GDb::cDebugPageHandler { /* Size=0x5b30 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac: fields for GDb::cDebugPageHandler */
  /* 0x00d0 */ protected: _RTL_CRITICAL_SECTION m_blEntry;
  /* 0x00f0 */ protected: Fun_Runtime::cVectorip<VFX::cGlobalLight *,3712> m_vLights;
  /* 0x3b00 */ protected: Fun_Runtime::cVectorip<VFX::cGlobalLight *,512> m_vOccludedLights;
  /* 0x4310 */ protected: bool m_bNightTime;
  /* 0x4314 */ protected: unsigned int m_nToDTransitionTime;
  /* 0x4318 */ protected: VFX::cGlobalLightManager::tOcclusionData m_aOcclusionData[512];
  /* 0x5b18 */ protected: D3DTexture* m_pTexture;
  /* 0x5b1c */ protected: VFX::cShader* m_pShader;
  /* 0x5b20 */ protected: VFX::cShader* m_pShaderOcclusion;
  public: static const char m_cGlobalLightManager_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcGlobalLightManagerClass;
  public: static const char* pcGlobalLightManagerClassID;
  protected: static VFX::cGlobalLightManager* ms_pSingleton;
  protected: static Fun_Runtime::cMap<Fun_Runtime::cString,signed char,std::less<Fun_Runtime::cString>,Fun_Runtime::cAllocator<std::pair<Fun_Runtime::cString,signed char>,46,&VFX::cGlobalLightManager::cLightDataMap_FL> > m_LightDataMap;
  protected: static Fun_Runtime::cVector<VFX::cLightData *,Fun_Runtime::cAllocator<VFX::cLightData *,46,&VFX::cGlobalLightManager::cLightDataArray_FL> > m_vLightData;
  protected: static Fun_Runtime::cPool<VFX::cGlobalLight,3712> m_aLightPool;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGlobalLightManager(const VFX::cGlobalLightManager&);
  public: cGlobalLightManager(const RWS::CAttributePacket&);
  public: virtual ~cGlobalLightManager();
  public: void Render();
  public: void RenderOcclusionGeometry();
  public: void RenderAllLights();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: char RetLightIndex(const char*) const;
  public: const VFX::cLightData* RetLightData(char) const;
  public: void InitAfterLight(VFX::cAfterlightBase**, const VFX::cLightData*, VFX::cGlobalLight*);
  public: void TermAfterLight(VFX::cAfterlightBase**, const VFX::cLightData*);
  public: void GetLight(VFX::cGlobalLight**, char);
  public: void ReturnLight(VFX::cGlobalLight**);
  public: void InitOccludedLight(VFX::cGlobalLight**, char);
  public: void TermOccludedLight(VFX::cGlobalLight**);
  public: bool AddGlobalLight(VFX::cGlobalLight*);
  public: bool RemoveGlobalLight(VFX::cGlobalLight*);
  public: void RemoveAllLights();
  public: short GetOccludedLightIndex();
  public: void ReturnOccludedLightIndex(short);
  public: void FixupAfterLightData(VFX::cLightData*, char);
  protected: virtual void RenderDebugPage(int, int);
  private: bool AddOccludedLight(VFX::cGlobalLight*);
  private: bool RemoveOccludedLight(VFX::cGlobalLight*);
  private: void UpdateLight(VFX::cGlobalLight*, const VFX::cLightData*, const float, const bool, float&, float&);
  private: float CalcFlickerAlpha(VFX::cGlobalLight*, const VFX::cLightData*);
  private: float CalcPulseScale(VFX::cGlobalLight*, const VFX::cLightData*, float);
  private: float CalcFlashingAlpha(VFX::cGlobalLight*, const VFX::cLightData*);
  private: float CalcFadeAlpha(VFX::cGlobalLight*, const VFX::cLightData*, float);
  public: VFX::cGlobalLightManager& operator=(const VFX::cGlobalLightManager&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static VFX::cGlobalLightManager* RetGlobalLightManager();
  public: static char RegisterLightData(const char*, VFX::cLightData*);
  protected: static Fun_Runtime::cFileLine cLightDataMap_FL();
  protected: static Fun_Runtime::cFileLine cLightDataArray_FL();
};
