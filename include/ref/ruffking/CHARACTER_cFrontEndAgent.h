
class CHARACTER::cFrontEndAgent : public CHARACTER::cPlayerCharacter { /* Size=0x3df0 */
  /* 0x0000: fields for CHARACTER::cPlayerCharacter */
  /* 0x2d70 */ private: TGT::cPlayerTargeting m_Targeting;
  /* 0x3520 */ private: CHARACTER::cCharacterControllerSimple m_Phantom;
  /* 0x3780 */ private: CHARACTER::cFEPoi* m_POI;
  /* 0x3784 */ private: Anim::cAnimHandlerDefault m_HndDefault;
  /* 0x378c */ private: Anim::cAnimHandlerGenericFullBody m_HndGenericFullBody;
  /* 0x379c */ private: CHARACTER::cActionGenericFullBodyIF m_GenericFullBody;
  /* 0x37dc */ private: Anim::cAnimHandlerStand m_HndStand;
  /* 0x37e4 */ private: CHARACTER::cActionStandIF m_StandIF;
  /* 0x3810 */ private: CHARACTER::cActionHand2HandFullIF m_Hand2HandFull;
  /* 0x3b50 */ private: Anim::cAnimHandlerTransformation m_HndTransformation;
  /* 0x3b58 */ private: CHARACTER::cActionTransformationIF m_TransformationIF;
  /* 0x3b80 */ private: CHARACTER::cActionHand2HandUpperIF m_Hand2HandUpper;
  /* 0x3de0 */ private: CHARACTER::cDebugIF m_DebugIF;
  public: static const char m_cFrontEndAgent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcFrontEndAgentClass;
  public: static const char* pcFrontEndAgentClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cFrontEndAgent(const CHARACTER::cFrontEndAgent&);
  public: cFrontEndAgent(GOM::cObjectPrototype*);
  public: virtual ~cFrontEndAgent();
  public: virtual Fun_Runtime::RetVal InitClump();
  public: virtual bool HandleRenderableResources(GOM::cObjectPrototype*);
  public: virtual void PreTickUpdate(float);
  public: virtual void TickUpdate(float);
  public: virtual void PostTickUpdate(float);
  public: virtual void UpdateCameraAlphaFading(float);
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual void TickReplicationUpdate(float);
  public: virtual bool CanUpdatePhysics();
  public: CHARACTER::cFrontEndAgent& operator=(const CHARACTER::cFrontEndAgent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
