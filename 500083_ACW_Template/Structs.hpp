#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

namespace structs
{
	enum TransportMode 
	{
		Foot = 0,
		Bike = 1,
		Car  = 2,
		Bus  = 3,
		Rail = 4,
		Ship = 5
	};
}

//Logging class

#define LOG_ENTRY_EXIT_FOR(x)       logging  SomeLongNameThatIsNotLikelyToBeUsedInTheFunctionlogger(x)
#define LOG_ENTRY_EXIT              LOG_ENTRY_EXIT_FOR(__func__)

class logging {
private:
	int dolog = 1; //Change dolog to 0 to disable logging
	std::string name;
public:
	logging(std::string x) :name(x) {
		if (dolog == 0) return;
		std::ofstream out;	
		out.open("output.txt", std::ios_base::app);
		time_t now = time(nullptr);
		out << "[" << std::put_time(localtime(&now), "%T") << "] - " << "ENTERED FUNCTION > " << name << "\n";
		out.close();
	}
	~logging() {
		if (dolog == 0) return;
		std::ofstream out;
		out.open("output.txt", std::ios_base::app);
		time_t now = time(nullptr);
		out << "[" << std::put_time(localtime(&now), "%T") << "] - " << "EXITED FUNCTION  < " << name << "\n";
		out.close();
	}
};