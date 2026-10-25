
class AI::TrainingAmbient : public AI::NPCBehaviour, public cNPCArmourySetup { /* Size=0x110 */
  /* 0x0000: fields for AI::NPCBehaviour */
  /* 0x0100: fields for cNPCArmourySetup */
  /* 0x0100 */ private: Activity::cSquadMemberSpawnPoint* m_pTargetSP;
  /* 0x0104 */ private: AI::TrainingAmbient::eState m_nState;
  public: static const char* pTrainingAmbientClassID;
  public: static const char m_TrainingAmbient_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pTrainingAmbientClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: TrainingAmbient(const AI::TrainingAmbient&);
  public: TrainingAmbient(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void Update(float);
  public: virtual void SetAmbientTarget(Activity::cSquadMemberSpawnPoint*);
  public: virtual void OnAmbient(const Fun_Runtime::cVectorip<AI::cAnimParams *,10>&, float);
  private: const AI::cPatrolRoute* RetDefaultPatrolRoute();
  public: virtual ~TrainingAmbient();
  public: AI::TrainingAmbient& operator=(const AI::TrainingAmbient&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
