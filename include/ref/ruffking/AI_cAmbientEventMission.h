
class AI::cAmbientEventMission : public RWS::CEventHandler, public AI::cMissionBase { /* Size=0x3b0 */
  /* 0x0000: fields for RWS::CEventHandler */
  /* 0x0010: fields for AI::cMissionBase */
  /* 0x0360 */ private: bool m_bCleared;
  /* 0x0361 */ private: unsigned char m_nMaxIndex;
  /* 0x0362 */ private: bool m_bIsDay;
  /* 0x0364 */ private: AI::cAmbientEventMission::eAmbientEventDayState m_eDayState;
  /* 0x0370 */ private: Fun_Runtime::cVectorip<AI::cMission *,10> m_vMissions;
  public: static const char m_cAmbientEventMission_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAmbientEventMissionClass;
  public: static const char* pcAmbientEventMissionClassID;
  private: static bool m_bDebugInfo;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAmbientEventMission(const AI::cAmbientEventMission&);
  public: cAmbientEventMission(const RWS::CAttributePacket&);
  public: virtual ~cAmbientEventMission();
  public: virtual bool IsOwnedLocally();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void TickUpdate(float);
  public: virtual void Activate();
  public: virtual void Deactivate();
  public: virtual void ResetMission();
  public: virtual unsigned short RetMissionID() const;
  public: void IncrementCount();
  public: virtual void CalculateLOD(int);
  public: virtual void RenderDebugPage(int&, int&);
  public: virtual bool DebugPageEnter();
  public: virtual const char* RetMenuText(unsigned char);
  public: void RenderDebugInfo();
  public: void SetDay(unsigned char);
  protected: void SetAmbientEventDayState(AI::cAmbientEventMission::eAmbientEventDayState);
  protected: AI::cAmbientEventMission::eAmbientEventDayState RetAmbientEventDayState() const;
  protected: virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
  protected: virtual unsigned int GetMaxReplicatedFields() const;
  protected: virtual unsigned int GetNumObjectIDBits() const;
  protected: virtual void InitReplication();
  protected: virtual void TermReplication();
  protected: virtual void ReplicateInitialFields();
  protected: virtual void ReplicateFields();
  protected: void ToggleCleared();
  public: AI::cAmbientEventMission& operator=(const AI::cAmbientEventMission&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static void ShowDebug();
};
