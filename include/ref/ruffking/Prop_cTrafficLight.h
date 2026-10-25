
class Prop::cTrafficLight : public Prop::cProp { /* Size=0xed0 */
  /* 0x0000: fields for Prop::cProp */
  /* 0x0ea0 */ protected: long long m_iTrafficControlEdgeID;
  /* 0x0ea8 */ protected: AI::cJunctionNodeController::eSignalColour m_eCurrentColour;
  /* 0x0eac */ protected: AI::cJunctionNodeController::eSignalColour m_eNewColour;
  /* 0x0eb0 */ protected: bool m_bLightActive;
  /* 0x0eb1 */ protected: bool m_bFirstRender;
  /* 0x0eb2 */ protected: bool m_bIsBroken;
  /* 0x0eb4 */ protected: AI::cTrafficControlEdge::LogicType m_LogicType;
  /* 0x0eb8 */ protected: VFX::cGlobalLight* m_paBillboardLight[2];
  /* 0x0ec0 */ protected: Prop::cTrafficLight* m_pNextActive;
  /* 0x0ec4 */ protected: Prop::cTrafficLight* m_pPrevActive;
  public: static const char m_cTrafficLight_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcTrafficLightClass;
  public: static const char* pcTrafficLightClassID;
  protected: static Prop::cTrafficLight* ms_pFirstActive;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTrafficLight(const Prop::cTrafficLight&);
  public: cTrafficLight(GOM::cObjectPrototype*);
  public: virtual ~cTrafficLight();
  public: virtual void TickUpdate(float);
  public: virtual bool EnterRenderableState(eResourcesType);
  public: virtual void LeaveRenderableState();
  public: virtual void UpdateRenderMatrix();
  public: void SetTrafficControlEdgeID(long long);
  public: long long RetTrafficControlEdgeID();
  public: void SetLogicType(AI::cTrafficControlEdge::LogicType);
  protected: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  protected: virtual Fun_Runtime::RetVal Term();
  protected: virtual void AddBillboardLight();
  protected: virtual void RemoveBillboardLight();
  protected: void UpdateLightColour(AI::cJunctionNodeController::eSignalColour, bool);
  protected: bool AddLight(int, AI::cJunctionNodeController::eSignalColour);
  protected: void RemoveLight(int, AI::cJunctionNodeController::eSignalColour);
  protected: void FindFrame(int, AI::cJunctionNodeController::eSignalColour, cFrame&);
  protected: void RemoveAllLights();
  protected: virtual void OnBreakOff();
  protected: virtual void TurnOffLights();
  public: Prop::cTrafficLight& operator=(const Prop::cTrafficLight&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static void UpdateAllLights(unsigned long long, AI::cJunctionNodeController::eSignalColour);
};
