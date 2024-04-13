#include "TOpticsData.h"
#include "constant.h"
using art::TOpticsData;

ClassImp(TOpticsData)

TOpticsData::TOpticsData()
  : fDelta(kInvalidD), fA(kInvalidD), fB(kInvalidD)
{
}

TOpticsData::~TOpticsData()
{
}


void art::TOpticsData::Clear(Option_t *) {
  fDelta = fA = fB = kInvalidD;
}


TOpticsData& TOpticsData::operator=(const TOpticsData& rhs) {
   if (this != &rhs) {
     //((TOpticsData&)rhs).Copy(*this);
   }
   return *this;
}
