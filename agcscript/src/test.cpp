#include "../head/agcs/agcscript.hpp"
#include <cstring>
#include <fstream>
#include <sstream>

int main() {

	std::ifstream file("exemple.agcs");
	std::stringstream stream;
	std::string line;
	
	if (!file.is_open()) {
		std::cout << "Could not open file " << std::endl;
///		exit(0);
		
        if (file.fail()) {
            // Print a more detailed error message using
            // strerror
            std::cerr << "Error details: " << strerror(errno)
                 << std::endl;
        }
	exit(0);
	}	
	
	while(std::getline(file, line)) {
		stream << line << std::endl;
	}
	
	//std::cout << stream.str() << std::endl;

	agcs::Scanner scanner{stream.str()};
}
