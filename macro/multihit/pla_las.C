{
  TCut trig="trig_las.fID==0";
  //TCut trig="trig_coin.fID==0";
  TCut lasp_3="pla_las_3@.GetEntriesFast()>0";
  TCut lasp_4="pla_las_4@.GetEntriesFast()>0";
  TCut lasp_5="pla_las_5@.GetEntriesFast()>0";
  TCut lasp_6="pla_las_6@.GetEntriesFast()>0";



  Int_t all_hit=tree->GetEntries(trig);
  Int_t lasp_3_hit=tree->GetEntries(trig && lasp_3);
  Int_t lasp_4_hit=tree->GetEntries(trig && lasp_4);
  Int_t lasp_5_hit=tree->GetEntries(trig && lasp_5);  
  Int_t lasp_6_hit=tree->GetEntries(trig && lasp_6);

  std::cout << " LAS  pla 3 MultiHit eff : " << (Double_t) lasp_3_hit/all_hit*100.0 << " %" << std::endl;
  std::cout << " LAS  pla 4 MultiHit eff : " << (Double_t) lasp_4_hit/all_hit*100.0 << " %" << std::endl;
  std::cout << " LAS  pla 5 MultiHit eff : " << (Double_t) lasp_5_hit/all_hit*100.0 << " %" << std::endl;
  std::cout << " LAS  pla 6 MultiHit eff : " << (Double_t) lasp_6_hit/all_hit*100.0 << " %" << std::endl;
  

  

  
}
