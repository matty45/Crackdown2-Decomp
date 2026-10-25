
class AI::TrainingDummy : public AI::NPCBehaviour { /* Size=0x110 */
  /* 0x0000: fields for AI::NPCBehaviour */
  /* 0x0100 */ private: AI::TrainingDummy::eState m_nState;
  /* 0x0104 */ private: unsigned int m_nEmoteTime;
  /* 0x0108 */ private: unsigned char m_nDamageFlags;
  /* 0x0109 */ private: unsigned char m_nSpawnAction;
  public: static const char* pTrainingDummyClassID;
  public: static const char m_TrainingDummy_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pTrainingDummyClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: TrainingDummy(const AI::TrainingDummy&);
  public: TrainingDummy(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void Update(float);
  public: virtual void OnAttacked(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void SetSpawnAction(unsigned char);
  public: unsigned char RetDamageFlags() const;
  public: void ResetDamageFlags();
  public: virtual void RenderDebugInfo();
  public: AI::TDummyPrototype* RetTDummyProto() const;
  private: void ChangeState(AI::TrainingDummy::eState);
  private: void TrackPlayer();
  public: virtual ~TrainingDummy();
  public: AI::TrainingDummy& operator=(const AI::TrainingDummy&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
