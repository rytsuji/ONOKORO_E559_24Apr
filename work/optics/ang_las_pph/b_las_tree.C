TFile *fin = TFile::Open("output/las/run5451127.root");
TFile* fout = new TFile("output/las/run5451127.fit.root","recreate");
TTree* rtree = ((TTree*)fin->Get("tree"))->CloneTree();

Double_t db_tgt=25.0/606.5;  
const int nPrm=28;

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);

int b_las_tree(){


  
  //std::cout <<  "****DEBUG****" << std::endl;
  TMinuit *min = new TMinuit(nPrm);// set number of parameters
  min->SetPrintLevel(1);
  int ierflg = 0;
  
  //Intialize of parameters
  double vstart[nPrm];
  for(int i=0;i<nPrm;i++){
    vstart[i] = 0.0;
  }
  
  //step width
  double step[nPrm];
  for(int i=0;i<nPrm;i++){
      step[i]=1.0e-15;
  }
  //set limit of prm
  for(int i=0;i<nPrm;i++){
    min->mnparm(i, Form("p%d",i), vstart[i], step[i], 0, 0, ierflg);
  }
  
  min->SetFCN(chi2);

  int migrad_stats = min->Migrad();
  migrad_stats = min->Migrad(); 
  
  TString oname="work/ang_las_pph/result/las_b_tree_1000.yaml"; 
  ofstream ofile((std::string) oname);
  
  double par[nPrm]; //x0,x1,...,x4,a,xa,xxa,aa,xaa,xxaaa,...,xxaaaaa
  double par_err[nPrm];

  cout<<"**************************************"<<endl;
  for(int i=0;i<nPrm;i++){
    min->GetParameter(i,par[i],par_err[i]);
    cout<<"p" << i << ": "<< par[i] <<" +/- "<< par_err[i] <<endl;
  }

  ofile  << "offset: " << par[0] << std::endl;
  ofile  << "y: " << par[1] << std::endl;
  ofile  << "b: " << par[2] << std::endl;
  ofile  << "yx: " << par[3] << std::endl;
  ofile  << "ya: " << par[4] << std::endl;
  ofile  << "yxx: " << par[5] << std::endl;
  ofile  << "yxa: " << par[6] << std::endl;
  ofile  << "yaa: " << par[7] << std::endl;
  ofile  << "yxxx: " << par[8] << std::endl;
  ofile  << "yxxa: " << par[9] << std::endl;
  ofile  << "yxaa: " << par[10] << std::endl;
  ofile  << "yaaa: " << par[11] << std::endl;  
  ofile  << "bx: " << par[12] << std::endl;
  ofile  << "ba: " << par[13] << std::endl;
  ofile  << "yyy: " << par[14] << std::endl;
  ofile  << "yyyx: " << par[15] << std::endl;
  ofile  << "yyya: " << par[16] << std::endl;
  ofile  << "yyyxx: " << par[17] << std::endl;
  ofile  << "yyyxa: " << par[18] << std::endl;
  ofile  << "yyyaa: " << par[19] << std::endl;
  ofile  << "bxx: " << par[20] << std::endl;
  ofile  << "bxa: " << par[21] << std::endl;
  ofile  << "baa: " << par[22] << std::endl;
  ofile  << "x: " << par[23] << std::endl;
  ofile  << "xx: " << par[24] << std::endl;
  ofile  << "a: " << par[25] << std::endl;
  ofile  << "aa: " << par[26] << std::endl;
  ofile  << "yy: " << par[27] << std::endl;              


  
  
  ofile.close();

  TTree *ftree = new TTree("ftree","ftree");

  double x;
  double a;
  double y;
  double b;
  double bc;
  double b_tgt;  

  ftree->Branch("x",&x);
  ftree->Branch("y",&y);  
  ftree->Branch("a",&a);
  ftree->Branch("b",&b);  
  //ftree->Branch("a_tgt",&a_tgt);
  ftree->Branch("b_tgt",&b_tgt);
  ftree->Branch("bc",&bc);


  
  TClonesArray *arr = NULL;
  art::TMWDCTrackingResult *lfp;
  rtree->SetBranchAddress("lfp",&arr);
  
  for(int i=0; i<rtree->GetEntries(); i++){
      
    rtree->GetEntry(i);
    lfp = static_cast<art::TMWDCTrackingResult*>(arr->At(0));

    x= lfp->GetX();
    y= lfp->GetY();
    a= lfp->GetA();
    b= lfp->GetB();

    double yc= lfp->GetY(-448);
    
    Bool_t IsValidData=0;

    if(y>-100 && y<(1.121260e-01*x-8.433738e+01)){
      b_tgt=db_tgt*2.0;
      IsValidData=1;
    }else if(y>(7.604994e-02*x-6.296592e+01) && y < (4.696572e-02*x-1.931826e+01)){
      b_tgt=db_tgt*1.0;
      IsValidData=1;
    }else if(y>(2.015116e-02*x-5.932205e+00) && y < (-2.205882e-03*x+1.779585e+01)){
      b_tgt=db_tgt*0.0;
      IsValidData=1;
    }else if(y>(-4.303864e-02*x+3.495086e+01) && y < (-6.273770e-02*x+7.809830e+01)){
      b_tgt=db_tgt*(-1.0);
      IsValidData=1;      
    }else if(y>(-7.681104e-02*x+9.114883e+01) && y < 105){
      b_tgt=db_tgt*(-2.0);
      IsValidData=1;
    }

    double val=0;
    
    val += par[0];
    val += par[1]*y;
    val += par[2]*b;
    val += par[3]*y*x;
    val += par[4]*y*a;
    val += par[5]*y*x*x;
    val += par[6]*y*a*x;
    val += par[7]*y*a*a;
      
    val += par[8]*y*x*x*x;
    val += par[9]*y*x*x*a;
    val += par[10]*y*x*a*a;
    val += par[11]*y*a*a*a;

    
    val += par[12]*b*x;                 
    val += par[13]*b*a;

    val += par[14]*y*y*y;
    val += par[15]*y*y*y*x;
    val += par[16]*y*y*y*a;

    val += par[17]*pow(y,3.0)*x*x;
    val += par[18]*pow(y,3.0)*x*a;
    val += par[19]*pow(y,3.0)*a*a;
      
    val += par[20]*b*x*x;
    val += par[21]*b*a*x;
    val += par[22]*b*a*a;

    val += par[23]*x;
    val += par[24]*x*x;
    val += par[25]*a;
    val += par[26]*a*a;

    //val += par[27]*pow(y,2.0);


   
    if(IsValidData==1) bc = val;

    ftree->Fill();  
  }
  
  ftree->Write();
  delete min;    
  return 0;
}  



