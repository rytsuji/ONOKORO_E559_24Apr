#include "TMath.h"
#include "TParticleData.h"
#include "constant.h"
using art::TParticleData;

ClassImp(TParticleData)

TParticleData::TParticleData()
: fMass(kInvalidD), fTheta(kInvalidD), fPhi(kInvalidD), fTKE(kInvalidD), fTOF(kInvalidD), fTOFcentral(kInvalidD)
{
}

TParticleData::~TParticleData()
{
}


void art::TParticleData::Clear(Option_t *) {
  fMass = fTheta = fPhi = fTKE = fTOF = fTOFcentral = kInvalidD;
}


TParticleData& TParticleData::operator=(const TParticleData& rhs) {
   if (this != &rhs) {
     //((TParticleData&)rhs).Copy(*this);
   }
   return *this;
}
