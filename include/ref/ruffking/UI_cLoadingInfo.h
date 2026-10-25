
class UI::cLoadingInfo : public RWS::CAttributeHandler { /* Size=0x4c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: unsigned int m_NameHash[4];
  /* 0x0028 */ private: float m_ExtraDisplayTime;
  /* 0x002c */ private: Fun_Runtime::cStringc m_ImageFile;
  /* 0x0048 */ private: bool m_bHasBeenViewed[4];
  public: static const char* pcLoadingInfoClassID;
  public: static const int kMaxImagesPerFile;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLoadingInfo(const UI::cLoadingInfo&);
  public: cLoadingInfo(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: bool HaveAllImagesBeenSeen() const;
  public: void ClearSeen();
  public: void SetAsSeen(int);
  public: bool SeenImage(int) const;
  public: bool HasImage(int) const;
  public: const char* ImageFile() const;
  public: unsigned int InfoText(int) const;
  public: virtual ~cLoadingInfo();
  public: UI::cLoadingInfo& operator=(const UI::cLoadingInfo&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
