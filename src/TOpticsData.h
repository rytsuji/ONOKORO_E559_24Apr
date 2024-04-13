#ifndef TOPTICSDATA_H
#define TOPTICSDATA_H

#include "TDataObject.h"

namespace art {
   class TOpticsData;
}

class art::TOpticsData : public TDataObject {
public:
  TOpticsData();
  virtual ~TOpticsData();
  
  TOpticsData(const TOpticsData& rhs);
  virtual void Clear(const Option_t* = "");
  TOpticsData& operator=(const TOpticsData& rhs);
  void SetDelta(Double_t val){ fDelta = val;}
  Double_t GetDelta(){ return fDelta; }
  void SetA(Double_t val){ fA = val; }
  Double_t GetA(){ return fA; }
  void SetB(Double_t val){ fB = val; }
  Double_t GetB(){ return fB; }
  
  Bool_t IsProcessed() const { return kProcessed; }
  void SetProcessed(Bool_t val) { kProcessed = val; }
  
 protected:
  Double_t fDelta;
  Double_t fA;
  Double_t fB;
  Bool_t kProcessed;
  
 private:
  
  ClassDef(TOpticsData,1) 
};

#endif //TOPTICSDATA_H       
