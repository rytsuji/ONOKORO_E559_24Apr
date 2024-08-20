#ifndef TSPECTROMETERPROCESSOR_H
#define TSPECTROMETERPROCESSOR_H


#include "TProcessor.h"
#include "TEventCollection.h"
#include "TOpticsData.h"
#include "TParticleData.h"
#include <vector>

namespace art {
  class TSpectrometerProcessor;
}

class TClonesArray;

class art::TSpectrometerProcessor : public TProcessor {
public:
  TSpectrometerProcessor();
  virtual ~TSpectrometerProcessor();
  
  virtual void Init(TEventCollection *col);
  virtual void Process();

protected:  
  TString fNameInput;
  TString fNameOutput;

  TClonesArray **fInput;//!                                                                                                                                 
  TClonesArray *fOutput;//!                                                                                                                                  
  Int_t fVerbose;

  TString    fInputFileName;
  Double_t fMass;
  Int_t fAtomicNumber;
  Int_t fMassNumber;
  Double_t fRho;
  Double_t fMagneticField;
  Double_t fAngle;
  
private:
  
  ClassDef(TSpectrometerProcessor,1) 
};

#endif
