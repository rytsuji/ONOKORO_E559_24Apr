/**
 * @file   TTimingTrefValidatorLR.cc
 * @brief  validate time or timestamp in certain window
 *
 * @date   Created       : 2015-11-17 13:53:41 JST
 *         Last Modified : Dec 02, 2015 15:26:30 JST
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2015 Shinsuke OTA
 */

#include "TTimingTrefValidatorLR.h"
#include <TClonesArray.h>
#include <ITiming.h>
#include <TDataObject.h>

using art::TTimingTrefValidatorLR;

ClassImp(TTimingTrefValidatorLR)

TTimingTrefValidatorLR::TTimingTrefValidatorLR()
{
   RegisterInputCollection("InputCollection1","Input collection1",
                           fInputName1,TString("input1"),&fInput1,
                           TClonesArray::Class_Name(),ITiming::Class_Name());
   RegisterInputCollection("InputCollection2","Input collection2",
			   fInputName2,TString("input2"),&fInput2,
			   TClonesArray::Class_Name(),ITiming::Class_Name());
   RegisterInputCollection("InputCollection3","Input collection3",
			   fInputName3,TString("input3"),&fInput3,
			   TClonesArray::Class_Name(),ITiming::Class_Name());   
   RegisterOutputCollection("OutputCollection1","Output collection1",fOutputName1,TString("validated"));
   RegisterOutputCollection("OutputCollection2","Output collection2",fOutputName2,TString("validated"));

   const FloatVec_t range(3,0.);
   //const FloatVec_t range[3]={0.0,-1000,1000};
   
   RegisterProcessorParameter("ValidTimeRange","[min,max,offset] => Tmin = offset + min etc. ignored if min == max",
                              fValidTimeRange,range);

   RegisterProcessorParameter("ValidTimeRangeL","[min,max,offset] => Tmin = offset + min etc. ignored if min == max",
                              fValidTimeRangeL,range);
   RegisterProcessorParameter("ValidTimeRangeR","[min,max,offset] => Tmin = offset + min etc. ignored if min == max",
                              fValidTimeRangeR,range);

}

TTimingTrefValidatorLR::~TTimingTrefValidatorLR()
{
}

TTimingTrefValidatorLR::TTimingTrefValidatorLR(const TTimingTrefValidatorLR& rhs)
{
}

TTimingTrefValidatorLR& TTimingTrefValidatorLR::operator=(const TTimingTrefValidatorLR& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}


void TTimingTrefValidatorLR::Init(TEventCollection *col)
{

  //LR
   if (fValidTimeRange[0] > fValidTimeRange[1]) {
      SetStateError("Time range : min > max");
      return;
   }

   
   fValidTimeMin = fValidTimeRange[2] + fValidTimeRange[0];
   fValidTimeMax = fValidTimeRange[2] + fValidTimeRange[1];

   //L
   if (fValidTimeRangeL[0] > fValidTimeRangeL[1]) {
      SetStateError("Time range L : min > max");
      return;
   }
   fValidTimeMinL = fValidTimeRangeL[2] + fValidTimeRangeL[0];
   fValidTimeMaxL = fValidTimeRangeL[2] + fValidTimeRangeL[1];

   //R
   if (fValidTimeRangeR[0] > fValidTimeRangeR[1]) {
     SetStateError("Time range R : min > max");
     return;
   }
   fValidTimeMinR = fValidTimeRangeR[2] + fValidTimeRangeR[0];
   fValidTimeMaxR = fValidTimeRangeR[2] + fValidTimeRangeR[1];
   
   const TClass* inClass = (*fInput1)->GetClass();


   if (!inClass->InheritsFrom(TDataObject::Class())) {
      SetStateError(Form("Input class '%s' does not inherits from TDataObject",inClass->GetName()));
      return;
   }
   fOutput1 = new TClonesArray(inClass);
   col->Add(fOutputName1,fOutput1,fOutputIsTransparent);
   fOutput2 = new TClonesArray(inClass);
   col->Add(fOutputName2,fOutput2,fOutputIsTransparent);
}

void TTimingTrefValidatorLR::Process()
{
   fOutput1->Clear("C");
   fOutput2->Clear("C");

   

   if((*fInput3)->GetEntriesFast()>0){
     const ITiming *const trefData = dynamic_cast<const ITiming*>((*fInput3)->At(0));
     
     Double_t tref = trefData->GetTiming();
   
     Int_t nHits1 = (*fInput1)->GetEntriesFast();
     Int_t nHits2 = (*fInput2)->GetEntriesFast();
     for (Int_t iHit1 = 0; iHit1 != nHits1; ++iHit1) {
       for (Int_t iHit2 = 0; iHit2 != nHits2; ++iHit2) {
	 const ITiming *const timingData1 = dynamic_cast<const ITiming*>((*fInput1)->At(iHit1));
	 const TDataObject *const data1 = static_cast<TDataObject*>((*fInput1)->At(iHit1));

	 const ITiming *const timingData2 = dynamic_cast<const ITiming*>((*fInput2)->At(iHit2));
	 const TDataObject *const data2 = static_cast<TDataObject*>((*fInput2)->At(iHit2));

	 if (!timingData1 && !timingData2) continue;
	 Double_t timing1 = timingData1->GetTiming();
	 Double_t timing2 = timingData2->GetTiming();
	 if ( (0.5*(timing1+timing2)-tref < fValidTimeMin || fValidTimeMax < 0.5*(timing1+timing2)-tref ) || ( timing1-tref < fValidTimeMinL || fValidTimeMaxL < timing1-tref ) || ( timing2-tref < fValidTimeMinR || fValidTimeMaxR < timing2-tref ) ) {
	   continue;
	 }	 
	 TDataObject *const outData1 = fOutput1->ConstructedAt(fOutput1->GetEntriesFast());
	 TDataObject *const outData2 = fOutput2->ConstructedAt(fOutput2->GetEntriesFast());
	 data1->Copy(*outData1);
	 data2->Copy(*outData2);	 
       }
     }

   }
}
   
