
class Audio::cVOAScheduler : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy, public GDb::cDebugPageHandler { /* Size=0x4a8 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x0040: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c: fields for GDb::cDebugPageHandler */
  /* 0x0040 */ private: float m_fPeriod;
  /* 0x0044 */ private: Fun_Runtime::cRandGen m_RandGen;
  /* 0x004c */ private: float m_fTimeSinceVOA;
  /* 0x0050 */ private: const Audio::cVOALine* m_apLines[256];
  /* 0x0450 */ private: int m_nLineCount;
  /* 0x0454 */ private: const Audio::cVOALine* m_pMostRecentlyPlayedLine;
  /* 0x0458 */ private: bool m_abAreBooleansForced[36];
  /* 0x047c */ private: bool m_abForcedValues[36];
  /* 0x04a0 */ private: Audio::etVOASchedulerDebugPage m_eDebugPage;
  /* 0x04a4 */ private: Audio::etVOABooleanState m_eSelectedBoolean;
  public: static const char m_cVOAScheduler_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcVOASchedulerClass;
  public: static const char* pcVOASchedulerClassID;
  private: static Audio::cVOAScheduler* ms_pInstance;
  private: static const int nMAX_VOA_LINES;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cVOAScheduler(const Audio::cVOAScheduler&);
  public: cVOAScheduler(const RWS::CAttributePacket&);
  public: virtual ~cVOAScheduler();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void RenderDebugPage(int, int);
  public: virtual void DebugPageUp();
  public: virtual void DebugPageDown();
  public: virtual void DebugPageLeft();
  public: virtual void DebugPageRight();
  public: virtual void DebugPageEnter();
  public: void RenderLinesDebugPage(int, int);
  public: void RenderGameStateDebugPage(int, int);
  public: void RegisterLine(const Audio::cVOALine*);
  public: void UnregisterLine(const Audio::cVOALine*);
  private: float RetPeriod() const;
  private: void ChooseAndPlayLine();
  public: Audio::cVOAScheduler& operator=(const Audio::cVOAScheduler&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static Audio::cVOAScheduler& RetInstance();
};
