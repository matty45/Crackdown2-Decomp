
class AI::cMissionTier : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x64 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ private: Editor::cGUIDEventHandler<AI::cMissionTier> m_guidEventHandler;
  /* 0x002c */ private: Fun_Runtime::cList<AI::cMissionTier::tMissionData,Fun_Runtime::cAllocator<AI::cMissionTier::tMissionData,39,&AI::cMissionTier::tMissionTierList_FL> > m_lMissions;
  /* 0x0038 */ private: Fun_Runtime::cStringc m_sName;
  /* 0x0054 */ private: unsigned int m_nMissionTierIndex;
  /* 0x0058 */ private: bool m_bAllowGenericVOAReminders;
  /* 0x005c */ private: float m_fVOAReminderPeriod;
  /* 0x0060 */ private: bool m_bUnlocked;
  /* 0x0061 */ private: bool m_bComplete;
  public: static const char m_cMissionTier_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcMissionTierClass;
  public: static const char* pcMissionTierClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cMissionTier(const AI::cMissionTier&);
  public: cMissionTier(const RWS::CAttributePacket&);
  public: virtual ~cMissionTier();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void AddMissionList(const RWS::CAttributeCommandIterator&, bool);
  public: void AddMission(AI::cMission*, bool);
  public: void Unlock();
  public: void UpdateCompletionStatus();
  public: bool IsUnlocked() const;
  public: bool IsComplete() const;
  public: const char* RetName() const;
  public: const Fun_Runtime::cList<AI::cMissionTier::tMissionData,Fun_Runtime::cAllocator<AI::cMissionTier::tMissionData,39,&AI::cMissionTier::tMissionTierList_FL> >* RetMissionList() const;
  public: unsigned int RetMissionTierIndex() const;
  public: bool AllowGenericVOAReminders() const;
  public: float RetVOAReminderPeriod() const;
  protected: void SetMissionTierID(unsigned int);
  public: AI::cMissionTier& operator=(const AI::cMissionTier&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static Fun_Runtime::cFileLine tMissionTierList_FL();
};
