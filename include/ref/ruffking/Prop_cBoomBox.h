
class Prop::cBoomBox : public Prop::cProp { /* Size=0xea0 */
  /* 0x0000: fields for Prop::cProp */
  public: static const char m_cBoomBox_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcBoomBoxClass;
  public: static const char* pcBoomBoxClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cBoomBox(const Prop::cBoomBox&);
  public: cBoomBox(GOM::cObjectPrototype*);
  public: virtual void PostTickUpdate(float);
  private: bool IsInCompletedCellStronghold() const;
  private: Prop::cBoomBoxPrototype& RetBoomBoxProto() const;
  public: virtual ~cBoomBox();
  public: Prop::cBoomBox& operator=(const Prop::cBoomBox&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
