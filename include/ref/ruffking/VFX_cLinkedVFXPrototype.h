
class VFX::cLinkedVFXPrototype : public VFX::cAmbientVFXPrototypeBase { /* Size=0x44 */
  /* 0x0000: fields for VFX::cAmbientVFXPrototypeBase */
  /* 0x0030 */ public: Editor::cGUIDEventHandler<VFX::cLinkedVFXPrototype> m_EventHandler;
  public: static const char* pcLinkedVFXPrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLinkedVFXPrototype(const VFX::cLinkedVFXPrototype&);
  public: cLinkedVFXPrototype(const RWS::CAttributePacket&);
  public: virtual ~cLinkedVFXPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: VFX::cLinkedVFXPrototype& operator=(const VFX::cLinkedVFXPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
