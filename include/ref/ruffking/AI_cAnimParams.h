
class AI::cAnimParams : public RWS::CAttributeHandler { /* Size=0x48 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: int m_nAnimID;
  /* 0x001c */ private: char m_nMinLoop;
  /* 0x001d */ private: char m_nMaxLoop;
  /* 0x0020 */ private: float m_fBlendIn;
  /* 0x0024 */ private: float m_fSpeedMin;
  /* 0x0028 */ private: float m_fSpeedMax;
  /* 0x002c */ private: float m_fWeight;
  /* 0x0030 */ private: bool m_bPlayBackToBack;
  /* 0x0034 */ private: Editor::cGUIDEventHandler<AI::cAnimParams> m_EventHandler;
  public: static const char m_cAnimParams_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAnimParamsClass;
  public: static const char* pcAnimParamsClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAnimParams(const AI::cAnimParams&);
  public: cAnimParams(const RWS::CAttributePacket&);
  public: virtual ~cAnimParams();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: int RetAnimID();
  public: float RetMaxRate();
  public: float RetMinRate();
  public: float RetBlendTime();
  public: char RetMinLoop();
  public: char RetMaxLoop();
  public: float RetWeight();
  public: bool RetPlayBackToBack();
  public: void SetMinLoop(char);
  public: void SetMaxLoop(char);
  public: void SetAnimID(int);
  public: void SetBlendSpeed(float);
  public: void SetMinSpeed(float);
  public: void SetMaxSpeed(float);
  public: void SetWeight(float);
  public: void SetPlayBackToBack(bool);
  public: AI::cAnimParams& operator=(const AI::cAnimParams&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
