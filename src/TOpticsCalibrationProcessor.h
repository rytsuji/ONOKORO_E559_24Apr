#ifndef TOPTICSCALIBRATIONROCESSOR_H
#define TOPTICSCALIBRATIONROCESSOR_H


#include "TProcessor.h"
#include "TEventCollection.h"
#include "TOpticsData.h"
#include "TMWDCTrackingResult.h"
#include "TTrack.h"
#include <vector>

namespace art {
  class TOpticsCalibrationProcessor;
}

class TClonesArray;

class art::TOpticsCalibrationProcessor : public TProcessor {
public:
  TOpticsCalibrationProcessor();
  virtual ~TOpticsCalibrationProcessor();
  
  virtual void Init(TEventCollection *col);
  virtual void Process();

protected:  
  TString fNameInput;
  TString fNameOutput;

  TClonesArray **fInput;//!                                                                                                                                 
  TClonesArray *fOutput;//!                                                                                                                                  
  Int_t fVerbose;

  TString    fMatrixFileNameDelta;
  IntVec_t   fTermsDelta;
  FloatVec_t fCoefficientsDelta;
  
  
  TString    fMatrixFileNameA;
  IntVec_t   fTermsA;
  FloatVec_t fCoefficientsA;

  TString    fMatrixFileNameB;
  IntVec_t   fTermsB;
  FloatVec_t fCoefficientsB;
  Float_t fYBtgt;  
  Float_t fYBXtgt; //Btgt=Yfp(fYBtgt+fYBXtgt*x)+h.o.


  TString    fMatrixFileNameZ;
  IntVec_t   fTermsZ;
  FloatVec_t fCoefficientsZ;
  
private:
  
  ClassDef(TOpticsCalibrationProcessor,1) 
};

#endif
