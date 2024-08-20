#include "TChargeCalibrationProcessor.h"
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


using art::TChargeCalibrationProcessor;


ClassImp(TChargeCalibrationProcessor)

TChargeCalibrationProcessor::TChargeCalibrationProcessor()
: fOutput(NULL)
{


  RegisterProcessorParameter("MatrixFile","path to the matrix file Charge",
			      fMatrixFileName,TString("path/to/file_Charge"));

  RegisterInputCollection("InputCollectionTiming", "array of objects inheriting from art::ITiming and/or art::ICharge",
			  fTimingInputName, TString("input_timing"), &fTimingInput,
			  TClonesArray::Class_Name(),ITiming::Class_Name());
  
  RegisterInputCollection("InputCollectionCharge", "array of objects inheriting from art::ITiming and/or art::ICharge",
			  fChargeInputName, TString("input_charge"), &fChargeInput,
			  TClonesArray::Class_Name(),ICharge::Class_Name());
  
  RegisterInputCollection("InputCollectionTrack",
			  "input collection tracking",
			  fTrackInputName, "mwdc_track",
			  &fTrackInput, TClonesArray::Class_Name(),
			  art::TMWDCTrackingResult::Class_Name());
  
   RegisterOutputCollection("OutputCollection","output class will be the same as input",
                            fOutputName,TString("calibrated plastic"),
			    &fOutput, TClonesArray::Class_Name(),
			    art::TTimingChargeData::Class_Name());

   RegisterProcessorParameter("ChargeTypeID","data type id for charge information (valid when ChargeType != (0 (mean TOT) or 2 (plastic)) , default: 2)",
                              fChargeType,2);
}


TChargeCalibrationProcessor::~TChargeCalibrationProcessor()
{
  delete fOutput;
}

namespace {
   const Int_t kDimension = 4;
   const char kXYAB[kDimension] = {'X', 'Y', 'A', 'B'};
   enum EOrder { kX=0, kY, kA, kB};
   const Int_t kShift = 4;
   const Int_t kMask  = 0x7;
   const Int_t kMaxDegree = 7;

   Int_t KeyToInt(const std::string& key)
   {
      TString key_(key);
      key_.ToUpper();

      Int_t ret = 0;

      for (Int_t i = 0; i != kDimension; ++i) {
	 const Int_t degree = key_.CountChar(kXYAB[i]);
	 if (degree > kMaxDegree) {
	    printf("Maximum Degree is %d for each matrix element.\n",kMaxDegree);
	    return 0;
	 }
	 ret += degree << (i * kShift);
      }

      return ret;
   }
}


void TChargeCalibrationProcessor::Init(TEventCollection* col){
  
  //Charge
  std::ifstream finCharge(fMatrixFileName.Data());
  if(!finCharge.is_open()) {
    SetStateError(TString::Format("Cannot open configuration file: %s",fMatrixFileName.Data()));
    return;
  }
  
  try {
    YAML::Node matrix;
    matrix = YAML::Load(finCharge);
    for(auto element : matrix) {
      std::string key = element.first.as<std::string>();
      Float_t value = element.second.as<Float_t>();       
      Int_t term = KeyToInt(key);
      
      
      if (term) {
	fTermsCharge.push_back(term);
	fCoefficientsCharge.push_back(value);
      }
    }
  } catch (YAML::Exception& e) {
    SetStateError(TString::Format("Error Occurred while loading matrix file\n%s\n",
				  e.what()));
    return;
  }
  
  
}

void TChargeCalibrationProcessor::Process(){
  
  fOutput->Clear("C");
  Bool_t kProcessed = kFALSE;
  
  //if ((*fTrackInput)->GetEntriesFast() < 1 || (*fTimingInput)->GetEntriesFast()<1 || (*fChargeInput)->GetEntriesFast()<1 || (*fOpticsInput)->GetEntriesFast() < 1) {

  if ((*fTrackInput)->GetEntriesFast() < 1 || (*fTimingInput)->GetEntriesFast()<1 || (*fChargeInput)->GetEntriesFast()<1 ) {
    kProcessed = kFALSE;    
  }
  else {
    kProcessed = kTRUE;
        

    const TDataObject *const inDataT = static_cast<TDataObject*>((*fTimingInput)->At(0));
    const ITiming *const timingData = dynamic_cast<const ITiming*>(inDataT);
    Double_t timing = timingData->GetTiming();

    Double_t charge = 0;
    
    if(fChargeType == 2){

      //Plastic

      const TDataObject *const inDataQ = static_cast<TDataObject*>((*fChargeInput)->At(0));
      const ICharge *const chargeData = dynamic_cast<const ICharge*>(inDataQ);
      charge = chargeData->GetCharge();      
      
    }else if(fChargeType == 0){

      const Int_t nDataQ = (*fChargeInput)->GetEntriesFast();
      //Mean TOT

      for(int iDataQ=0; iDataQ < nDataQ; iDataQ++){
	const TDataObject *const inDataQ = static_cast<TDataObject*>((*fChargeInput)->At(iDataQ));
	const ICharge *const chargeData = dynamic_cast<const ICharge*>(inDataQ);
	charge += ( (Double_t) chargeData->GetCharge() )/( (Double_t) nDataQ );
      }
    }else{
      
    }

    TObject *const outData = fOutput->ConstructedAt(0);    
    Double_t outTiming=timing;
    Double_t outCharge=charge;
    
    const TMWDCTrackingResult *const inTrackData = static_cast<TMWDCTrackingResult*>((*fTrackInput)->At(0));
    const TTrack *const track= dynamic_cast<const TTrack*> (inTrackData->GetTrack());
      
    Double_t xyab[kDimension];      
    xyab[0] = track->GetX();
    xyab[1] = track->GetY();
    xyab[2] = (track->GetA());
    xyab[3] = (track->GetB());
    /*
    TOpticsData *const inData = static_cast<TOpticsData*>((*fOpticsInput)->At(0));
    double Delta = inData->GetDelta();
    */
    for (Int_t i = 0, n = fTermsCharge.size(); i != n; ++i) {
      Double_t elem = 1.;
      for (Int_t j = 0; j != kDimension; ++j) {
	const Int_t power = (fTermsCharge[i] >> (j * kShift) & kMask);
	elem *= TMath::Power(xyab[j],power);
      }
      outCharge += elem * fCoefficientsCharge[i];
    }
    
    ITiming *const outDataT = dynamic_cast<ITiming*>(outData);
    outDataT->SetTiming(outTiming);
    ICharge *const outDataQ = dynamic_cast<ICharge*>(outData);
    outDataQ->SetCharge(outCharge);
    
  }
  return;
}
  


