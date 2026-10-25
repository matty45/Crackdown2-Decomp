
class AI::TrainingPilot : public AI::NPCBehaviour { /* Size=0x110 */
  /* 0x0000: fields for AI::NPCBehaviour */
  /* 0x0100 */ private: bool m_bPatrolling;
  public: static const char* pTrainingPilotClassID;
  public: static const char m_TrainingPilot_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pTrainingPilotClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: TrainingPilot(const AI::TrainingPilot&);
  public: TrainingPilot(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void Update(float);
  public: virtual ~TrainingPilot();
  public: AI::TrainingPilot& operator=(const AI::TrainingPilot&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
