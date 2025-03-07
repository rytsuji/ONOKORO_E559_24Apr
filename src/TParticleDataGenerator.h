/* $Id:$ */
/**
 * @file   TRandomNumberEventStore.h
 * @date   Created : Jul 11, 2013 18:11:07 JST
 *   Last Modified : 2021-12-08 13:57:18 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *  
 *  
 *    Copyright (C)2013
 */
#ifndef TPARTICLEDATAGENERATOR_H
#define TPARTICLEDATAGENERATOR_H

#include "TProcessor.h"
#include "TConditionBit.h"
#include "IEventStore.h"
#include "TParticleData.h"
//#include "TSimpleData.h"

namespace art {

   class TParticleDataGenerator;
}


class art::TParticleDataGenerator  : public TProcessor, public IEventStore {

public:
   TParticleDataGenerator();
   ~TParticleDataGenerator();

   virtual void Init(TEventCollection *col);
   virtual void Process();
   
private:
  Int_t           fNumLoop; //! local variable
  Int_t           fMaxLoop;

  Float_t        fTMin;
  Float_t        fTMax;
  Float_t        fThetaMin;
  Float_t        fThetaMax;
  Float_t        fPhiMin;
  Float_t        fPhiMax;

  Parameter<Double_t> fMass;

  TString fNameOutput;
  TClonesArray *fOutput;
  
  //TSimpleData    *fData;
  //TString         fOutputColName;
  

   ClassDef(TParticleDataGenerator,1);
};

#endif // end of #ifdef TRANDOMNUMBEREVENTSTORE_H
