
class Prop::cPintleFaceplate : public Prop::cProp { /* Size=0xeb0 */
  /* 0x0000: fields for Prop::cProp */
  /* 0x0ea0 */ private: Vehicle::cPintleMount* m_pParentPintleMount;
  public: static const char m_cPintleFaceplate_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcPintleFaceplateClass;
  public: static const char* pcPintleFaceplateClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPintleFaceplate(const Prop::cPintleFaceplate&);
  public: cPintleFaceplate(GOM::cObjectPrototype*);
  public: virtual ~cPintleFaceplate();
  public: virtual bool EnterPhysicalState();
  public: virtual void EnterGhostState();
  public: virtual void LeaveGhostState();
  public: void SetParentPintleMount(Vehicle::cPintleMount*);
  public: void ForceUpdateRenderMatrix();
  public: Prop::cPintleFaceplate& operator=(const Prop::cPintleFaceplate&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
