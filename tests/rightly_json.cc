#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>

using namespace nlohmann;

class Weekly{
	public:
		std::string _wkDate{""};
		std::string _wkKeyBoard{""};
		std::string _wkMouse{""};

		Weekly(){}
		Weekly(std::string d, std::string k, std::string m):_wkDate(d),_wkKeyBoard(k),_wkMouse(m){}
};
namespace wkl{
	std::string date(){
		time_t t = ::time(nullptr);
		struct tm * st = localtime(&t);
		std::stringstream ss;
		ss << st->tm_year + 1900 
		<< "-" << std::to_string((1+st->tm_mon)/10) << std::to_string((1+st->tm_mon)%10) 
		<< "-" << std::to_string(st->tm_mday/10) << std::to_string(st->tm_mday%10);
		return ss.str();
	}

	std::string time(){
		time_t t = ::time(nullptr);
		struct tm * st = localtime(&t);
		std::stringstream ss;
		ss << st->tm_year + 1900 
		<< "-" << std::to_string((1+st->tm_mon)/10) << std::to_string((1+st->tm_mon)%10) 
		<< "-" << std::to_string(st->tm_mday/10) << std::to_string(st->tm_mday%10)
		<< " " << st->tm_hour << ":" << st->tm_min << ":" << st->tm_sec;
		return ss.str();
	}
}

void help(char* argv[]){
	std::cout << "please input arguments like:" << argv[1] << " file"  << std::endl;
} 

void Display(const std::string& msg){
	std::cout << msg.c_str() << std::endl;
}

int to_number(const std::string &s)
{
	if(s == "")return 0;
	std::stringstream ss;
	ss << s;
	int ret;
	ss >> ret;
	return ret;
}

void DumpWeekly(const std::vector<Weekly> & allKeys, json &jobj)
{
	for(auto ak : allKeys){
		json ji;
		ji["keyboard"] = to_number(ak._wkKeyBoard);
		ji["mouse"] = to_number(ak._wkMouse); 
		jobj[ak._wkDate] = ji;
	}
}

int main(int argc, char* argv[])
{
	if(argc < 2){
		help(argv);return -1;
	}
	std::vector<Weekly> allKeys;
	std::ifstream ifs(argv[1]);
	json j;
	ifs >> j;
	// Display(wkl::date());
	// Display(wkl::time());
	std::string s;
	for(int y = 2023; y >= 2022; y--){
		if(y == 2023){
			for(int m = 2; m >= 1; m--){
				if( m == 2){
					for(int d = 7; d >= 1; d--){
						s = std::to_string(y) + "-" + std::to_string(m/10)+ std::to_string(m%10) 
						+ "-" + std::to_string(d/10) + std::to_string(d%10);
						if(j.contains(s)){
							// Display(s + " " + j[s].dump());
							Weekly wl;
							wl._wkDate = s;
							if(j[s].contains("keyboard")){
								wl._wkKeyBoard = j[s]["keyboard"].dump();
								wl._wkMouse = j[s]["mouse"].dump();
							}
							else wl._wkKeyBoard = j[s].dump();
							allKeys.push_back(wl);
						}
					}
				}else{
					for(int d = 31; d >= 1; d--){
						s = std::to_string(y) + "-" + std::to_string(m/10)+ std::to_string(m%10) 
						+ "-" + std::to_string(d/10) + std::to_string(d%10);
						if(j.contains(s)){
							if(j[s].contains("keyboard")){
								allKeys.emplace_back(Weekly(s, j[s]["keyboard"].dump(), j[s]["mouse"].dump()));
							}else{
								allKeys.emplace_back(s, j[s].dump(), "");
							}
						}
					}
				}
			}
		}else{
			for(int m = 12; m >= 1; m--){
				for(int d = 31; d >= 1; d--){
					s = std::to_string(y) + "-" + std::to_string(m/10)+ std::to_string(m%10) 
						+ "-" + std::to_string(d/10) + std::to_string(d%10);
					if(j.contains(s)){
						// Display(s +" " +  j[s].dump());
						Weekly wl;
						wl._wkDate = s;
						if(j[s].contains("keyboard")){
							wl._wkKeyBoard = j[s]["keyboard"].dump();
							wl._wkMouse = j[s]["mouse"].dump();
						}
						else wl._wkKeyBoard = j[s].dump();
						allKeys.push_back(wl);
					}
				}
			}
		}
	}
	
	json jout;
	DumpWeekly(allKeys, jout);
	if(!jout.is_null()){
		Display(jout.dump());
		std::ofstream ofs("output.json");
		ofs << jout;
		ofs.close();
	}
	return 0;
}
