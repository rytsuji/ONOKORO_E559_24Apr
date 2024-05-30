#ifndef TPIDCALIBRATIONROCESSOR_H
#define TPIDCALIBRATIONROCESSOR_H


#include "TProcessor.h"
#include "TEventCollection.h"
//#include "TTimingChargeData"
#include "TMWDCTrackingResult.h"
#include "TTrack.h"
#include <vector>

namespace art {
  class TPIDCalibrationProcessor;
}

class TClonesArray;

class art::TPIDCalibrationProcessor : public TProcessor {
public:
  TPIDCalibrationProcessor();
  virtual ~TPIDCalibrationProcessor();
  
  virtual void Init(TEventCollection *col);
  virtual void Process();

protected:  
  TString fTrackInputName;
  TString fTimingInputName;
  TString fChargeInputName;
  TString fOutputName;
  

  
  TClonesArray **fTrackInput;//!
  TClonesArray **fTimingInput;//!
  TClonesArray **fChargeInput;//!
  TClonesArray *fOutput;//!                                                                                                                                
  Int_t fVerbose;

  TString    fMatrixFileNameCharge;
  IntVec_t   fTermsCharge;
  FloatVec_t fCoefficientsCharge;
  
  
  TString    fMatrixFileNameTiming;
  IntVec_t   fTermsTiming;
  FloatVec_t fCoefficientsTiming;


  Int_t  fChargeType;
  
    
private:
  
  ClassDef(TPIDCalibrationProcessor,1) 
};

#endif
