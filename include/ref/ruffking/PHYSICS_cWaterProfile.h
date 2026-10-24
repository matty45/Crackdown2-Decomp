
class PHYSICS::cWaterProfile : public cNonGameBase, public GDb::cDebugPageHandler { /* Size=0xd0 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac: fields for GDb::cDebugPageHandler */
  public: static PHYSICS::cWaterCinfo m_WaterInfo;
  public: static const char m_cWaterProfile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcWaterProfileClass;
  public: static const char* pcWaterProfileClassID;
  
  private: void Initialise();
  private: void Terminate();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: cWaterProfile(const PHYSICS::cWaterProfile&);
  public: cWaterProfile(const RWS::CAttributePacket&);
  public: virtual ~cWaterProfile();
  public: PHYSICS::cWaterProfile& operator=(const PHYSICS::cWaterProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static float RetWaterLevel();
  public: static float RetWaveAmplitude();
  public: static float RetWaveFrequency();
  public: static float RetWaveLength();
  public: static float RetWaveGradient();
  public: static float RetWaterAngularDamping();
  public: static float RetWaterLinearDamping();
  public: static float RetWaterLevelMax();
  public: static float RetWaterLinearFwdDamping();
  public: static float RetGroundLevel();
  public: static float RetMaxHeightLevel();
};
