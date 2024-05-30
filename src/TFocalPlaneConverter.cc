#include "TFocalPlaneConverter.h"

#include "constant.h"
#include <iostream>
#include <string>
#include <fstream>
//#include "TDataObject.h"

#include <TClonesArray.h>
#include <TClass.h>
#include <TSimpleData.h>
#include <yaml-cpp/yaml.h>


using art::TFocalPlaneConverter;


ClassImp(TFocalPlaneConverter)

TFocalPlaneConverter::TFocalPlaneConverter()
: fMWDCTrackOut(NULL)
{

  Register(fOffsetX("OffsetX","relative x position between VDC and coordinate",0));
  Register(fOffsetY("OffsetY","relative y position between VDC and coordinate",0));
  Register(fOffsetZ("OffsetZ","relative z position between VDC and coordinate",0));
  RegisterProcessorParameter("MatrixFile","path to the matrix file",
			      fMatrixFileName,TString("path/to/file"));


  RegisterInputCollection("InputCollection",
                           "input collection",
                           fNameInput, "MWDCTrackIn",
			  &fMWDCTrackIn, TClonesArray::Class_Name(),
			  art::TMWDCTrackingResult::Class_Name());
 RegisterOutputCollection("OutputCollection","output collection",
                           fNameOutput,"MWDCTrackOut",
                           &fMWDCTrackOut, TClonesArray::Class_Name(),
                           art::TMWDCTrackingResult::Class_Name());
}


TFocalPlaneConverter::~TFocalPlaneConverter()
{
  delete fMWDCTrackOut;
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


void TFocalPlaneConverter::Init(TEventCollection*){
  std::ifstream fin(fMatrixFileName.Data());


  if(!fin.is_open()) {
      SetStateError(TString::Format("Cannot open configuration file: %s",fMatrixFileName.Data()));
      return;
   }

   try {
     YAML::Node matrix;
     matrix = YAML::Load(fin);
     for(auto element : matrix) {
       std::string key = element.first.as<std::string>();
       Float_t value = element.second.as<Float_t>();       
       Int_t term = KeyToInt(key);
       
       
       if (term) {
	 fTerms.push_back(term);
	 fCoefficients.push_back(value);
       }
     }
   } catch (YAML::Exception& e) {
     SetStateError(TString::Format("Error Occurred while loading matrix file\n%s\n",
				   e.what()));
     return;
   }



   
}

void TFocalPlaneConverter::Process(){

  fMWDCTrackOut->Clear("C");
  Bool_t kProcessed = kFALSE;
  const Int_t nData = (*fMWDCTrackIn)->GetEntriesFast();

  
  
  
  if (nData < 1) {
    //if (fVerbose) std::cout << "Multiplicity is" << nData << ", cannot process" << std::endl;
    kProcessed = kFALSE;    
  }
  else {
    kProcessed = kTRUE;
    
    for (Int_t iData = 0; iData != nData; ++iData) {
      


      const TMWDCTrackingResult *const trIn = static_cast<TMWDCTrackingResult*>((*fMWDCTrackIn)->At(iData));
      TMWDCTrackingResult *trOut = (TMWDCTrackingResult*)fMWDCTrackOut->ConstructedAt(fMWDCTrackOut->GetEntriesFast());


      
      Double_t xyab[kDimension];
      
      xyab[0] = trIn->GetX();
      xyab[1] = trIn->GetY();
      xyab[2] = (trIn->GetA());
      xyab[3] = (trIn->GetB());
      
      
      Double_t x = xyab[0]+xyab[2]*fOffsetZ+fOffsetX;      
      Double_t y = xyab[1]+xyab[3]*fOffsetZ+fOffsetY;      
      Double_t a = xyab[2];
      Double_t b = xyab[3];
      for (Int_t i = 0, n = fTerms.size(); i != n; ++i) {
	Double_t elem = 1.0;
	for (Int_t j = 0; j != kDimension; ++j) {
	  const Int_t power = (fTerms[i] >> (j * kShift) & kMask);
	  elem *= TMath::Power(xyab[j],power);
	}
	x += elem * fCoefficients[i];
      }


      trOut->SetTrack(x,y,0.0,a,b);
      trOut->SetTrackingID(TMWDCTrackingResult::kGood);            
    }
  }
  
  return;
}
