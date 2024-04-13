#ifndef TVDTRACKINGMARGEPROCESSOR_H
#define TVDTRACKINGMARGEPROCESSOR_H
#include "TMWDCTrackingProcessor.h"

namespace art {
  class TVDCTrackingMergeProcessor;
}

class TClonesArray;

class art::TVDCTrackingMergeProcessor : public TProcessor {
public:
  TVDCTrackingMergeProcessor();
  virtual ~TVDCTrackingMergeProcessor();
  virtual void Init(TEventCollection *col);
  virtual void Process();
  
protected:
  Int_t fNTrack;

  StringVec_t fInputColName;
  std::vector<TClonesArray**> *fTrackIn;
  
  TString fNameOutput;
  TClonesArray *fTrackOut;

  ClassDef(TVDCTrackingMergeProcessor,0) // vdc tracking processor
};

#endif
