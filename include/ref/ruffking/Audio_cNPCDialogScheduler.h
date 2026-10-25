
class Audio::cNPCDialogScheduler : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x144 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ private: float m_fDefaultTimePeriod;
  /* 0x001c */ private: float m_fEventTimePeriod[74];
  public: static const char m_cNPCDialogScheduler_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcNPCDialogSchedulerClass;
  public: static const char* pcNPCDialogSchedulerClassID;
  private: static Audio::cNPCDialogScheduler* ms_pInstance;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cNPCDialogScheduler(const Audio::cNPCDialogScheduler&);
  public: cNPCDialogScheduler(const RWS::CAttributePacket&);
  public: virtual ~cNPCDialogScheduler();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: float GetDefaultTimePeriod();
  public: float GetEventTimePeriod(Audio::etNPCDialogEvent);
  public: Audio::cNPCDialogScheduler& operator=(const Audio::cNPCDialogScheduler&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static Audio::cNPCDialogScheduler& RetInstance();
  public: static bool SchedulerAvailable();
};
