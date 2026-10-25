
class AI::cGoliathBreachHole : public AI::cBreachHole { /* Size=0x180 */
  /* 0x0000: fields for AI::cBreachHole */
  /* 0x0170 */ private: Fun_Runtime::cList<Activity::cSquadSpawnPoint *,Fun_Runtime::cAllocator<Activity::cSquadSpawnPoint *,39,&AI::cBreachHole::tSquadSpawnPointList_FL> > m_lGoliathSquads;
  /* 0x017c */ private: Activity::cSquadSpawnPoint* m_pCurrentSquad;
  public: static const char m_cGoliathBreachHole_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcGoliathBreachHoleClass;
  public: static const char* pcGoliathBreachHoleClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGoliathBreachHole(const AI::cGoliathBreachHole&);
  public: cGoliathBreachHole(const RWS::CAttributePacket&);
  public: virtual ~cGoliathBreachHole();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void TickUpdate(float, bool);
  public: void DisableAllSquads();
  public: virtual void ExitState(AI::cBreachHole::eBreachHoleState);
  public: virtual void EnterState(AI::cBreachHole::eBreachHoleState);
  public: virtual void TryKillAllSpawned();
  public: AI::cGoliathBreachHole& operator=(const AI::cGoliathBreachHole&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
