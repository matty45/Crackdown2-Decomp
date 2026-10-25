
class Activity::cLongDistancePropManager : public cNonGameBase, public GDb::cDebugPageHandler { /* Size=0xe4 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac: fields for GDb::cDebugPageHandler */
  /* 0x00d0 */ protected: Fun_Runtime::cVector<Activity::cSpawnPoint *,Fun_Runtime::cAllocator<Activity::cSpawnPoint *,17,&Activity::cLongDistancePropManager::cSpawnPointVec_FL> > m_vpSpawnPoints;
  /* 0x00e0 */ protected: unsigned short m_nMaxProps;
  public: static const char m_cLongDistancePropManager_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcLongDistancePropManagerClass;
  public: static const char* pcLongDistancePropManagerClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLongDistancePropManager(const Activity::cLongDistancePropManager&);
  public: cLongDistancePropManager(const RWS::CAttributePacket&);
  public: virtual ~cLongDistancePropManager();
  public: void RegisterSpawnPoint(Activity::cSpawnPoint*);
  public: void UnRegisterSpawnPoint(Activity::cSpawnPoint*);
  public: void RemoveLongDistanceProps();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void Update(float);
  public: virtual void RenderDebugPage(int, int);
  protected: void SpawnDeleteObject(Activity::cSpawnPoint*, bool);
  protected: void RequestRenderResources(Activity::cSpawnPoint*, bool);
  public: Activity::cLongDistancePropManager& operator=(const Activity::cLongDistancePropManager&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  protected: static Fun_Runtime::cFileLine cSpawnPointVec_FL();
};
