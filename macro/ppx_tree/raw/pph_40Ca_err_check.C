{
  double count_htcg=htcg->Integral(htcg->FindBin(17.83),htcg->FindBin(28.83));
  double count_hacg=hacg->Integral(htcg->FindBin(17.83),htcg->FindBin(28.83))/8.0;
  std::cout << "***Intgral Sx=[17.83 MeV, 28.83 MeV] (Ex=[-1 MeV, 10 MeV])***" << std::endl;

  std::cout << "htcg intgral: " << count_htcg << std::endl; 
  std::cout << "hacg intgral/8: " << count_hacg << std::endl;
  std::cout << "Count (tc-ac): " << count_htcg-count_hacg << std::endl;
  std::cout << "Err: " << sqrt(count_htcg+count_hacg) << std::endl;   
}
