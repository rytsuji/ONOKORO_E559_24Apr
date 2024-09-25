//void ppX_ang(int clust, int target,double Q, double BGR, double delta_gr ,TString name){
void ppX_qf0(int clust, int target,double Q, TString name){

  ofstream ofile(name);

  int N_tp=200000;
  
  double Tp_min=144;
  double Tp_max=156;  
  
  
  double T_inc=226.0; //beam energy (MeV)
  double mp=938.256;  //proton mass (MeV)

  //clust mass : 0: d, 1: t, 2: 3He, 3: alpha,
  double m_clust[4]={1875.581,2808.873,2808.343,3727.315};
  //Z of cluster
  double Z[4]={1.,1.,2.,2.};
  double mx=m_clust[clust];

  //0: 40Ca, 1:42Ca, 2: 44Ca, 3: 48Ca 4: 12C, 5: 16O
  double m_target[6]={37214.06,39073.32,40933.36,44656.51,11174.67,14894.82};

  double mt=m_target[target];
  double mr=mt-mx+Q;  
  double qf_abs=0.0;
  
  for(int i_tp=0;i_tp<N_tp+1;i_tp++){
    
    double Tp=Tp_min+(Tp_max-Tp_min)*((double) i_tp/N_tp);
    
    //fermi motion    
    TVector3 qf(0,0,0);
    
    //kinetic energy of residual
    double T_res =  sqrt(mr*mr+qf.Mag2()) - mr ;    
    
    //p-X total p & E @lab
    TLorentzVector total_lab( -qf.X() ,
			      -qf.Y() ,
			      -qf.Z()+sqrt(T_inc*T_inc+2*mp*T_inc) ,
			      (T_inc+mp+mt)-(T_res+mr));    
    
    //double Tp=sqrt(pow(0.3*BGR*3.0*(1+delta_gr),2.0)+mp*mp)-mp;
    //double Tp=sqrt(pow(0.3*BGR*3.0*(1+delta_gr),2.0)+mp*mp)-mp;
    double Tx=total_lab.E()-(Tp+mp+mx);
      
    double theta_p_prime=acos(  ((Tp*Tp+2*Tp*mp)-(Tx*Tx+2*Tx*mx)+pow(total_lab.P(),2.0))/(2.0*sqrt(Tp*Tp+2*Tp*mp)*total_lab.P()) );
    double theta_x_prime=acos( (-(Tp*Tp+2*Tp*mp)+(Tx*Tx+2*Tx*mx)+pow(total_lab.P(),2.0))/(2.0*sqrt(Tx*Tx+2*Tx*mx)*total_lab.P()) );    
    
    ofile << Tp << " ";
    ofile << TMath::RadToDeg()*(theta_p_prime+total_lab.Theta()) << " ";
    ofile << TMath::RadToDeg()*(theta_x_prime-total_lab.Theta()) << std::endl;         
}

  ofile.close();

}
