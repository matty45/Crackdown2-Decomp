
class ZoneManager::cReverbZone : public ZoneManager::cPlayerTriggerZone { /* Size=0x150 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerZone */
  /* 0x00e0 */ private: Fun_Runtime::cString m_strName;
  /* 0x00fc */ private: unsigned int m_nType;
  /* 0x0100 */ private: unsigned int m_nLayerType;
  /* 0x0104 */ private: unsigned int m_nWetLevel;
  /* 0x0108 */ private: unsigned int m_nDryLevel;
  /* 0x010c */ private: unsigned int m_nHFRatio;
  /* 0x0110 */ private: unsigned int m_nReverbTime;
  /* 0x0114 */ private: unsigned int m_nReverbDiffusion;
  /* 0x0118 */ private: unsigned int m_nReverbERLevel;
  /* 0x011c */ private: unsigned int m_nReverbEQ1Gain;
  /* 0x0120 */ private: unsigned int m_nReverbEQ1Freq;
  /* 0x0124 */ private: unsigned int m_nReverbEQ1Q;
  /* 0x0128 */ private: unsigned int m_nReverbEQ2Gain;
  /* 0x012c */ private: unsigned int m_nReverbEQ2Freq;
  /* 0x0130 */ private: unsigned int m_nReverbEQ2Q;
  /* 0x0134 */ private: unsigned int m_nReverbEQ3Gain;
  /* 0x0138 */ private: unsigned int m_nReverbEQ3Freq;
  /* 0x013c */ private: unsigned int m_nReverbEQ3Q;
  /* 0x0140 */ private: unsigned int m_nDebugZoneColour;
  /* 0x0144 */ private: bool m_bPreviouslyEntered;
  /* 0x0145 */ private: bool m_bPreviouslyLeft;
  public: static const char* pcReverbZoneClassID;
  private: static int s_reverbZone;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cReverbZone(const ZoneManager::cReverbZone&);
  public: cReverbZone(const RWS::CAttributePacket&);
  public: virtual ~cReverbZone();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void InitTriggerZone();
  public: virtual void TermTriggerZone();
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: virtual void DebugDrawTriggerZone();
  public: ZoneManager::cReverbZone& operator=(const ZoneManager::cReverbZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static bool IsReverb();
};
