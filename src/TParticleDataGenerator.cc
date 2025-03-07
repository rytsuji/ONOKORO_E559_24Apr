/**
 * @file   TRandomNumberEventStore.cc
 * @date   Created : Jul 11, 2013 18:11:52 JST
 *   Last Modified : Feb 01, 2015 03:37:49 JST
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *  
 *  
 *    Copyright (C)2013
 */
#include "TParticleDataGenerator.h"
#include "TParticleData.h"
#include <TClonesArray.h>
#include <TClass.h>
#include <TLoop.h>
#include <TRandom.h>
//#include <TSimpleData.h>

ClassImp(art::TParticleDataGenerator);

art::TParticleDataGenerator::TParticleDataGenerator()
   : fNumLoop(0)
{
  //RegisterOutputCollection("OutputCollection","output name of random values",fOutputColName,TString("random"));
  RegisterOutputCollection("OutputCollection","output collection",
			   fNameOutput,"TParticleData",
                           &fOutput, TClonesArray::Class_Name(),
                           art::TParticleData::Class_Name());

  RegisterProcessorParameter("MaxLoop","the maximum number of loop",fMaxLoop,100);

  Register(fMass("Mass","mass of particle",0.0));
  
  RegisterProcessorParameter("TMin","the minimum value",fTMin,(float)0.);
  RegisterProcessorParameter("TMax","the maximum value",fTMax,(float)230.);
  
  RegisterProcessorParameter("ThetaMin","the minimum value",fThetaMin,(float)0.);
  RegisterProcessorParameter("ThetaMax","the maximum value",fThetaMax,(float)180.);
  
  RegisterProcessorParameter("PhiMin","the minimum value",fPhiMin,(float)0.);
  RegisterProcessorParameter("PhiMax","the maximum value",fPhiMax,(float)360.);

  
}
art::TParticleDataGenerator::~TParticleDataGenerator()
{
}


void art::TParticleDataGenerator::Init(TEventCollection *col)
{
   fNumLoop = 0;
   //fData = new TSimpleData;
   //col->Add(fOutputColName,fData,fOutputIsTransparent);
}
void art::TParticleDataGenerator::Process()
{

  Double_t TKE=gRandom->Uniform(fTMin,fTMax);  
  Double_t CosTheta=gRandom->Uniform(cos(TMath::DegToRad()*fThetaMax),cos(TMath::DegToRad()*fThetaMin));
  //Double_t Phi=TMath::DegToRad()*gRandom->Uniform(fPhiMin,fPhiMax);
  Double_t Phi=gRandom->Uniform(fPhiMin,fPhiMax);

  //fData->SetValue(gRandom->Uniform(fMin,fMax));


  TParticleData *outData = NULL;
  outData = static_cast<TParticleData*>(fOutput->ConstructedAt(0));
  outData->SetMass(fMass);
  outData->SetTKE(TKE);
  outData->SetTheta(TMath::RadToDeg()*acos(CosTheta));
  outData->SetPhi(Phi);
  
  fNumLoop++;
  
  if (fMaxLoop <= fNumLoop) {
    SetStopLoop();
    SetEndOfRun();
  }
}
