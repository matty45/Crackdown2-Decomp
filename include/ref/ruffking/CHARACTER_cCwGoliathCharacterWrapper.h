
class CHARACTER::cCwGoliathCharacterWrapper : public CHARACTER::cCwCharacter { /* Size=0x3400 */
  /* 0x0000: fields for CHARACTER::cCwCharacter */
  /* 0x2c50 */ private: CHARACTER::cCharacterControllerGoliath m_Phantom;
  /* 0x2e00 */ private: TGT::cAiTargeting m_Targeting;
  /* 0x2e60 */ private: CHARACTER::cGoliathPoiIF m_PoiIF;
  /* 0x2ee0 */ private: CHARACTER::cDebugIF m_DebugIF;
  /* 0x2ee8 */ private: Anim::cAnimHandlerDefault m_HndDefault;
  /* 0x2ef0 */ private: Anim::cAnimHandlerGenericFullBody m_HndGenericFullBody;
  /* 0x2f00 */ private: Anim::cAnimHandlerGoliath m_HndGoliath;
  /* 0x2f08 */ private: Anim::cAnimHandlerPropPickUpFull m_HndPropPickUpFull;
  /* 0x2f10 */ private: Anim::cAnimHandlerPropCarryNPC m_HndPropCarry;
  /* 0x2f18 */ private: Anim::cAnimHandlerPropThrowNPC m_HndPropThrow;
  /* 0x2f20 */ private: Anim::cAnimHandlerNPCEquipmentThrowFull m_HndEquipmentThrowFull;
  /* 0x2f28 */ private: Anim::cAnimHandlerStand m_HndStand;
  /* 0x2f30 */ private: Anim::cDeathHandler m_HndDeath;
  /* 0x2f40 */ private: CHARACTER::cActionGoliathVfxIF m_VfxIF;
  /* 0x30b0 */ private: CHARACTER::cActionGenericFullBodyIF m_GenericFullBody;
  /* 0x30f0 */ private: CHARACTER::cActionGoliathIF m_GoliathIF;
  /* 0x3310 */ private: CHARACTER::cActionPropPickUpFullIF m_PropPickUpFull;
  /* 0x3338 */ private: CHARACTER::cActionNPCPropCarryFullIF m_PropCarryIF;
  /* 0x3358 */ private: CHARACTER::cActionNPCPropThrowFullIF m_PropThrowIF;
  /* 0x3380 */ private: CHARACTER::cActionNPCEquipmentThrowFullIF m_EquipmentThrowFull;
  /* 0x33ac */ private: CHARACTER::cActionStandIF m_StandIF;
  /* 0x33d8 */ private: CHARACTER::cActionDeadIF m_DeadIF;
  public: static const char m_cCwGoliathCharacterWrapper_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcCwGoliathCharacterWrapperClass;
  public: static const char* pcCwGoliathCharacterWrapperClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCwGoliathCharacterWrapper(const CHARACTER::cCwGoliathCharacterWrapper&);
  public: cCwGoliathCharacterWrapper(GOM::cObjectPrototype*);
  public: virtual ~cCwGoliathCharacterWrapper();
  public: virtual Fun_Runtime::RetVal InitClump();
  public: virtual bool CanUpdate();
  public: virtual bool CanUpdateAnimation();
  public: virtual bool CanUpdatePhysics();
  public: virtual bool IsManagedByActivityManager();
  public: virtual bool NeedsEnvironmentCollision();
  public: virtual void PostTickUpdate(float);
  public: unsigned char LodCalculation(unsigned int);
  public: virtual int RetCharNetworkLOD(CHARACTER::cCharacter*);
  public: CHARACTER::cCwGoliathCharacterWrapper& operator=(const CHARACTER::cCwGoliathCharacterWrapper&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
