#ifndef TMEANCHARGEPROCESSOR_H
#define TMEANCHARGEPROCESSOR_H


#include "TProcessor.h"
#include "TEventCollection.h"
#include <vector>

namespace art {
  class TMeanChargeProcessor;
}

class TClonesArray;

class art::TMeanChargeProcessor : public TProcessor {
public:
  TMeanChargeProcessor();
  virtual ~TMeanChargeProcessor();
  
  virtual void Init(TEventCollection *col);
  virtual void Process();

protected:  
  TString fTimingInputName;
  TString fChargeInputName;
  TString fOutputName;
  
  TClonesArray **fTimingInput;//!
  TClonesArray **fChargeInput;//!
  TClonesArray *fOutput;//!                                                                                                                                
  Int_t fVerbose;
  
private:
  FloatVec_t fValidChargeRange;
  Float_t fValidChargeMin;
  Float_t fValidChargeMax;
  ClassDef(TMeanChargeProcessor,1) 
};

#endif
