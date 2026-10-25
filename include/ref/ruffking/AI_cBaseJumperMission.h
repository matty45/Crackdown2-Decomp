
class AI::cBaseJumperMission : public AI::cMission { /* Size=0x400 */
  /* 0x0000: fields for AI::cMission */
  /* 0x03c0 */ private: Fun_Runtime::cVector<AI::cLocalPlayerTrigger *,Fun_Runtime::cAllocator<AI::cLocalPlayerTrigger *,15,&AI::cBaseJumperMission::tTriggerList_FL> > m_LandingZones;
  /* 0x03d0 */ private: AI::cBaseJumperMission::eBaseJumperMissionState m_eBJState;
  /* 0x03e0 */ private: Fun_Runtime::Vec3 m_vFallStartPos;
  /* 0x03f0 */ private: float m_fFallDist;
  public: static const char m_cBaseJumperMission_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcBaseJumperMissionClass;
  public: static const char* pcBaseJumperMissionClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cBaseJumperMission(const AI::cBaseJumperMission&);
  public: cBaseJumperMission(const RWS::CAttributePacket&);
  public: virtual ~cBaseJumperMission();
  public: virtual void TickUpdate(float);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: float RetFallDistance() const;
  private: void ChangeState(AI::cBaseJumperMission::eBaseJumperMissionState);
  public: AI::cBaseJumperMission& operator=(const AI::cBaseJumperMission&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  private: static Fun_Runtime::cFileLine tTriggerList_FL();
};
