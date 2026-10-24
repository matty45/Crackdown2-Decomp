
class RWS::CClassFactory::CRegistrar { /* Size=0x1 */
  
  public: ~CRegistrar();
  public: CRegistrar(const char*, RWS::CAttributeHandler* (*)(const RWS::CAttributePacket&, bool), unsigned int, bool);
  public: void* __vecDelDtor(unsigned int);
};
