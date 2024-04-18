#include "TOpticsCalibrationProcessor.h"

#include "constant.h"
#include <iostream>
#include <string>
#include <fstream>
//#include "TDataObject.h"

#include <TClonesArray.h>
#include <TClass.h>
#include <TSimpleData.h>
#include <yaml-cpp/yaml.h>


using art::TOpticsCalibrationProcessor;


ClassImp(TOpticsCalibrationProcessor)

TOpticsCalibrationProcessor::TOpticsCalibrationProcessor()
: fOutput(NULL)
{


  RegisterProcessorParameter("MatrixFileDelta","path to the matrix file delta",
			      fMatrixFileNameDelta,TString("path/to/file_delta"));
  RegisterProcessorParameter("MatrixFileA","path to the matrix file A",
			      fMatrixFileNameA,TString("path/to/file_A"));
  RegisterProcessorParameter("MatrixFileB","path to the matrix file B",
			      fMatrixFileNameB,TString("path/to/file_B"));  


  RegisterInputCollection("InputCollection",
                           "input collection",
                           fNameInput, "mwdc_track",
			  &fInput, TClonesArray::Class_Name(),
			  art::TMWDCTrackingResult::Class_Name());

  RegisterOutputCollection("OutputCollection","output collection",
                            fNameOutput,"optics",
                            &fOutput, TClonesArray::Class_Name(),
                            art::TOpticsData::Class_Name());
}


TOpticsCalibrationProcessor::~TOpticsCalibrationProcessor()
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


void TOpticsCalibrationProcessor::Init(TEventCollection*){
  std::ifstream finDelta(fMatrixFileNameDelta.Data());

  //Delta
  if(!finDelta.is_open()) {
      SetStateError(TString::Format("Cannot open configuration file: %s",fMatrixFileNameDelta.Data()));
      return;
   }

   try {
     YAML::Node matrix;
     matrix = YAML::Load(finDelta);
     for(auto element : matrix) {
       std::string key = element.first.as<std::string>();
       Float_t value = element.second.as<Float_t>();       
       Int_t term = KeyToInt(key);
       
       
       if (term) {
	 fTermsDelta.push_back(term);
	 fCoefficientsDelta.push_back(value);
       }
     }
   } catch (YAML::Exception& e) {
     SetStateError(TString::Format("Error Occurred while loading matrix file\n%s\n",
				   e.what()));
     return;
   }


   //A   
   std::ifstream finA(fMatrixFileNameA.Data());
   if(!finDelta.is_open()) {
     SetStateError(TString::Format("Cannot open configuration file: %s",fMatrixFileNameA.Data()));
      return;
   }   
   try {
     YAML::Node matrix;
     matrix = YAML::Load(finA);
     for(auto element : matrix) {
       std::string key = element.first.as<std::string>();
       Float_t value = element.second.as<Float_t>();       
       Int_t term = KeyToInt(key);
       
       if (term) {
	 fTermsA.push_back(term);
	 fCoefficientsA.push_back(value);
       }
      }
   } catch (YAML::Exception& e) {
     SetStateError(TString::Format("Error Occurred while loading matrix file\n%s\n",
				   e.what()));
     return;
   }


   
   //B
   std::ifstream finB(fMatrixFileNameB.Data());   
   if(!finB.is_open()) {
     SetStateError(TString::Format("Cannot open configuration file: %s",fMatrixFileNameB.Data()));
     return;
   }
   try {

     YAML::Node matrix;
     matrix = YAML::Load(finB);
     for(auto element : matrix) {
       std::string key = element.first.as<std::string>();
       Float_t value = element.second.as<Float_t>();       
       Int_t term = KeyToInt(key);
       
	
	if (term) {
	  fTermsB.push_back(term);
	  fCoefficientsB.push_back(value);
	}
      }
   } catch (YAML::Exception& e) {
     SetStateError(TString::Format("Error Occurred while loading matrix file\n%s\n",
				   e.what()));
     return;
   }

   
   
}

void TOpticsCalibrationProcessor::Process(){

  fOutput->Clear("C");
  //(*fInput)->Sort();
  Bool_t kProcessed = kFALSE;
  const Int_t nData = (*fInput)->GetEntriesFast();

  
  
  
  if (nData < 1) {
    //if (fVerbose) std::cout << "Multiplicity is" << nData << ", cannot process" << std::endl;
    kProcessed = kFALSE;    
  }
  else {
    kProcessed = kTRUE;
    Double_t Delta=0;
    Double_t A=0;
    Double_t B=0;
    
    for (Int_t iData = 0; iData != nData; ++iData) {
      
      //TOpticsData *const outData = fOutData->ConstructedAt(iData);
      TOpticsData *outData = NULL;
      outData = static_cast<TOpticsData*>(fOutput->ConstructedAt(iData));
      const TMWDCTrackingResult *const inData = static_cast<TMWDCTrackingResult*>((*fInput)->At(iData));
      const TTrack *const track= dynamic_cast<const TTrack*> (inData->GetTrack());

      Double_t xyab[kDimension];
      
      xyab[0] = track->GetX();
      xyab[1] = track->GetY();
      xyab[2] = (track->GetA());
      xyab[3] = (track->GetB());
      
      
      Double_t Delta = 0 ;
      Double_t A = 0;
      Double_t B = 0;
      
      
      for (Int_t i = 0, n = fTermsDelta.size(); i != n; ++i) {
	Double_t elem = 1.;
	for (Int_t j = 0; j != kDimension; ++j) {
	  const Int_t power = (fTermsDelta[i] >> (j * kShift) & kMask);
	  elem *= TMath::Power(xyab[j],power);
	}
	Delta += elem * fCoefficientsDelta[i];
      }

      for (Int_t i = 0, n = fTermsA.size(); i != n; ++i) {
	Double_t elem = 1.;
	for (Int_t j = 0; j != kDimension; ++j) {
	  const Int_t power = (fTermsA[i] >> (j * kShift) & kMask);
	  elem *= TMath::Power(xyab[j],power);
	}
	A += elem * fCoefficientsA[i];
      }
      
      
      for (Int_t i = 0, n = fTermsB.size(); i != n; ++i) {
	Double_t elem = 1.;
	for (Int_t j = 0; j != kDimension; ++j) {
	  const Int_t power = (fTermsB[i] >> (j * kShift) & kMask);
	  elem *= TMath::Power(xyab[j],power);
	}
	B += elem * fCoefficientsB[i];
      }
      
      
      
      
      outData->SetDelta(Delta);
      outData->SetA(A);
      outData->SetB(B);
      outData->SetProcessed(kProcessed);
    }
  }
  
  return;
}
