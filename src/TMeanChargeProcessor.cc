#include "TMeanChargeProcessor.h"
#include "constant.h"
#include <iostream>
#include <string>
#include <fstream>
#include "TDataObject.h"
#include "ITiming.h"
#include "ICharge.h"
#include <TOpticsData.h>
#include "TTimingChargeData.h"
#include <TClonesArray.h>
#include <TClass.h>
#include <TSimpleData.h>
#include <yaml-cpp/yaml.h>


using art::TMeanChargeProcessor;


ClassImp(TMeanChargeProcessor)

TMeanChargeProcessor::TMeanChargeProcessor()
: fOutput(NULL)
{
  const FloatVec_t range(3,0.);
  RegisterProcessorParameter("ValidChargeRange","[min,max,offset] => Tmin = offset + min etc. ignored if min == max",
                              fValidChargeRange,range);
  
  RegisterInputCollection("InputCollectionTiming", "array of objects inheriting from art::ITiming and/or art::ICharge",
			  fTimingInputName, TString("input_timing"), &fTimingInput,
			  TClonesArray::Class_Name(),ITiming::Class_Name());
  
  RegisterInputCollection("InputCollectionCharge", "array of objects inheriting from art::ITiming and/or art::ICharge",
			  fChargeInputName, TString("input_charge"), &fChargeInput,
			  TClonesArray::Class_Name(),ICharge::Class_Name());
  
  RegisterOutputCollection("OutputCollection","output class will be the same as input",
                            fOutputName,TString("calibrated plastic"),
			    &fOutput, TClonesArray::Class_Name(),
			    art::TTimingChargeData::Class_Name());

}


TMeanChargeProcessor::~TMeanChargeProcessor()
{
  delete fOutput;
}

namespace {
}


void TMeanChargeProcessor::Init(TEventCollection* col){
  if (fValidChargeRange[0] > fValidChargeRange[1]) {                                                                                                             
    SetStateError("Charge range : min > max");                                                                                                                  
    return;
  }                                                                                                                                                             
  
  fValidChargeMin = fValidChargeRange[2] + fValidChargeRange[0];
  fValidChargeMax = fValidChargeRange[2] + fValidChargeRange[1];
}

void TMeanChargeProcessor::Process(){
  
  fOutput->Clear("C");
  Bool_t kProcessed = kFALSE;

  //if((*fTimingInput)->GetEntriesFast()>0){
  if((*fChargeInput)->GetEntriesFast()>0){  
    const TDataObject *const inDataT = static_cast<TDataObject*>((*fTimingInput)->At(0));
    const ITiming *const timingData = dynamic_cast<const ITiming*>(inDataT);
    Double_t timing = timingData->GetTiming();
    Double_t charge = 0;
  
    
    //Mean TOT
    const Int_t nDataQ = (*fChargeInput)->GetEntriesFast();
    int nValidQ=0;
    
    for(int iDataQ=0; iDataQ < nDataQ; iDataQ++){
      const TDataObject *const inDataQ = static_cast<TDataObject*>((*fChargeInput)->At(iDataQ));
      const ICharge *const chargeData = dynamic_cast<const ICharge*>(inDataQ);
      
      //if(chargeData->GetCharge()>fValidChargeMin && chargeData->GetCharge()<fValidChargeMax){
      if(isfinite(chargeData->GetCharge())){
	charge +=  (Double_t) chargeData->GetCharge() ;
	nValidQ++;
      }
    }
    
    TObject *const outData = fOutput->ConstructedAt(0);    
    Double_t outTiming=timing;  
    ITiming *const outDataT = dynamic_cast<ITiming*>(outData);
    outDataT->SetTiming(outTiming);
    if(nValidQ>0){
      Double_t outCharge=charge/nValidQ;
      ICharge *const outDataQ = dynamic_cast<ICharge*>(outData);
      outDataQ->SetCharge(outCharge);
    }else{
      //ICharge *const outDataQ = dynamic_cast<ICharge*>(outData);
      //outDataQ->SetCharge(-9999.0);
    }
  }
  return;
}
  


