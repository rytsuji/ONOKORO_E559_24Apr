#include <yaml-cpp/yaml.h>

void test(void){
  std::string path_config="macro/ppx_tree/prm/ppt_40Ca.yaml";
  std::ifstream fin(path_config);    
  YAML::Node node  = YAML::Load(fin);    

  std::string  angGR = node["angGR"].as<std::string>();  
  //TCut angGR = Form("%s",(node["angGR"].as<std::string>()).c_str());
  std::cout << angGR << std::endl;

  return;
}
  
