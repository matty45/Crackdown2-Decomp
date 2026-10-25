
class AI::AIBehaviour : public cNonGameBase, public AI::cAIEventHandler { /* Size=0xc0 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac: fields for AI::cAIEventHandler */
  public: static const char* pAIBehaviourClassID;
  public: static const char m_AIBehaviour_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pAIBehaviourClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: AIBehaviour(const AI::AIBehaviour&);
  public: AIBehaviour(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void Update(float);
  public: virtual void RenderDebugInfo();
  public: virtual ~AIBehaviour();
  public: AI::AIBehaviour& operator=(const AI::AIBehaviour&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
