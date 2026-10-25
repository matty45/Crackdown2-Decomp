
class AI::cMissionActivationCylinder : public ZoneManager::cPlayerTriggerCylinder { /* Size=0x110 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerCylinder */
  /* 0x00f0 */ public: Editor::cGUIDEventHandler<AI::cMissionActivationCylinder> m_EventHandler;
  /* 0x0104 */ private: bool m_bMissionCritical;
  public: static const char* pcMissionActivationCylinderClassID;
  public: static Fun_Runtime::cList<AI::cMissionActivationCylinder *,Fun_Runtime::cAllocator<AI::cMissionActivationCylinder *,39,&AI::cMissionActivationCylinder::tActCylinderList_FL> > m_lCurrentActivationList;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cMissionActivationCylinder(const AI::cMissionActivationCylinder&);
  public: cMissionActivationCylinder(const RWS::CAttributePacket&);
  public: virtual ~cMissionActivationCylinder();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: virtual void DebugDrawTriggerZone();
  public: void SetMissionCritical(bool);
  public: AI::cMissionActivationCylinder& operator=(const AI::cMissionActivationCylinder&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static AI::cMissionActivationCylinder* RetCurrentActivationCylinder();
  public: static Fun_Runtime::cFileLine tActCylinderList_FL();
};
