#ifndef TPARTICLEDATA_H
#define TPARTICLEDATA_H

#include "TDataObject.h"
#include "TMath.h"

namespace art {
   class TParticleData;
}

class art::TParticleData : public TDataObject {
public:
  TParticleData();
  virtual ~TParticleData();
  
  TParticleData(const TParticleData& rhs);
  virtual void Clear(const Option_t* = "");
  TParticleData& operator=(const TParticleData& rhs);

  void SetMass(Double_t val){ fMass = val;}
  Double_t GetMass(){ return fMass; }

  void SetTKE(Double_t val){ fTKE = val;}
  Double_t GetTKE(){ return fTKE; }

  void SetTheta(Double_t val){ fTheta = val;}
  Double_t GetTheta(){ return fTheta; }

  void SetPhi(Double_t val){ fPhi = val;}
  Double_t GetPhi(){ return fPhi; }

  Double_t GetPx(){ return sqrt(fTKE*(fTKE+2.0*fMass))*sin(fTheta*TMath::DegToRad())*cos(fPhi*TMath::DegToRad()); }
  Double_t GetPy(){ return sqrt(fTKE*(fTKE+2.0*fMass))*sin(fTheta*TMath::DegToRad())*sin(fPhi*TMath::DegToRad()); }
  Double_t GetPz(){ return sqrt(fTKE*(fTKE+2.0*fMass))*cos(fTheta*TMath::DegToRad());}
  Double_t GetP(){ return sqrt(fTKE*(fTKE+2.0*fMass));}

  Double_t GetEnergy(){ return fTKE*fMass;}

  void SetTOF(Double_t tof, Double_t tof_central){
    fTOF = tof;
    fTOFcentral = tof_central;
  }
  Double_t GetTOF(){ return fTOF; }
  Double_t GetTOFDiff(){ return fTOF-fTOFcentral; }

  
  Bool_t IsProcessed() const { return kProcessed; }
  void SetProcessed(Bool_t val) { kProcessed = val; }
  
 protected:
  Double_t fMass;
  Double_t fTheta;
  Double_t fPhi;
  Double_t fTKE;
  Double_t fTOF;
  Double_t fTOFcentral;
  Bool_t kProcessed;

 private:
  
  ClassDef(TParticleData,1) 
};

#endif //TOPTICSDATA_H       
