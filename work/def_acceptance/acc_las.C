void acc_las(double theta0,TString fname){

  TFile *fout = new TFile(fname,"RECREATE");
  TTree *tree = new TTree("tree","data");

  int N=1000000;

  double ThetaRad=theta0*TMath::DegToRad();
  double PhiRad=180.0*TMath::DegToRad();
  
  TRandom r;
  double theta;
  double phi;
  double a;
  double b;

  tree->Branch("a",&a,"a/D");
  tree->Branch("b",&b,"b/D");
  tree->Branch("theta",&theta,"theta/D");
  tree->Branch("phi",&phi,"phi/D");
  
  for(int i=0;i<N;i++){
    a=r.Uniform(-60./1000.0,60./1000.);
    b=r.Uniform(-60./1000.,50./1000.);

    
      
    double rx=a*cos(ThetaRad)*cos(PhiRad)-b*sin(PhiRad)+sin(ThetaRad)*cos(PhiRad);
    double ry=a*cos(ThetaRad)*sin(PhiRad)+b*cos(PhiRad)+sin(ThetaRad)*sin(PhiRad);
    double rz=-a*sin(ThetaRad)+cos(ThetaRad);
    
    TVector3 r(rx,ry,rz);
    
    theta = TMath::RadToDeg()*r.Theta();
    phi = fmod(TMath::RadToDeg()*r.Phi()+360.0,360.0);
    
    tree->Fill();
      
      
      
  }

  fout->Write();
  fout->Close();
  TFile *_file0 = TFile::Open(fname);


}
