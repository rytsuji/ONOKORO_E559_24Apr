#ifndef TPARTICLEDATASIMLATOR_H
#define TPARTICLEDATASIMLATOR_H


#include "TProcessor.h"
#include "TEventCollection.h"
#include "TOpticsData.h"
#include "TSimpleData.h"
#include <vector>

namespace art {
  class TParticleDataSimulator;
}

class TClonesArray;

class art::TParticleDataSimulator : public TProcessor {
public:
  TParticleDataSimulator();
  virtual ~TParticleDataSimulator();
  
  virtual void Init(TEventCollection *col);
  virtual void Process();

protected:  

  TString    fNameKineticEInput;
  TString    fNameThetaInput;
  TString    fNamePhiInput;    
  TString fNameOutput;

  TClonesArray **fKineticEInput;//!
  TClonesArray **fThetaInput;//!
  TClonesArray **fPhiInput;//!                                                                                                                                   
  TClonesArray *fOutput;//!                                                                                                                                  
  Int_t fVerbose;
  Parameter<Double_t> fMass;
    
private:
  
  ClassDef(TParticleDataSimulator,1) 
};

#endif
