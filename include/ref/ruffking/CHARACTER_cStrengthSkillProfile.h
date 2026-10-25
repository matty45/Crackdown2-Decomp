
class CHARACTER::cStrengthSkillProfile : public cNonGameBase { /* Size=0x444 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac */ protected: Fun_Runtime::cString m_sProfileName;
  /* 0x00c8 */ protected: RWS::CEventId m_Msg_Return_Self;
  /* 0x00d0 */ public: float m_fMaxLiftMass;
  /* 0x00d4 */ public: float m_fMaxPushMass;
  /* 0x00d8 */ public: float m_fPushStrength;
  /* 0x00dc */ public: float m_fCharacterInteractionStrength;
  /* 0x00e0 */ public: float m_fLiftMassMultiForCarryEffectDownScaling;
  /* 0x00e4 */ public: float m_fUpperHand2HandRadiusMul;
  /* 0x00e8 */ public: float m_fAttackStrength;
  /* 0x00ec */ public: float m_fBargeAttackStrength;
  /* 0x00f0 */ public: float m_fNPCPropAttackStrength;
  /* 0x00f4 */ public: float m_fAttackForceMin[6][6];
  /* 0x0184 */ public: float m_fAttackForceMax[6][6];
  /* 0x0214 */ public: float m_fAttackMass[6][6];
  /* 0x02a4 */ public: float m_fAttackMinVerticalAngle[6];
  /* 0x02bc */ public: float m_fAttackMaxVerticalAngle[6];
  /* 0x02d4 */ public: float m_fAttackMinHorazontalAngle[6];
  /* 0x02ec */ public: float m_fAttackMaxHorazontalAngle[6];
  /* 0x0304 */ public: float m_fBargeSpeedReductionMin[6];
  /* 0x031c */ public: float m_fBargeSpeedReductionMax[6];
  /* 0x0334 */ public: float m_fGroundStrikeMinSpeed;
  /* 0x0338 */ public: float m_fGroundStrikeMaxSpeed;
  /* 0x033c */ public: float m_fGroundStrikeMinForce;
  /* 0x0340 */ public: float m_fGroundStrikeMaxForce;
  /* 0x0344 */ public: float m_fGroundStrikeMinForceRadius;
  /* 0x0348 */ public: float m_fGroundStrikeMaxForceRadius;
  /* 0x034c */ public: float m_fGroundStrikeMinDamage;
  /* 0x0350 */ public: float m_fGroundStrikeMaxDamage;
  /* 0x0354 */ public: float m_fGroundStrikeMinDamageRadius;
  /* 0x0358 */ public: float m_fGroundStrikeMaxDamageRadius;
  /* 0x035c */ public: float m_fGroundStrikeAccelDownTweak;
  /* 0x0360 */ public: float m_fRushAtkHigh_VelBoost;
  /* 0x0364 */ public: float m_fRushAtkHigh_RunningTargetVelBoost;
  /* 0x0368 */ public: float m_fThrowVelocityIncrementMaxTime;
  /* 0x036c */ public: float m_fThrowRandomAngle;
  /* 0x0370 */ public: float m_fThrowMinVelocity[6];
  /* 0x0388 */ public: float m_fThrowMaxVelocity[6];
  /* 0x03a0 */ public: float m_fThrowMaxMass[6];
  /* 0x03b8 */ public: CHARACTER::tThrowSetupData m_aThrowSetupData[2];
  /* 0x03e8 */ public: float m_fFullHealth;
  /* 0x03ec */ public: float m_fHealthFraction;
  /* 0x03f0 */ public: float m_fLimboTime;
  /* 0x03f4 */ public: float m_fFireDamageModifier;
  /* 0x03f8 */ public: unsigned int m_nNumFramesDisabledDamageReactionPostStunned;
  /* 0x03fc */ public: unsigned short m_nMinNumFlinchFrames;
  /* 0x03fe */ public: unsigned short m_nMaxNumFlinchFrames;
  /* 0x0400 */ public: unsigned short m_nMinNumFlinchDisabledFrames;
  /* 0x0402 */ public: unsigned short m_nMaxNumFlinchDisabledFrames;
  /* 0x0404 */ public: float m_fForceThreshhold;
  /* 0x0408 */ public: float m_fMainFireArmFlinchThreshhold;
  /* 0x040c */ public: float m_fHeadFireArmFlinchThreshhold;
  /* 0x0410 */ public: float m_fArmFireArmFlinchThreshhold;
  /* 0x0414 */ public: float m_fLegFireArmFlinchThreshhold;
  /* 0x0418 */ public: float m_fMainCollisionFlinchThreshhold;
  /* 0x041c */ public: float m_fMainFireArmRagdollThreshhold;
  /* 0x0420 */ public: float m_fMainFightingRagdollThreshhold;
  /* 0x0424 */ public: float m_fMainCollisionRagdollThreshhold;
  /* 0x0428 */ public: float m_fMainFireArmDamageThreshhold;
  /* 0x042c */ public: float m_fHeadFireArmDamageThreshhold;
  /* 0x0430 */ public: float m_fArmFireArmDamageThreshhold;
  /* 0x0434 */ public: float m_fLegFireArmDamageThreshhold;
  /* 0x0438 */ public: float m_fMainCollisionDamageThreshhold;
  /* 0x043c */ public: float m_fRagdollCollisionDamageModifier;
  /* 0x0440 */ public: unsigned char m_bStandardAtkLow_HighImpact : 1; /* BitPos=0 */
  /* 0x0440 */ public: unsigned char m_bRushAtkHigh_HighImpact : 1; /* BitPos=1 */
  /* 0x0440 */ public: unsigned char m_bRushAtkLow_HighImpact : 1; /* BitPos=2 */
  /* 0x0440 */ public: unsigned char m_bDamageReactionWhileStunned : 1; /* BitPos=3 */
  /* 0x0440 */ public: unsigned char m_bDisableArmShotsIfOnlyOneWeapon : 1; /* BitPos=4 */
  /* 0x0440 */ public: unsigned char m_bDisableArmShots : 1; /* BitPos=5 */
  /* 0x0440 */ public: unsigned char m_bDisableMovementFlinch : 1; /* BitPos=6 */
  /* 0x0440 */ public: unsigned char m_bDisableFlinch : 1; /* BitPos=7 */
  /* 0x0440 */ unsigned char : 0; /* BitPos=8 */
  /* 0x0441 */ public: unsigned char m_bAttackHighImpact : 1; /* BitPos=5 */
  /* 0x0441 */ public: unsigned char m_bStompAtk_HighImpact : 1; /* BitPos=6 */
  /* 0x0441 */ public: unsigned char m_bStandardAtkHigh_HighImpact : 1; /* BitPos=7 */
  public: static const char* pcStrengthSkillProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cStrengthSkillProfile(const CHARACTER::cStrengthSkillProfile&);
  public: cStrengthSkillProfile(const RWS::CAttributePacket&);
  public: virtual ~cStrengthSkillProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: float RetHitHorazontalAngle(unsigned int) const;
  public: float RetHitVerticalAngle(unsigned int) const;
  public: float RetHitForce(float, unsigned int) const;
  public: float RetThrowForce(float, float) const;
  public: float RetBargeSpeedReduction(float) const;
  public: unsigned int RetMaxNumFlinchFrames() const;
  public: unsigned int RetMaxNumFlinchDisabledFrames() const;
  public: bool IsFlinchDisabled() const;
  public: bool IsMovementFlinchDisabled() const;
  public: CHARACTER::cStrengthSkillProfile& operator=(const CHARACTER::cStrengthSkillProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
