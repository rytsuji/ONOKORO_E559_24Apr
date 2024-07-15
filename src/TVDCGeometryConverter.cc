#include "TVDCGeometryConverter.h"
#include "TMWDCTrackingResult.h"
#include "TMWDCParameter.h"
#include "TMWDCPlaneInfo.h"
#include "TClonesArray.h"
#include "TMath.h"
#include "TVector3.h"


using art::TVDCGeometryConverter;
ClassImp(art::TVDCGeometryConverter)

art::TVDCGeometryConverter::TVDCGeometryConverter()
: fMWDCTrackOut(NULL)
{

  Register(fOffsetX("OffsetX","relative x position between VDC and coordinate",0));
  Register(fOffsetY("OffsetY","relative y position between VDC and coordinate",0));
  Register(fOffsetZ("OffsetZ","relative z position between VDC and coordinate",0));
  Register(fFPTiltedAngleY("FPTiltedAngleY","tilted angle of fp  along y axis in deg",0));
  Register(fVDCTiltedAngleX("VDCTiltedAngleX","tilted angle of whole system along x axis in deg",0));  
  Register(fVDCTiltedAngleY("VDCTiltedAngleY","tilted angle of whole system along y axis in deg",0));
  Register(fVDCTiltedAngleZ("VDCTiltedAngleZ","tilted angle of whole system along z axis in deg",0));    
  
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

	HitPos.RotateX(fVDCTiltedAngleX*TMath::DegToRad());
	Vec.RotateX(fVDCTiltedAngleX*TMath::DegToRad());
	
	HitPos.RotateY(fVDCTiltedAngleY*TMath::DegToRad());
	Vec.RotateY(fVDCTiltedAngleY*TMath::DegToRad());

	HitPos.RotateZ(fVDCTiltedAngleZ*TMath::DegToRad());
	Vec.RotateZ(fVDCTiltedAngleZ*TMath::DegToRad());
	
	double ConvX=HitPos.X()+fOffsetX - (HitPos.Z()+fOffsetZ)*Vec.X()/Vec.Z();
	double ConvY=HitPos.Y()+fOffsetY - (HitPos.Z()+fOffsetZ)*Vec.Y()/Vec.Z();
	double ConvZ=0;

	Vec.RotateY((fFPTiltedAngleY)*TMath::DegToRad());
	//trIn->Copy(*trOut);
	trOut->SetTrack(ConvX,ConvY,ConvZ,Vec.X()/Vec.Z(),Vec.Y()/Vec.Z());
	trOut->SetTrackingID(TMWDCTrackingResult::kGood);
      }
      
    }
  }
}
