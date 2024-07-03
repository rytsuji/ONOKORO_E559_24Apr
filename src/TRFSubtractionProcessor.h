/**
 * @file   TRFSubtractionProcessor.h
 * @brief
 *
 * @date   Created:       2013-11-07 15:17:35
 *         Last Modified: 2014-06-18 11:12:05 JST (kawase)
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro All rights reserved
 */

#ifndef TRFSUBTRACTIONPROCESSOR_H
#define TRFSUBTRACTIONPROCESSOR_H

#include <TProcessor.h>
#include <vector>

namespace art {
   class TRFSubtractionProcessor;
}

class TObjArray;
class TClonesArray;

class art::TRFSubtractionProcessor : public TProcessor {
public:
   // Default constructor
   TRFSubtractionProcessor();
   virtual ~TRFSubtractionProcessor();

   virtual void Init(TEventCollection *col);
   virtual void Process();

   virtual void ProcessByTimeDiff();

protected:
   TString        fInputColName;
   TString        fOutputColName;
   TClonesArray **fInData;             //!
   TClonesArray  *fOutData; //!
   TClonesArray **fStartTimingData;    //!
   TString        fStartTimingColName;
   Int_t          fStartTimingDetID;
   Int_t         fUseMultipleStartTiming;
   Int_t         fMaxDetID;


   static const Int_t HITID_ORIGIN = 1;
   std::vector<Int_t> *fHitIDArray;    //!
   TObjArray          *fStartTiming; //!

   DoubleVec_t fValidTimeRange;
   Double_t fValidTimeMin;
   Double_t fValidTimeMax;

  Parameter<Double_t> fOffset;
  Parameter<Double_t> fPeriod;
  
   Int_t fUseStart; // use start timing as timestamp if 1, or use end if 0
   

private:
   // Copy constructor (prohibited)
   TRFSubtractionProcessor(const TRFSubtractionProcessor&);
   // Assignment operator (prohibited)
   TRFSubtractionProcessor& operator=(const TRFSubtractionProcessor&);

   ClassDef(TRFSubtractionProcessor,0) // processor for timing subtraction
};

#endif // TTIMINGSUBTRACTIONPROCESSOR_H
