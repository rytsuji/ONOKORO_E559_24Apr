{
  TCut delta_gr_center="abs(p_lab.P()/(0.3*610.943*3.0)-1.0)<0.001";
  TCut delta_gr_pos="abs(p_lab.P()/(0.3*610.943*3.0)-1.0+0.0175)<0.001";
  TCut delta_gr_neg="abs(p_lab.P()/(0.3*610.943*3.0)-1.0-0.0175)<0.001";  

  tree->SetAlias("theta_gr","p_lab.Theta()*TMath::RadToDeg()");
  tree->SetAlias("phi_gr","p_lab.Phi()*TMath::RadToDeg()");

  tree->SetAlias("theta_las","x_lab.Theta()*TMath::RadToDeg()");
  tree->SetAlias("phi_las","x_lab.Phi()*TMath::RadToDeg()");
 
}
