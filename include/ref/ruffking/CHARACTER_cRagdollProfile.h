
class CHARACTER::cRagdollProfile : public cNonGameBase { /* Size=0x3e0 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00b0 */ public: hkVector4 m_BoneSize[13];
  /* 0x0180 */ public: CHARACTER::tRJointInfo m_RJointInfo[6];
  /* 0x0228 */ public: CHARACTER::tHJointInfo m_HJointInfo[6];
  /* 0x0270 */ public: CHARACTER::tTorsoDimensions m_Dim;
  /* 0x0294 */ public: char m_Map[13];
  /* 0x02a4 */ public: float m_BoneMass[13];
  /* 0x02d8 */ public: float m_fShotGlobalForce;
  /* 0x02dc */ public: float m_fShotLocalForce;
  /* 0x02e0 */ public: float m_fLinearDamping;
  /* 0x02e4 */ public: float m_fAngularDamping;
  /* 0x02e8 */ public: float m_fFriction;
  /* 0x02ec */ public: float m_fRestitution;
  /* 0x02f0 */ public: float m_fPCM_Tau;
  /* 0x02f4 */ public: float m_fPCM_Damping;
  /* 0x02f8 */ public: float m_fPCM_MaxForce;
  /* 0x02fc */ public: float m_fPCM_PropRecVel;
  /* 0x0300 */ public: float m_fPCM_ConstRecVel;
  /* 0x0304 */ public: hkKeyFrameHierarchyUtility::ControlData m_normalControlData;
  /* 0x0334 */ public: hkKeyFrameHierarchyUtility::ControlData m_carriedControlData;
  /* 0x0364 */ public: hkKeyFrameHierarchyUtility::ControlData m_floppyControlData;
  /* 0x0394 */ public: float m_fHandSpan;
  /* 0x03a0 */ public: hkVector4 m_CarryOffset;
  /* 0x03b0 */ private: Fun_Runtime::cString m_sProfileName;
  /* 0x03cc */ private: RWS::CEventId m_Msg_Return_Self;
  /* 0x03d4 */ private: RWS::CEventId m_Msg_Data_Modified;
  public: static const char m_cRagdollProfile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcRagdollProfileClass;
  public: static const char* pcRagdollProfileClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: cRagdollProfile(const CHARACTER::cRagdollProfile&);
  public: cRagdollProfile(const RWS::CAttributePacket&);
  public: virtual ~cRagdollProfile();
  public: const Fun_Runtime::cString& RetProfileName() const;
  public: CHARACTER::cRagdollProfile& operator=(const CHARACTER::cRagdollProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
