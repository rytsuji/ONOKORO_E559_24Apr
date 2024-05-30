/**
 * @file   TTimingTrefValidator.cc
 * @brief  validate time or timestamp in certain window
 *
 * @date   Created       : 2015-11-17 13:53:41 JST
 *         Last Modified : Dec 02, 2015 15:26:30 JST
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2015 Shinsuke OTA
 */

#include "TTimingTrefValidator.h"
#include <TClonesArray.h>
#include <ITiming.h>
#include <TDataObject.h>

using art::TTimingTrefValidator;

ClassImp(TTimingTrefValidator)

TTimingTrefValidator::TTimingTrefValidator()
{
   RegisterInputCollection("InputCollection1","Input collection1",
                           fInputName1,TString("input1"),&fInput1,
                           TClonesArray::Class_Name(),ITiming::Class_Name());
   RegisterInputCollection("InputCollection2","Input collection2",
			   fInputName2,TString("input2"),&fInput2,
			   TClonesArray::Class_Name(),ITiming::Class_Name());
   RegisterOutputCollection("OutputCollection","Output collection",fOutputName,TString("validated"));

   const FloatVec_t range(3,0.);
   RegisterProcessorParameter("ValidTimeRange","[min,max,offset] => Tmin = offset + min etc. ignored if min == max",
                              fValidTimeRange,range);
   

}

TTimingTrefValidator::~TTimingTrefValidator()
{
}

TTimingTrefValidator::TTimingTrefValidator(const TTimingTrefValidator& rhs)
{
}

TTimingTrefValidator& TTimingTrefValidator::operator=(const TTimingTrefValidator& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}


void TTimingTrefValidator::Init(TEventCollection *col)
{
   if (fValidTimeRange[0] > fValidTimeRange[1]) {
      SetStateError("Time range : min > max");
      return;
   }
   fValidTimeMin = fValidTimeRange[2] + fValidTimeRange[0];
   fValidTimeMax = fValidTimeRange[2] + fValidTimeRange[1];
   
   const TClass* inClass = (*fInput1)->GetClass();

   if (!inClass->InheritsFrom(TDataObject::Class())) {
      SetStateError(Form("Input class '%s' does not inherits from TDataObject",inClass->GetName()));
      return;
   }
   fOutput = new TClonesArray(inClass);
   col->Add(fOutputName,fOutput,fOutputIsTransparent);
}

void TTimingTrefValidator::Process()
{
   fOutput->Clear("C");

   

   if((*fInput2)->GetEntriesFast()>0){
     const ITiming *const trefData = dynamic_cast<const ITiming*>((*fInput2)->At(0));

     //const ITiming *const trefData = dynamic_cast<const ITiming*>((*fInput2));
     Double_t tref = trefData->GetTiming();
   
     Int_t nHits = (*fInput1)->GetEntriesFast();
     for (Int_t iHit = 0; iHit != nHits; ++iHit) {
       const ITiming *const timingData = dynamic_cast<const ITiming*>((*fInput1)->At(iHit));
       const TDataObject *const data = static_cast<TDataObject*>((*fInput1)->At(iHit));
       if (!timingData) continue;
       Double_t timing = timingData->GetTiming();
       if (timing-tref > fValidTimeMin && fValidTimeMax > timing-tref) {
         //continue;
	 TObject *const outData = fOutput->ConstructedAt(fOutput->GetEntriesFast());
	 data->Copy(*outData);
       }

     }
   }
}
   
