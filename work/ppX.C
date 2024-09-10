void ppX(int clust, int target,double Q, double qf_abs,TString name){

  TFile *fout = new TFile(name,"RECREATE");
  TTree *tree = new TTree("tree","data");

  int N=1000000;
  
  double T_inc=226.0; //beam energy (MeV)
  double mp=938.256;  //proton mass (MeV)

  //clust mass : 0: d, 1: t, 2: 3He, 3: alpha,
  double m_clust[4]={1875.581,2808.873,2808.343,3727.315};
  //Z of cluster
  double Z[4]={1.,1.,2.,2.};
  double mx=m_clust[clust];

  //0: 40Ca, 1:42Ca, 2: 44Ca, 3: 48Ca
  double m_target[4]={37224.274,39083.529,40943.564,44666.721};

  double mt=m_target[target];
  double mr=mt-mx+Q;
  //Q: Q value  > 0
  //qf_abs: fermi motion (MeV/c)


  //GR acceptance
  double delta_min=-0.0175;
  double delta_max=0.0175;  
  
  double a_min=-0.02;
  double a_max=0.02;

  double b_min= -0.07;
  double b_max= 0.07;    

  double theta_gr=TMath::DegToRad()*51.23;  //ppt
  double theta_las=TMath::DegToRad()*50.89; //ppt


  //caluc
  TVector3 qf;
  TVector3 q_tr;
  TRandom3 r;
  double x[3];
  double Sx;
  
  double Brho_p;
  double Brho_x;
  TLorentzVector p_cm;
  TLorentzVector x_cm;
  TLorentzVector p_lab;
  TLorentzVector x_lab;

  
  tree->Branch("mp",&mp,"mp/D");
  tree->Branch("mx",&mx,"mx/D");
  tree->Branch("Sx",&Sx,"Sx/D");
  tree->Branch("Brho_p",&Brho_p,"Brho_p/D");
  tree->Branch("Brho_x",&Brho_x,"Brho_x/D");
  tree->Branch("qf", "TVector3", &qf);
  tree->Branch("q_tr", "TVector3", &q_tr);
  tree->Branch("p_cm", "TLorentzVector", &p_cm);
  tree->Branch("x_cm", "TLorentzVector", &x_cm);
  tree->Branch("p_lab", "TLorentzVector", &p_lab);
  tree->Branch("x_lab", "TLorentzVector", &x_lab);
  
  
  

  for(int i=0;i<N;i++){

    //fermi motion
    r.Sphere(x[0],x[1],x[2],1); 
    qf.SetXYZ(x[0]*qf_abs,x[1]*qf_abs,x[2]*qf_abs);
    
    double T_res =  sqrt(mr*mr+qf.Mag2()) - mr ;    

    //p-X total p & E @lab
    TLorentzVector total_lab( qf.X() ,
			      qf.Y() ,
			      qf.Z()+sqrt(T_inc*T_inc+2*mp*T_inc) ,
			      (T_inc+mp+mt)-(T_res+mr));    
    //beta of cm
    TVector3 beta_cm(total_lab.Px()/total_lab.E(),
		     total_lab.Py()/total_lab.E(),
		     total_lab.Pz()/total_lab.E());

    total_lab.Boost(-beta_cm);
    double E_cm = total_lab.E();
    Double_t Ep_cm=0.5*( E_cm + (mp*mp-mx*mx)/E_cm );
    Double_t Ex_cm=0.5*( E_cm - (mp*mp-mx*mx)/E_cm );
    Double_t p_cm_abs=sqrt( Ep_cm*Ep_cm - mp*mp );
    
    r.Sphere(x[0],x[1],x[2],1);
    p_cm.SetPxPyPzE(p_cm_abs*x[0],p_cm_abs*x[1],p_cm_abs*x[2],Ep_cm);
    x_cm.SetPxPyPzE(-p_cm_abs*x[0],-p_cm_abs*x[1],-p_cm_abs*x[2],Ex_cm);
    
    
    p_lab=p_cm;
    p_lab.Boost(beta_cm);
    x_lab=x_cm;
    x_lab.Boost(beta_cm);
    
    Brho_p=sqrt(p_lab.E()*p_lab.E()-mp*mp)/299.792458;
    Brho_x=sqrt(x_lab.E()*x_lab.E()-mx*mx)/(299.792458*Z[clust]);

    q_tr.SetXYZ(x_lab.X()-qf.X(),x_lab.Y()-qf.Y(),x_lab.Z()-qf.Z());
    
    Sx=T_inc-(p_lab.E()+x_lab.E()-mp-mx);//-(sqrt(mr*mr+qf.Mag2())-mr);

    

    
    tree->Fill();


    //counter
    if(i%10000==0) std::cout << "evt: " << i << std::endl;

  }
  
  fout->Write();
  fout->Close();
  TFile *_file0 = TFile::Open(name);
}
