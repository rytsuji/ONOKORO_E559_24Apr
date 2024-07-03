{

  TCut gr="trig_gr.fID==0";
  TCut las="trig_las.fID==0";
  TCut coin="trig_coin.fID==0";

  TCut grp1="pla_gr_1@.GetEntriesFast()>0";
  TCut grp2="pla_gr_2@.GetEntriesFast()>0";
  TCut lasp3="pla_las_3@.GetEntriesFast()>0";

  Int_t hit_grtrig=tree->GetEntries(gr);
  Int_t hit_cointrig=tree->GetEntries(coin);
  Int_t hit_lastrig=tree->GetEntries(las);
  Int_t hit_grp1_grtrig=tree->GetEntries(grp1 && gr);
  Int_t hit_grp1_cointrig=tree->GetEntries(grp1 && coin);
  Int_t hit_lasp3_lastrig=tree->GetEntries(lasp3 && las);
  Int_t hit_lasp3_cointrig=tree->GetEntries(lasp3 && coin);  

  std::cout << " GR  pla 1 MultiHit eff for  GR  trigger: " << (Double_t) hit_grp1_grtrig/hit_grtrig*100.0 << " %" << std::endl;
  std::cout << " GR  pla 1 MultiHit eff for coin trigger: " << (Double_t) hit_grp1_cointrig/hit_cointrig*100.0 << " %" << std::endl;

  std::cout << " LAS pla 3 MultiHit eff for  LAS trigger: " << (Double_t) hit_lasp3_lastrig/hit_lastrig*100.0 << " %" << std::endl;
  std::cout << " LAS pla 3 MultiHit eff for coin trigger: " << (Double_t) hit_lasp3_cointrig/hit_cointrig*100.0 << " %" << std::endl;    

  //std::cout << " GR pla 2 MultiHit eff for GR trigger: " << (Double_t) grp_1_hit/all_hit*100.0 << " %" << std::endl;
  //std::cout << " GR pla 2 MultiHit eff for GR trigger: " << (Double_t) grp_1_hit/all_hit*100.0 << " %" << std::endl;

  

  
}
