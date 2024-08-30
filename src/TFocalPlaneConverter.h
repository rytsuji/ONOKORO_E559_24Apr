#ifndef TFPCONVERTER_H
#define TFPCONVERTER_H


#include "TProcessor.h"
#include "TEventCollection.h"
#include "TMWDCTrackingResult.h"
#include "TTrack.h"
#include <vector>

namespace art {
  class TFocalPlaneConverter;
}

class TClonesArray;

class art::TFocalPlaneConverter : public TProcessor {
public:
  TFocalPlaneConverter();
  virtual ~TFocalPlaneConverter();
  
  virtual void Init(TEventCollection *col);
  virtual void Process();

protected:  
  TString fNameInput;
  TString fNameOutput;

  TClonesArray **fMWDCTrackIn;//!                                                                                                                                 
  TClonesArray *fMWDCTrackOut;//!                                                                                                                                  
  Int_t fVerbose;

  TString    fMatrixFileXName;
  IntVec_t   fTermsX;
  FloatVec_t fCoefficientsX;

  TString    fMatrixFileYName;
  IntVec_t   fTermsY;
  FloatVec_t fCoefficientsY;
  
  
  Parameter<Double_t> fOffsetX; // unit of mm
  Parameter<Double_t> fOffsetY; // unit of mm
  Parameter<Double_t> fOffsetZ; // unit of mm  
  

  
private:
  
  ClassDef(TFocalPlaneConverter,1) 
};

#endif
