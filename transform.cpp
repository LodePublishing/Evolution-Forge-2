#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		return 1;
	}
	std::ostringstream os;
	os << argv[1];
	std::string file = os.str();
	std::string outfilename = file.substr(0, file.size()-3) + "html";

	std::ofstream outfile;
	outfile.open(outfilename.c_str());

	std::map<std::string, int> oldstats;
	std::ifstream infile;
	std::string oldfile = file + ".old";
	infile.open(oldfile.c_str());

	std::string line;

	while(std::getline(infile, line)) {
		std::string filename = line.substr(15, line.size()-16);	
		std::getline(infile, line);
		int length = line.find("%") - 15;
                std::string percent = line.substr(15, length);
                int percent_number = atoi(percent.c_str());

		oldstats[filename] =  percent_number;
	}
	infile.close();	
	

	infile.open(file.c_str());
	
	outfile << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" dir=\"ltr\" lang=\"de\"><head /><body><center><H1>Coverage EF2</H1><br /><br /><table border=\"3\" bordercolor=\"#c86260\" bgcolor=\"#ffffcc\" width=\"75%\" cellspacing=\"5\" cellpadding=\"3\"><tr><td>FILE</td><td>Coverage</td></tr>";

	while(std::getline(infile, line)) {
		std::string filename = line.substr(15, line.size()-16);	
		std::getline(infile, line);

		int length = line.find("%") - 15;
		std::string percent = line.substr(15, length);
		int percent_number = atoi(percent.c_str());
		outfile << "<tr><td valign=\"top\"><b><a href=\"gcov/" << filename << ".gcov\">" << filename << "</a></b></td><td>";
		for(int i = 0; i < percent_number / 5; i++) {
			outfile << "*";
		}
		outfile << " " << percent << "%";
		if(oldstats.find(filename) != oldstats.end()) {
			int difference = percent_number - oldstats.find(filename)->second;
			if(difference != 0) {
				if(difference > 0) {
					outfile << "&nbsp;<font color=\"green\">+";
				} else if(difference < 0) {
					outfile << "&nbsp;<font color=\"red\">";
				}
				outfile << difference << "%</font>";
			}
		}
		outfile << "</td></tr>";
	} 

	outfile << "</table></center></body></html>";

	infile.close();
	outfile.close();

	return 0;
}

