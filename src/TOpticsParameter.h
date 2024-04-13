/**
 * @file   TMWDCParameter.h
 * @brief  mwdc parameter object
 *
 * @date   Created       : 2014-03-13 09:40:42 JST
 *         Last Modified : 2014-07-10 16:28:35 JST (kawase)
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 KAWASE Shoichiro
 */

#ifndef INCLUDE_GUARD_UUID_E8F391B6_AD3C_4E93_9B7E_9235CFD58F2A
#define INCLUDE_GUARD_UUID_E8F391B6_AD3C_4E93_9B7E_9235CFD58F2A

#include "TParameterObject.h"

namespace art {
   class TOpticsParameter;
   class TOpticsInfo;
}

class art::TOpticsParameter : public TParameterObject {
public:
   TOpticsParameter();
   virtual ~TOpticsParameter();

   TOpticsParameter(const TOpticsParameter& rhs);
   TOpticsParameter& operator=(const TOpticsParameter& rhs);


  void SetMatrix(int i_x,int i_a, int i_y, int i_y, double val) {Matrix[i_x][i_a][i_y][i_b] = val;}
  Double_t GetMatrix(int i_x,int i_a, int i_y, int i_y) const  { return Matrix[i_x][i_a][i_y][i_b]}


  void SetConfigurationFile(const TString& str) {fConfigurationFile = str;}
  TString GetConfigurationFile() const {return fConfigurationFile;}

  TOpticsInfo *GetPlane(const TString& name, Bool_t isLocal = kFALSE);
  const TOpticsInfo *GetPlane(const TString& name, Bool_t isLocal = kFALSE) const;

   const TList *GetPlaneList(Bool_t isLocal = kFALSE) const;

   void Copy(TObject &obj) const;
   void Print(Option_t*) const;

   Bool_t LoadYAMLNode(const YAML::Node&);
   void PrintDescriptionYAML() const;
   void OutputDescriptionYAML(std::ostream&) const;

protected:
   static const Int_t kPosDim = 3;
   Double_t fPosition[kPosDim]; //[kPosDim] Position in global coordinate
   Double_t fAngle;             // rotation angle around z axis (deg)
   Int_t    fIsTurned;          // 180 deg flipped by y axis if non zero
   TString  fConfigurationFile; //! filename of plane configuration

   TList   *fPlanes;            // list of TMWDCPlaneInfo in local coordinate
   TList   *fPlanesGlobal;      // list of TMWDCPlaneInfo in global coordinate

   void GenerateGlobal();

private:

   ClassDef(TMWDCParameter,1) // mwdc parameter object
};

#endif // INCLUDE_GUARD_UUID_E8F391B6_AD3C_4E93_9B7E_9235CFD58F2A
