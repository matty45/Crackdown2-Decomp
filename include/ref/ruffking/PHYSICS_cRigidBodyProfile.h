
class PHYSICS::cRigidBodyProfile : public PHYSICS::cRigidBodyData, public cNonGameBase { /* Size=0x230 */
  /* 0x0000: fields for PHYSICS::cRigidBodyData */
  /* 0x0160: fields for cNonGameBase */
  /* 0x020c */ protected: Fun_Runtime::cString m_sProfileName;
  /* 0x0228 */ protected: RWS::CEventId m_Msg_Return_RB_Self;
  public: static const char* pcRigidBodyProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cRigidBodyProfile(const PHYSICS::cRigidBodyProfile&);
  public: cRigidBodyProfile(const RWS::CAttributePacket&);
  public: virtual ~cRigidBodyProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleResources(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: const Fun_Runtime::cString& RetProfileName() const;
  public: PHYSICS::cRigidBodyProfile& operator=(const PHYSICS::cRigidBodyProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
