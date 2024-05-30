/**
 * @file    TTimingTrefValidator.h
 * @brief  validate time or timestamp  in certain window
 *
 * @date   Created       : 2015-11-17 13:51:53 JST
 *         Last Modified : 2018-02-04 13:15:23 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *
 *    (C) 2015 Shinsuke OTA
 */

#ifndef TTIMINGTREFVALIDATORLR_H
#define TTIMINGTREFVALIDATORLR_H

#include "TProcessor.h"

namespace art {
   class  TTimingTrefValidatorLR;
}
class TClonesArray;

class art:: TTimingTrefValidatorLR : public TProcessor {
public:
    TTimingTrefValidatorLR();
   virtual ~ TTimingTrefValidatorLR();

    TTimingTrefValidatorLR(const  TTimingTrefValidatorLR& rhs);
    TTimingTrefValidatorLR& operator=(const  TTimingTrefValidatorLR& rhs);

protected:
   virtual void Init(TEventCollection *col);
   virtual void Process();
private:
  TString fInputName1; // name of input collection
  TString fInputName2; // name of input collection
  TString fInputName3; // name of input collection
  TString fOutputName1; // name of output collection
  TString fOutputName2; // name of output collection
  TClonesArray **fInput1; //! input
  TClonesArray **fInput2; //! input
  TClonesArray **fInput3; //! input
  TClonesArray  *fOutput1; //! output
  TClonesArray  *fOutput2; //! output
  
  //   Int_t fTimeVariable; // 0 time 1 timestamp
  FloatVec_t fValidTimeRange;
  Float_t fValidTimeMin;
  Float_t fValidTimeMax;

  FloatVec_t fValidTimeRangeL;
  Float_t fValidTimeMinL;
  Float_t fValidTimeMaxL;
  
  FloatVec_t fValidTimeRangeR;
  Float_t fValidTimeMinR;
  Float_t fValidTimeMaxR;
   
  
  ClassDef( TTimingTrefValidatorLR,1) // validate time in certain window
};

#endif // TTIMINGTREFVALIDATOR_H

