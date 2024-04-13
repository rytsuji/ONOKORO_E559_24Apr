#ifndef TVDCPLANECONVERTER_H
#define TVDCPLANECONVERTER_H

#include "TMWDCTrackingProcessor.h"

namespace art {
  //class TVDCFPTrackingProcessor;
  //class TMWDCTrackingResult;
  class TVDCGeometryConverter;
}

class TClonesArray;

class art::TVDCGeometryConverter : public TProcessor {
public:
  TVDCGeometryConverter();
  virtual ~TVDCGeometryConverter();
  //virtual void Init();
  virtual void Process();
  
protected:
  TString fNameInput;
  TString fNameOutput;
  TClonesArray **fMWDCTrackIn;
  TClonesArray *fMWDCTrackOut;

  Parameter<Double_t> fOffsetX; // unit of mm
  Parameter<Double_t> fOffsetY; // unit of mm
  Parameter<Double_t> fOffsetZ; // unit of mm
  Parameter<Double_t> fFPTiltedAngleY; // unit of deg
  Parameter<Double_t> fVDCTiltedAngleY; // unit of deg
  //Parameter<Double_t> fVDCTiltedAngleX; // unit of deg
  //Parameter<Double_t> fVDCTiltedAngleZ; // unit of deg
  ClassDef(TVDCGeometryConverter,0) // vdc tracking processor
};

#endif
