/**
 * @file   TVDCClusterizationProcessor.h
 * @brief  divide MWDC TimingChargeData into collection for each plane
 *
 * @date   Created:       2013-10-18 12:51:41
 *         Last Modified: 2014-06-28 15:51:45 JST (kawase)
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro All rights reserved
 */

#ifndef TVDCCLUSTERIZATIONSIZESELECTABLEPROCESSOR_MOD_H
#define TVDCCLUSTERIZATIONSIZESELECTABLEPROCESSOR_MOD_H

#include "TProcessor.h"
#include <vector>

namespace art {
   class TVDCClusterizationSizeSelectableProcessor;
   class TConverterBase;
   class TMWDCHitData;
}

class art::TVDCClusterizationSizeSelectableProcessor : public TProcessor {
public:
   // Default constructor
  TVDCClusterizationSizeSelectableProcessor();
  virtual ~TVDCClusterizationSizeSelectableProcessor();

  virtual void Init(TEventCollection *col);
  virtual void Process();
  virtual void ProcessCluster(std::vector<std::vector<TMWDCHitData*>> wires);
protected:
  TString		 fInputColName;     // name of input collection
  TString	         fMWDCName;         // name of mwdc
  TString	         fOutputName;         // name of mwdc
  StringVec_t	         fConverterList;    // name list of time-to-length converter
  StringVec_t	         fOutputColName;    // name of output collection
  TClonesArray	       **fMWDCIn;           //! input collection (not owned)
  TClonesArray	       **input;           //! input collection (not owned)
  TClonesArray	       *fClusterOut;         //! output collection array (owned)
  TClonesArray** ref;
  Int_t                 fNPlane;           // number of plane
  std::vector<Double_t> fCellSize;         // cell size for each plane
  std::vector<Int_t>	 fNWireID;          // wire number for each plane
  Int_t	        *fNData;	    //[fNPlane] data number for each planeID
  std::vector<TConverterBase*> *fConverterArray; //! time2length converter for each plane
  Int_t fMAXDL;
  
  Parameter<Double_t> fSearchTimeWidth; //! search time window width

  Int_t fClustSize;
  
  static const Int_t DETID_ORIGIN = 0;
  static const Int_t WIREID_ORIGIN = 1;
  
  std::vector<Int_t> fPlaneID;
  std::vector<Int_t> fWireID;
  Int_t fMaxDetID;
  
  Int_t fSortType; // sort type for output
  Int_t fPlaneType;
  Int_t fSortTypeInput; // sort type for output
  enum ESortType { kID = 0, kTiming = 1, kCharge = 2, kDriftLength = 3};
  Int_t fSortOrder; // sort order for output
  Int_t fSortOrderInput; // sort order for output
  Int_t fV1190; // sort order for output
  enum ESortOrder { kASC = 0, kDESC = 1,};
  int ievt;
  
private:
  //   Bool_t LoadParameter(TEventCollection*);
  //   void InitSortParameter();
  
  // Copy constructor (prohibited)
  //   TVDCClusterizationSizeSelectableProcessor_original(const TVDCClusterizationSizeSelectableProcessor_original& rhs);
  // Assignment operator (prohibited)
  //TVDCClusterizationSizeSelectableProcessor_original& operator=(const TVDCClusterizationSizeSelectableProcessor_original& rhs);
  
  ClassDef(TVDCClusterizationSizeSelectableProcessor,0) // processor for MWDC plane division
};

#endif // TMWDCPLANEPROCESSOR_H
