#include "TVDCTrackingMergeProcessor.h"
#include "TMWDCTrackingResult.h"
#include "TMWDCParameter.h"
#include "TMWDCPlaneInfo.h"
#include "TClonesArray.h"
#include "TMath.h"
#include "TVector3.h"

//#include <numeric>

using art::TVDCTrackingMergeProcessor;
ClassImp(art::TVDCTrackingMergeProcessor)

art::TVDCTrackingMergeProcessor::TVDCTrackingMergeProcessor()
: fTrackOut(NULL)
{

  StringVec_t defInput;
   defInput.push_back("vdc_xu");
   defInput.push_back("vdc_xv");
   defInput.push_back("vdc_uv");
   RegisterInputCollection("InputCollection","input",
                           fInputColName,defInput);

  
   RegisterOutputCollection("OutputCollection","output collection",
			    fNameOutput,"MWDCTrackOut",
			    &fTrackOut, TClonesArray::Class_Name(),
			    art::TMWDCTrackingResult::Class_Name());
}
  
TVDCTrackingMergeProcessor::~TVDCTrackingMergeProcessor(){
}


void TVDCTrackingMergeProcessor::Init(TEventCollection *col){
  fTrackIn = new std::vector<TClonesArray**>;
  fNTrack = fInputColName.size();
  for (Int_t i = 0;i!=fNTrack;++i) {
    const TString &inputName = fInputColName[i];
    TClonesArray** const ref = reinterpret_cast<TClonesArray**>(col->GetObjectRef(inputName.Data()));
    fTrackIn->push_back(ref);
  }


}
void TVDCTrackingMergeProcessor::Process(){

  fTrackOut->Clear("C");

  for (int itrack = 0; itrack < fNTrack; ++itrack) {
    TClonesArray** aTrack = fTrackIn->at(itrack);
    const Int_t nData = (*aTrack)->GetEntriesFast();
    if(nData>0){
      for (Int_t iData = 0; iData != nData; ++iData) {
	const TMWDCTrackingResult *const trIn = static_cast<TMWDCTrackingResult*>((*aTrack)->At(iData));
	TMWDCTrackingResult *trOut = (TMWDCTrackingResult*)fTrackOut->ConstructedAt(fTrackOut->GetEntriesFast());
	trOut->SetTrack(trIn->GetX(),trIn->GetY(),trIn->GetZ(),trIn->GetA(),trIn->GetB());
	//trIn->Copy(*trOut);
	trOut->SetTrackingID(TMWDCTrackingResult::kGood);
      }      
      break;
    }
  }
  

  return;

}
