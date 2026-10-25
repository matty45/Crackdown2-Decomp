
class AI::cTopOfTheWorldTrigger : public ZoneManager::cPlayerTriggerZone { /* Size=0xe0 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerZone */
  public: static const char* pcTopOfTheWorldTriggerClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTopOfTheWorldTrigger(const AI::cTopOfTheWorldTrigger&);
  public: cTopOfTheWorldTrigger(const RWS::CAttributePacket&);
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: virtual bool DoCollision(CHARACTER::cCharacter*);
  public: virtual ~cTopOfTheWorldTrigger();
  public: AI::cTopOfTheWorldTrigger& operator=(const AI::cTopOfTheWorldTrigger&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
