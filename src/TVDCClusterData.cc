/**
 * @file   TVDCCluster.cc
 * @brief
 *
 * @date   Created:       2013-08-14 10:34:09
 *         Last Modified: 2014-01-08 12:56:45
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro All rights reserved.
 */

#include "TVDCClusterData.h"
#include "constant.h"

#include <iostream>
#include <TClass.h>

using art::TVDCClusterData;

ClassImp(art::TVDCClusterData)

Int_t TVDCClusterData::fSortType  = TVDCClusterData::kID;
Int_t TVDCClusterData::fSortOrder = TVDCClusterData::kDESC;

// Default constructor
TVDCClusterData::TVDCClusterData() 
  : fTiming(kInvalidD), fCharge(kInvalidD),Clust_ID(kInvalidD),valid_cluster2(kInvalidD),valid_cluster(kInvalidD),fClust_Size(kInvalidD),fHitID(0),fHitDL(0),fHitTiming(0),fHitLR(0),fResidual(0){
   TDataObject::SetID(kInvalidI);
}

TVDCClusterData::~TVDCClusterData() {
}

// Copy constructor
TVDCClusterData::TVDCClusterData(const TVDCClusterData& rhs)
   : TDataObject(rhs), fTiming(rhs.fTiming), fCharge(rhs.fCharge) {
}
void TVDCClusterData::Print(Option_t*) const {
/*  std::cout << "OBJ: " << IsA()->GetName() << "\t"
	 << "TrackingID: " << GetID() << "\t"
	 << "nParameter: " << GetNParameter() << "\t"
	 << "SSR: " << GetSSR() << "\t"
	 << "TimeCost: " << GetTimeCost() << std::endl;
	 */
  printf("aaa\n");
}

void TVDCClusterData::Init() {


	 fHitID.resize(20);
	 fHitDL.resize(20);
	 fHitTiming.resize(20);
	 fHitLR.resize(20);
	 fResidual.resize(20);
  Clear();
}
void TVDCClusterData::Init2(int size) {


	 fHitID.resize(size);
	 fHitDL.resize(size);
	 fHitTiming.resize(size);
	 fHitLR.resize(size);
	 fResidual.resize(size-2);
  Clear();
}
// Assignment operator
/*TVDCClusterData& TVDCClusterData::operator=(const TVDCClusterData& rhs) {
   if (this != &rhs) {
      ((TVDCClusterData&)rhs).Copy(*this);
   }
   return *this;
}
*/
/*

void TVDCClusterData::Clear(Option_t *opt) {
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   this->SetTiming(kInvalidD);
   this->SetCharge(kInvalidD);
}
*/
