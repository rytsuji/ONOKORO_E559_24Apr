/**
 * @file   TTimingChargeMultiHitMappingProcessor.h
 * @brief
 *
 * @date   Created:       2022.11.24
 *         Last Modified: 2022.11.24 (Y.HIJIKATA)
 * @author Yuto HIJIKATA
 *
 *    Original : TTimingChargeMappingProcessor.h
 */

#ifndef TTIMINGCHARGEMULTIHITMAPPINGPROCESSOR_H
#define TTIMINGCHARGEMULTIHITMAPPINGPROCESSOR_H

#include <TProcessor.h>

namespace art{
   class TTimingChargeMultiHitMappingProcessor;
   class TCategorizedData;
}

class TClonesArray;

class art::TTimingChargeMultiHitMappingProcessor : public TProcessor {

public:
   // Default constructor
   TTimingChargeMultiHitMappingProcessor();
   virtual ~TTimingChargeMultiHitMappingProcessor();

   virtual void Init(TEventCollection*);
   virtual void Process();

protected:
   TString            fInputColName;
   TString            fOutputColName;
   TCategorizedData **fCategorizedData; //!
   TClonesArray      *fPlastic; //!

   Int_t  fCatID;        // default: 21 (spla in anapaw)
   Int_t  fChargeType;   // 0: V1190 width (default), 1: QDC (V792 etc)
   Int_t  fChargeTypeID; // used only when fChargeType is QDC
   Int_t  fTimingTypeID; // Typeid for timing (& width when fChargeType is V1190width)
   Bool_t fTrailingComesFirst; // F: TL->TT (default), T: TT->TL (for QTC etc.)

   Bool_t fIsSparse;

private:
   // Copy constructor (prohibited)
   TTimingChargeMultiHitMappingProcessor(const TTimingChargeMultiHitMappingProcessor&);
   // Assignment operator (prohibited)
   TTimingChargeMultiHitMappingProcessor& operator=(const TTimingChargeMultiHitMappingProcessor&);

   void MapEdgedTime(const TObjArray*);
   void MapPairedTimeCharge(const TObjArray*);
   void MapTimeCharge(const TObjArray*, const TObjArray*);

   enum EChargeTypeID { kWIDTH, kQDC, kHINP,};

   ClassDef(TTimingChargeMultiHitMappingProcessor,0) // processor for mapping timine and charge data for multi hit data
};

#endif // TTIMINGCHARGEMULTIHITMAPPINGPROCESSOR_H
