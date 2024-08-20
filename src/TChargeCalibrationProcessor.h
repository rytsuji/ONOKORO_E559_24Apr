#ifndef TCHARGECALIBRATIONROCESSOR_H
#define TCHARGECALIBRATIONROCESSOR_H


#include "TProcessor.h"
#include "TEventCollection.h"
//#include "TTimingChargeData"
#include "TMWDCTrackingResult.h"
#include "TTrack.h"
#include <vector>

namespace art {
  class TChargeCalibrationProcessor;
}

class TClonesArray;

class art::TChargeCalibrationProcessor : public TProcessor {
public:
  TChargeCalibrationProcessor();
  virtual ~TChargeCalibrationProcessor();
  
  virtual void Init(TEventCollection *col);
  virtual void Process();

protected:  
  TString fTrackInputName;
  TString fTimingInputName;
  TString fChargeInputName;
  //TString fOpticsInputName;
  TString fOutputName;
  

  
  TClonesArray **fTrackInput;//!
  TClonesArray **fTimingInput;//!
  TClonesArray **fChargeInput;//!
  TClonesArray *fOutput;//!                                                                                                                                
  Int_t fVerbose;

  TString    fMatrixFileName;
  IntVec_t   fTermsCharge;
  FloatVec_t fCoefficientsCharge;

  Int_t  fChargeType;
  
    
private:
  
  ClassDef(TChargeCalibrationProcessor,1) 
};

#endif
