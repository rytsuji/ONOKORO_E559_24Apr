//void ppX(int clust, int target,double Q, double kf_abs, double theta_gr, double theta_las, double BGR, TString name){

void ppt(int target,double Q, double theta_gr, double theta_las, double BGR,TString name){

  int clust=1;
  
  //TFile *fout = new TFile(name,"RECREATE");
  //TTree *tree = new TTree("tree","data");

  ofstream ofile(name); 
  
  int N=100000;
  int N_kf=100;
  int N_theta=100;  
  
  double kf_max=100.0; //MeV/c
  //double theta_cm_range[2]={60.0,80.0};
  double theta_cm_range[2]={65.0,75.0};
  
  double T_inc=226.0; //beam energy (MeV)
  double mp=938.256;  //proton mass (MeV)

  //clust mass : 0: d, 1: t, 2: 3He, 3: alpha,
  double m_clust[4]={1875.581,2808.873,2808.343,3727.315};
  //Z of cluster
  double Z[4]={1.,1.,2.,2.};
  double mx=m_clust[clust];

  //0: 40Ca, 1:42Ca, 2: 44Ca, 3: 48Ca
  double m_target[4]={37214.06,39073.32,40933.36,44656.51};

  double mt=m_target[target];
  double mr=mt-mx+Q;
  //Q: Q value  > 0
  //kf_abs: fermi motion (MeV/c)


  

  //GR acceptance
  double delta_min=-0.0175;
  double delta_max=0.0175;  
  
  double a_min=-0.02;
  double a_max=0.02;

  double b_min= -0.07;
  double b_max= 0.07;    

  theta_gr = theta_gr*TMath::DegToRad();
  theta_las = theta_las*TMath::DegToRad();


  //caluc
  TVector3 kf;
  TVector3 q_tr;
  TRandom3 r;
  TRandom phi_rand;  
  double x[3];
  double Sx;

  double Brho_p;
  double Brho_x;
  TLorentzVector p_cm;
  TLorentzVector x_cm;
  TLorentzVector p_lab;
  TLorentzVector x_lab;

  double a_gr, b_gr;
  double a_las, b_las;

  int req=0;
  int acc=0;  
  
  /*
  tree->Branch("mp",&mp,"mp/D");
  tree->Branch("mx",&mx,"mx/D");
  tree->Branch("Sx",&Sx,"Sx/D");
  tree->Branch("Brho_p",&Brho_p,"Brho_p/D");
  tree->Branch("Brho_x",&Brho_x,"Brho_x/D");
  tree->Branch("kf", "TVector3", &kf);
  tree->Branch("q_tr", "TVector3", &q_tr);
  tree->Branch("p_cm", "TLorentzVector", &p_cm);
  tree->Branch("x_cm", "TLorentzVector", &x_cm);
  tree->Branch("p_lab", "TLorentzVector", &p_lab);
  tree->Branch("x_lab", "TLorentzVector", &x_lab);

  tree->Branch("a_gr",&a_gr,"a_gr/D");
  tree->Branch("b_gr",&b_gr,"b_gr/D");  
  tree->Branch("a_las",&a_las,"a_las/D");
  tree->Branch("b_las",&b_las,"b_las/D");    
  */
  
  for(int i_kf=0; i_kf<N_kf+1; i_kf++){

    double kf_abs=kf_max*((double) i_kf/N_kf);
    std::cout << "********** kf: " << kf_abs << " (MeV/c) **********" << std::endl;

    for(int i_theta=0; i_theta<N_theta+1; i_theta++){
    
      double theta_cm=theta_cm_range[0]+(theta_cm_range[1]-theta_cm_range[0])*((double) i_theta/N_theta);
      //std::cout << "  theta_cm: " << theta_cm << " (deg)" << std::endl;  

      req = 0;
      acc = 0;
      
      for(int i=0;i<N;i++){           
	//fermi motion
	r.Sphere(x[0],x[1],x[2],1); 
	kf.SetXYZ(x[0]*kf_abs,x[1]*kf_abs,x[2]*kf_abs);
      
	double T_res =  sqrt(mr*mr+kf.Mag2()) - mr ;    
	
	//p-X total p & E @lab
	TLorentzVector total_lab( kf.X(),
				  kf.Y(),
				  kf.Z()+sqrt(T_inc*T_inc+2*mp*T_inc),
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
	
	//r.Sphere(x[0],x[1],x[2],1);

	
	double phi_cm=phi_rand.Uniform(-15.0,15.0);
	x[0]=sin(theta_cm*TMath::DegToRad())*cos(phi_cm*TMath::DegToRad());
	x[1]=sin(theta_cm*TMath::DegToRad())*sin(phi_cm*TMath::DegToRad());
	x[2]=cos(theta_cm*TMath::DegToRad());
	
	p_cm.SetPxPyPzE(p_cm_abs*x[0],p_cm_abs*x[1],p_cm_abs*x[2],Ep_cm);
	x_cm.SetPxPyPzE(-p_cm_abs*x[0],-p_cm_abs*x[1],-p_cm_abs*x[2],Ex_cm);
	
	
	p_lab=p_cm;
	p_lab.Boost(beta_cm);
	x_lab=x_cm;
	x_lab.Boost(beta_cm);
	
	Brho_p=sqrt(p_lab.E()*p_lab.E()-mp*mp)/299.792458;
	Brho_x=sqrt(x_lab.E()*x_lab.E()-mx*mx)/(299.792458*Z[clust]);
	
	q_tr.SetXYZ(x_lab.X()-kf.X(),x_lab.Y()-kf.Y(),x_lab.Z()-kf.Z());
      
	Sx=T_inc-(p_lab.E()+x_lab.E()-mp-mx);//-(sqrt(mr*mr+kf.Mag2())-mr);
	
	TVector3 e_r_gr(sin(theta_gr),
			0.0,
		      cos(theta_gr));  
	TVector3 e_theta_gr(cos(theta_gr),
			    0.0,
			    -sin(theta_gr));
	
	TVector3 e_phi_gr(0.0,
			  1.0,
			  0.0);
      
	TVector3 e_r_las(-sin(theta_las),
			 0.0,
			 cos(theta_las));  
	TVector3 e_theta_las(-cos(theta_las),
			     0.0,
			   -sin(theta_las));
	TVector3 e_phi_las(0,
			   -1.0,
			   0.0);
	
	a_gr = (p_lab.Px()*e_theta_gr.X()+p_lab.Py()*e_theta_gr.Y()+p_lab.Pz()*e_theta_gr.Z())/(p_lab.Px()*e_r_gr.X()+p_lab.Py()*e_r_gr.Y()+p_lab.Pz()*e_r_gr.Z());
	b_gr = (p_lab.Px()*e_phi_gr.X()+p_lab.Py()*e_phi_gr.Y()+p_lab.Pz()*e_phi_gr.Z())/(p_lab.Px()*e_r_gr.X()+p_lab.Py()*e_r_gr.Y()+p_lab.Pz()*e_r_gr.Z());
	
	a_las = (x_lab.Px()*e_theta_las.X()+x_lab.Py()*e_theta_las.Y()+x_lab.Pz()*e_theta_las.Z())/(x_lab.Px()*e_r_las.X()+x_lab.Py()*e_r_las.Y()+x_lab.Pz()*e_r_las.Z());
	b_las = (x_lab.Px()*e_phi_las.X()+x_lab.Py()*e_phi_las.Y()+x_lab.Pz()*e_phi_las.Z())/(x_lab.Px()*e_r_las.X()+x_lab.Py()*e_r_las.Y()+x_lab.Pz()*e_r_las.Z());


	
              	
	if(abs(fmod(x_lab.Phi()*TMath::RadToDeg()+360.0,360.0)-180.0)<3.5) req++;
	if(abs(fmod(x_lab.Phi()*TMath::RadToDeg()+360.0,360.0)-180.0)<3.5 &&
	   abs(x_lab.Theta()*TMath::RadToDeg()-50.9)<3.4 &&
	   abs(p_lab.Theta()*TMath::RadToDeg()-51.2)<1.0 &&
	   abs(p_lab.Phi()*TMath::RadToDeg())<3.5 &&
	   abs(p_lab.Phi()*TMath::RadToDeg())<(4.0*p_lab.Theta()*TMath::RadToDeg()-199.3) &&
	   abs(p_lab.Phi()*TMath::RadToDeg())<(-5.0*p_lab.Theta()*TMath::RadToDeg()+262.5) &&
	   abs(p_lab.E()-p_lab.M()-149.0)<4.0) acc++;       	
      }
      ofile << kf_abs << " " << theta_cm << " " <<  (double) acc/req << " " << acc << " "  << req << std::endl;
    }
    ofile << std::endl;
  }
  //fout->Write();
  //fout->Close();
  //TFile *_file0 = TFile::Open(name);
  ofile.close();
}
