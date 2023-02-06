#include <iostream>
#include <vector>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include <fstream>
#include <stdio.h>
#include <tracer.h>

//D:\works\litechrome\cefbuild\chromium_git\chromium\src\out\Relex_GN_x64\obj\third_party\abseil-cpp\absl\types\bad_variant_access\bad_variant_access.obj

void Log(const std::string &msg)
{
	std::cout << __FILE__ << " msg:" << msg.c_str() << std::endl; 	
}

bool isAccess(const std::string &filepath)
{
	SK_TRACE_FUNC()
	#ifdef _WIN32
	if(!_access(filepath.c_str(), 0))return true;
	#else
	if(!access(filepath.c_str(), F_OK))return true;		
	#endif
	else{
		// std::cout << "file not exist" << std::endl;
		return false;
	} 
}

void Split(const std::string &sfile, std::vector<std::string> &dsts, const std::string &idots)
{
	SK_TRACE_FUNC()
	dsts.clear();
	std::size_t start = sfile.find_first_not_of(idots, 0);
	std::size_t pos = sfile.find(idots, start);
	for(; start != std::string::npos; ){
		dsts.emplace_back(sfile.substr(start, pos-start));
		start = sfile.find_first_not_of(idots, pos);
		pos = sfile.find(idots, start);
	}
}

std::string parseFile(const std::string &filepath)
{
	SK_TRACE_FUNC()
	if(isAccess(filepath))
	{
		std::ifstream ifs;
		ifs.open(filepath);
		if(ifs.is_open()){
			ifs.seekg(0, std::ios::end);
			std::streampos pos = ifs.tellg();
			ifs.seekg(0, std::ios::beg);
			std::string s;
			char *ch = new char[pos];
			ifs.read(ch, pos);
			s = ch;
			ifs.close();
			delete ch;
			return s;
		}
	}
	return "";
}

void Display(const std::string &path, bool flag, bool bshow){
	// auto f = [](int a){ if(a) return  "is not empty"; else return "is empty";};std::cout << path.c_str() << f(flag) << std::endl;
	auto f = [&]{ 
		if(flag) 
		{
			if(bshow)
			std::cout << path.c_str() << " is not empty" << std::endl;
		}
		else
		{
			std::cout << path.c_str() << " is empty" << std::endl;
		}
	};
	f();
	// auto f = [=]{ if(flag) return  "is not empty"; else return "is empty";};std::cout << path.c_str() << f() << std::endl;
}

void help(char* argv[]){
	std::cout << "please input arguments like:" << argv[0] << " file.txt";
}

int main(int argc, char* argv[])
{
	if(argc < 2){
		help(argv);
		return -1;
	}
	
	if(argc == 3){
		for(int i = 1; i < argc; i++)
			Display(argv[i], isAccess(argv[i]), true);
		return 0;		
	}

	std::vector<std::string> arrs;
	Split(parseFile(argv[1]), arrs, " ");
	for(auto a : arrs){
		Display(a, isAccess(a), false);
	}
	return 0;
}
