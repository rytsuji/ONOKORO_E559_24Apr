{
  TCut trig="trig_gr.fID==0";
  //TCut trig="trig_coin.fID==0";

  TCut grp_1="pla_gr_1@.GetEntriesFast()>0";
  TCut grp_2="pla_gr_2@.GetEntriesFast()>0";



  Int_t all_hit=tree->GetEntries(trig);
  Int_t grp_1_hit=tree->GetEntries(trig && grp_1);
  Int_t grp_2_hit=tree->GetEntries(trig && grp_2);
  Int_t grp_12_hit=tree->GetEntries(trig && grp_1 && grp_2);


  std::cout << " GR pla 1 MultiHit eff : " << (Double_t) grp_1_hit/all_hit*100.0 << " %" << std::endl;
  std::cout << " GR pla 2 MultiHit eff : " << (Double_t) grp_2_hit/all_hit*100.0 << " %" << std::endl;
  std::cout << " GR pla 1&2 MultiHit eff : " << (Double_t) grp_12_hit/all_hit*100.0 << " %" << std::endl;
  

  
}
