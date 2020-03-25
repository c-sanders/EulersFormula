#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <cmath>
// std::sin, std::cos
#include <utility>
// std::pair

#include <boost/lexical_cast.hpp>
// boost::lexical_cast

#include <EulersFormula.hpp>


using std::pair;
using std::cout;
using std::endl;
using std::cos;
using std::sin;


// Forward declaration of the function which is defined below.

void
display_usage
(
 const
 string   nameExecutable
);


int
main
(
 int    argc,
 char * argv[]
)
{
	string                           argumentHelp    = "--help";
	
	int                              numComponents = 0;

	long double                      angleRadians  = 0;

	EulersFormula                  * object_p      = nullptr;

	pair<long double, long double>   complexResult;


	// --------------------------------------------------------------------------------------------
	// Step 1)
	//
	// Analyse the command line arguments and proceed accordingly.
	// --------------------------------------------------------------------------------------------
	
	if (argc == 2)
	{
		if (
		    (argumentHelp.compare("--help") == 0) ||
		    (argumentHelp.compare("-h")     == 0)
		   )
		{
			display_usage(argv[0]);

			goto return_routine;
		}
	}

	if (argc != 3)
	{
		cout << "argc != 3" << endl;

		display_usage(argv[0]);

		goto return_routine;
	}

	numComponents = boost::lexical_cast<int>(argv[1]);

	if (numComponents <= 0)
	{
		display_usage(argv[0]);

		goto return_routine;
	}

	angleRadians = boost::lexical_cast<double long>(argv[2]);

	cout << numComponents << endl;
	cout << angleRadians  << endl;


	// --------------------------------------------------------------------------------------------
	// Step 2)
	//
	// Create an appropriately configured object and then instruct it to compute a value for
	// Euler's formula based on the values it was configured with.
	// --------------------------------------------------------------------------------------------

	object_p = new EulersFormula(numComponents, angleRadians);

	std::cout << "limit = " << numComponents << std::endl; 

	complexResult = object_p->compute();


	// --------------------------------------------------------------------------------------------
	// Step 3)
	//
	// Display the results.
	// --------------------------------------------------------------------------------------------

	// Manipulate the ostream so that the results can be displayed in a nicer fashion.
	//
	//   - Set the precision width to be fixed.
	//   - ...
	//   - ...

	std::cout << std::fixed << std::setw(12) << std::setprecision(18);

	std::cout << endl << endl;
	
	std::cout << "Answer (e^j)       = " << complexResult.first << " + j" << complexResult.second << endl;
	std::cout << "Answer (cos / sin) = " << cos(angleRadians) << " + j" << sin(angleRadians) << endl;


	// --------------------------------------------------------------------------------------------
	// Step 4)
	//
	// Cleanup and then exit from this function.
	// --------------------------------------------------------------------------------------------

	return_routine :
	{
		delete(object_p);

		return(0);
	}
}


void
display_usage
(
 const
 string   nameExecutable
)
{
	cout << endl;
	cout << "Usage :" << endl;
	cout << endl;
	cout << "  " << nameExecutable << " num_components angle" << endl;
	cout << endl;
	cout << "where;" << endl;
	cout << endl;
	cout << "num_components : the number of the highest component which should be used in the calculation of Euler's formula." << endl;
	cout << "angle          : the angle in Radians for which Euler's formula should be calculated." << endl;
	cout << endl;
}
