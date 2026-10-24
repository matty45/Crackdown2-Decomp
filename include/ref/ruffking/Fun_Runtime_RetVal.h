
class Fun_Runtime::RetVal { /* Size=0x4 */
  /* 0x0000 */ private: int m_nVal;
  
  public: RetVal(int);
  public: RetVal();
  public: int GetVal() const;
  public: int operator int() const;
};
