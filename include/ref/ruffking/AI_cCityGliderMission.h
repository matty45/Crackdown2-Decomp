
class AI::cCityGliderMission : public AI::cMission { /* Size=0x440 */
  /* 0x0000: fields for AI::cMission */
  /* 0x03c0 */ private: unsigned char m_nProgress[16];
  /* 0x03d0 */ private: unsigned int m_nLastCompletedTime[16];
  /* 0x0410 */ private: Fun_Runtime::cVector<AI::cCityGliderWaypoint *,Fun_Runtime::cAllocator<AI::cCityGliderWaypoint *,15,&AI::cCityGliderMission::tWaypoints_FL> > m_IslandWaypoints[3];
  public: static const char m_cCityGliderMission_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcCityGliderMissionClass;
  public: static const char* pcCityGliderMissionClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCityGliderMission(const AI::cCityGliderMission&);
  public: cCityGliderMission(const RWS::CAttributePacket&);
  public: virtual ~cCityGliderMission();
  public: virtual void TickUpdate(float);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: unsigned char RetProgressForNode(unsigned char) const;
  public: unsigned char RetNumCompleteNodes() const;
  public: virtual void RenderDebugPage(int&, int&);
  public: AI::cCityGliderMission& operator=(const AI::cCityGliderMission&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  private: static Fun_Runtime::cFileLine tWaypoints_FL();
};
