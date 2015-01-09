#include "MJD.hpp"
#include "TimeTag.hpp"
#include "TestUtil.hpp"
#include <iostream>
#include <fstream>

using namespace gpstk;
using namespace std;

class MJD_T
{
	public:

	/* Test will check if MJD variable can be set from a map.
	   Test also implicity tests whether the != operator functions. */
	int setFromInfoTest (void)
	{
		MJD setFromInfo1;
		MJD setFromInfo2;
		MJD Compare(135000.0,TimeSystem(2)), Compare2(0.0,TimeSystem(2));
		TimeTag::IdToValue Id;
		Id['Q'] = "135000.0";
		Id['P'] = "GPS";
		if (!setFromInfo1.setFromInfo(Id)) return 1;
		if (setFromInfo1 != Compare) return 2;
		Id.erase('Q');
		if(!setFromInfo2.setFromInfo(Id)) return 3;
		if (setFromInfo2 != Compare2) return 4;

		return 0;
	}

	/* Test will check if the ways to initialize and set an MJD object.
	   Test also tests whether the comparison operators and isValid method function. */
	int operatorTest (void)
	{

		gpstk::MJD Compare(135000); // Initialize with value
		gpstk::MJD LessThanJD(134000); // Initialize with value
		gpstk::MJD CompareCopy(Compare); // Initialize with copy constructor
		gpstk::MJD CompareCopy2; //Empty initialization
		CompareCopy2 = CompareCopy; //Assignment

		//Equality Assertion
		if (!(Compare == CompareCopy)) return 1;
		//Non-equality Assertion
		if (!(Compare != LessThanJD)) return 2;
		//Less than assertions
		if (!(LessThanJD < Compare)) return 3;
		if (Compare < LessThanJD) return 4;
		//Greater than assertions
		if(!(Compare > LessThanJD)) return 5;
		//Less than equals assertion
		if (!(LessThanJD <= Compare)) return 6;
		if(!(CompareCopy <= Compare)) return 7;
		//Greater than equals assertion
		if(!(Compare >= LessThanJD)) return 8;
		if(!(Compare >= CompareCopy)) return 9;
		//Validity check
		if(!(Compare.isValid())) return 10;
		return 0;
	}

	/* Test will check the reset method. */
	int resetTest (void)
	{
	
	  	MJD Compare(135000,TimeSystem(2)); //Initialize an object
		// Check Initialization
  		if (!(Compare.getTimeSystem()==TimeSystem(2))) return 1; 
  		if (135000 != (int)Compare.mjd) return 2; 

	  	Compare.reset(); // Reset it
	  	if (TimeSystem(0) != Compare.getTimeSystem()) return 3; 
	  	if (0 != (int)Compare.mjd) return 4;
		return 0;
	}

	/* Test will check converting to/from CommonTime. */
	int toFromCommonTimeTest (void)
	{
	  	MJD Compare(135000,TimeSystem(2)); //Initialize an object
  		CommonTime Test = Compare.convertToCommonTime(); //Convert to

  		MJD Test2;
  		Test2.convertFromCommonTime(Test); //Convert From

  		if (!(Test2 == Compare)) return 1; // Converting to then from yields original

  		if (!(Compare.getTimeSystem()==TimeSystem(2))) return 2; // Recheck TimeSystem
  		if (135000 != (int)Compare.mjd) return 3; // Recheck value
		return 0;
	}

	/* Test will check the TimeSystem comparisons when using the comparison operators. */
	int timeSystemTest (void)
	{

  		MJD GPS1(135000,TimeSystem(2));
  		MJD GPS2(134000,TimeSystem(2));
  		MJD UTC1(135000,TimeSystem(5));
  		MJD UNKNOWN(135000,TimeSystem(0));
  		MJD ANY(135000,TimeSystem(1));

  		if (GPS1 == GPS2) return 1; // GPS1 and GPS2 should have different times
  		if (GPS1.getTimeSystem() != GPS2.getTimeSystem()) return 2; // Should have the same time system
  		if (GPS1 == UTC1) return 3; //Should have different time systems
  		if (GPS1 == UNKNOWN) return 4;

		// Perform comparisons to start of CommonTime
  		if (GPS1.convertToCommonTime() < CommonTime::BEGINNING_OF_TIME) return 11;
  		if (CommonTime::BEGINNING_OF_TIME > GPS1) return 12;
		
		// Make TimeSystem part not matter and perform comparisons
		// which solely depend on the time value.
  		if (GPS1 != ANY) return 5; 
  		if (UTC1 != ANY) return 6;
  		if (UNKNOWN != ANY) return 7;
  		if (GPS2 == ANY) return 8;
  		if (GPS2 > GPS1) return 9;
  		if (GPS2 > ANY) return 10;

  		UNKNOWN.setTimeSystem(TimeSystem(2)); //Set the Unknown TimeSystem
  		if (UNKNOWN.getTimeSystem()!=TimeSystem(2)) return 13;
		return 0;
	}
	/* Test for the formatted printing of MJD objects */
	int printfTest (void)
	{

  		MJD GPS1(135000,TimeSystem(2));
  		MJD UTC1(135000,TimeSystem(7));
		
  		if (GPS1.printf("%08Q %02P") != (std::string)"135000.000000 GPS") return 1;
  		if (UTC1.printf("%08Q %02P") != (std::string)"135000.000000 UTC") return 2;
  		if (GPS1.printError("%08Q %02P") != (std::string)"ErrorBadTime ErrorBadTime") return 3; 
  		if (UTC1.printError("%08Q %02P") != (std::string)"ErrorBadTime ErrorBadTime") return 4;
		return 0;
	}
};

void checkResult(int check, int& errCount) // Function to handle test result output
{
	if (check == -1)
	{
		std::cout << "DIDN'T RUN!!!!" << std::endl;
	}
	else if (check == 0 )
	{
		std::cout << "GOOD!!!!" << std::endl;
	}
	else if (check > 0)
	{
		std::cout << "BAD!!!!" << std::endl;
		std::cout << "Error Message for Bad Test is Code " << check << std::endl;
		errCount++;
	}
}

int main() //Main function to initialize and run all tests above
{
	int check, errorCounter = 0;
	MJD_T testClass;
	check = testClass.operatorTest();
        std::cout << "opertatorTest Result is: ";
	checkResult(check, errorCounter);
	check = -1;

	check = testClass.setFromInfoTest(); // Not run due to issue with Solaris compiler.
        std::cout << "setFromInfoTest Result is: ";
	checkResult(check, errorCounter);
	check = -1;

	check = testClass.resetTest();
        std::cout << "resetTest Result is: ";
	checkResult(check, errorCounter);
	check = -1;

	check = testClass.timeSystemTest();
        std::cout << "timeSystemTest Result is: "; 
	checkResult(check, errorCounter);
	check = -1;
	check = testClass.toFromCommonTimeTest();
        std::cout << "toFromCommonTimeTest Result is: "; 
	checkResult(check, errorCounter);
	check = -1;

	check = testClass.printfTest();
        std::cout << "printfTest Result is: ";
	checkResult(check, errorCounter);
	check = -1;
	
	std::cout << "Total Errors: " << errorCounter << std::endl;

	return errorCounter; //Return the total number of errors
}