void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag){
  
  TClonesArray *arr = NULL;
  art::TMWDCTrackingResult *lfp;
  rtree->SetBranchAddress("lfp",&arr);
  
  double val = 0;
  double chisq = 0;  

  //for(int i=0; i<rtree->GetEntries(); i++){
  for(int i=0; i<1000; i++){

    
    rtree->GetEntry(i);

    lfp = static_cast<art::TMWDCTrackingResult*>(arr->At(0));

    double x= lfp->GetX();
    double y= lfp->GetY();
    double a= lfp->GetA();
    double b= lfp->GetB();

    double yc= lfp->GetY(-448);
    double b_tgt;
    Bool_t IsValidData=0;
    if(x<400 && x>-600){
    if(y>-100 && y<(1.121260e-01*x-8.433738e+01)){
      b_tgt=db_tgt*2.0;
      IsValidData=1;
    }else if(y>(7.604994e-02*x-6.296592e+01) && y < (4.696572e-02*x-1.931826e+01)){
      b_tgt=db_tgt*1.0;
      IsValidData=1;
    }else if(y>(2.015116e-02*x-5.932205e+00) && y < (-2.205882e-03*x+1.779585e+01)){
      b_tgt=db_tgt*0.0;
      IsValidData=1;
    }else if(y>(-4.303864e-02*x+3.495086e+01) && y < (-6.273770e-02*x+7.809830e+01)){
      b_tgt=db_tgt*(-1.0);
      IsValidData=1;      
    }else if(y>(-7.681104e-02*x+9.114883e+01) && y < 105){
      b_tgt=db_tgt*(-2.0);
      IsValidData=1;
    }
    
    val = -b_tgt;
    
    val += par[0];
    val += par[1]*y;
    val += par[2]*b;
    val += par[3]*y*x;
    val += par[4]*y*a;
    val += par[5]*y*x*x;
    val += par[6]*y*a*x;
    val += par[7]*y*a*a;
      
    val += par[8]*y*x*x*x;
    val += par[9]*y*x*x*a;
    val += par[10]*y*x*a*a;
    val += par[11]*y*a*a*a;

    
    val += par[12]*b*x;                 
    val += par[13]*b*a;

    val += par[14]*y*y*y;
    val += par[15]*y*y*y*x;
    val += par[16]*y*y*y*a;

    val += par[17]*pow(y,3.0)*x*x;
    val += par[18]*pow(y,3.0)*x*a;
    val += par[19]*pow(y,3.0)*a*a;
      
    val += par[20]*b*x*x;
    val += par[21]*b*a*x;
    val += par[22]*b*a*a;

    val += par[23]*x;
    val += par[24]*x*x;
    val += par[25]*a;
    val += par[26]*a*a;

    //val += par[27]*pow(y,2.0);


   
    if(IsValidData==1) chisq += pow(val,2.0);
    
  }
  }
  f = chisq;
  
}


