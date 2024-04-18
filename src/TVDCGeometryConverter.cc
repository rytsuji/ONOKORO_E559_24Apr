#include "TVDCGeometryConverter.h"
#include "TMWDCTrackingResult.h"
#include "TMWDCParameter.h"
#include "TMWDCPlaneInfo.h"
//"TVDCCluster.h"

//#include "TStopwatch.h"
#include "TClonesArray.h"
#include "TMath.h"
//#include "TMatrixD.h"
#include "TVector3.h"

//#include <numeric>

using art::TVDCGeometryConverter;
ClassImp(art::TVDCGeometryConverter)

art::TVDCGeometryConverter::TVDCGeometryConverter()
: fMWDCTrackOut(NULL)
{

  Register(fOffsetX("OffsetX","relative x position between VDC and coordinate",0));
  Register(fOffsetY("OffsetY","relative y position between VDC and coordinate",0));
  Register(fOffsetZ("OffsetZ","relative z position between VDC and coordinate",0));
  Register(fFPTiltedAngleY("FPTiltedAngleY","tilted angle of fp  along y axis in deg",0));
  Register(fVDCTiltedAngleY("VDCTiltedAngleY","tilted angle of whole system along y axis in deg",0));
  
  
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
  
TVDCGeometryConverter::~TVDCGeometryConverter(){
}

void TVDCGeometryConverter::Process(){

  fMWDCTrackOut->Clear("C");

  const Int_t nData = (*fMWDCTrackIn)->GetEntriesFast();

  if (nData < 1) {
    
  }else {
    for (Int_t iData = 0; iData != nData; ++iData) {
      
      const TMWDCTrackingResult *const trIn = static_cast<TMWDCTrackingResult*>((*fMWDCTrackIn)->At(iData));
      //const TTrack *const track= dynamic_cast<const TTrack*> (fMWDCTrackIn->GetTrack());
      TMWDCTrackingResult *trOut = (TMWDCTrackingResult*)fMWDCTrackOut->ConstructedAt(fMWDCTrackOut->GetEntriesFast());
      
      //trIn = trOut;
      
      if(trIn->GetTrackingID()==TMWDCTrackingResult::kGood){
	
	TVector3 HitPos(trIn->GetX(),trIn->GetY(),trIn->GetZ());
	TVector3 Vec(trIn->GetA(),trIn->GetB(),1.0);	
	/*
	double HitZ=(tan(fVDCTiltedAngleY*TMath::DegToRad())*(HitPos.X()+fOffsetX)+fOffsetZ)/(1-tan(fVDCTiltedAngleY*TMath::DegToRad())*Vec.X());
	
	double ConvX = (HitPos.X()+Vec.X()*HitZ+fOffsetX)*cos(-fVDCTiltedAngleY*TMath::DegToRad())-(HitZ-fOffsetZ)*sin(-fVDCTiltedAngleY*TMath::DegToRad());
	double ConvY = HitPos.Y()+Vec.Y()*HitZ+fOffsetY;
	double ConvZ = (HitPos.X()+Vec.X()*HitZ+fOffsetX)*sin(-fVDCTiltedAngleY*TMath::DegToRad())+(HitZ-fOffsetZ)*cos(-fVDCTiltedAngleY*TMath::DegToRad());
	Vec.RotateY((fFPTiltedAngleY+fVDCTiltedAngleY)*TMath::DegToRad());
	*/
	double ConvX=HitPos.X()+Vec.X()*fOffsetZ+fOffsetX;
	double ConvY=HitPos.Y()+Vec.Y()*fOffsetZ+fOffsetY;
	double ConvZ=0;
	Vec.RotateY((fFPTiltedAngleY)*TMath::DegToRad());
	trOut->SetTrack(ConvX,ConvY,ConvZ,Vec.X()/Vec.Z(),Vec.Y()/Vec.Z());
	trOut->SetTrackingID(TMWDCTrackingResult::kGood);
      }
      
    }
  }
}
