#include <EulersFormula.hpp>

#include <numeric>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_sf_gamma.h>
// factorial function

// 0.764842187284488426 + j0.644217687237691054
// 0.764842187284488426 + j0.644217687237691054


// static
void
EulersFormula::errorHandlerGSL
(
 const
 char * reason_p,
 const
 char * file_p,
 int    lineNumber,
 int    errnoGSL
)
noexcept
(
 false
)
{
	const
	string          nameMethod = "errorHandlerGSL : ";

	// runtime_error * e_p        = new runtime_error("GSL error");


	cout << nameMethod << "Enter" << endl;

	cout << "==================================" << endl;	
	cout << "GSL reported the following error :" << endl;
	cout << "==================================" << endl;
	cout << "File         : " << file_p << endl;
	cout << "Line number  : " << lineNumber << endl;
	cout << "Error number : " << errnoGSL << endl;
	cout << "Reason       : " << reason_p << endl;

	cout << nameMethod << "About to throw an exception" << endl;

	cout << nameMethod << "Exit" << endl;

	throw runtime_error("GSL Error.");
}


// Method
// ======
//
// Visibility : public
//
// Invoked by :
//
// Invokes    : EulersFormula::setNumComponents
//              EulersFormula::setAngleRadians

/**
 * \brief Constructor for the class.
 */

EulersFormula::EulersFormula
(
 int           numComponents,
 long double   angleRadians
)
{
	const
	string   nameMethod = "EulersFormula Ctor : ";


	cout << nameMethod << "Enter" << endl;

	this->counter = 0;
	this->realSum = 0;
	this->imagSum = 0;

	this->setNumComponents(numComponents);
	this->setAngleRadians(angleRadians);

	// gsl_set_error_handler(EulersFormula::errorHandlerGSL);

	this->gslErrorHandler_p = gsl_set_error_handler(this->errorHandlerGSL);

	cout << nameMethod << "Exit" << endl;
}


// Method
// ======
//
// Visibility : public
//
// Invoked by : * Client *
//
// Invokes    :

/**
 * \brief Destructor for the class.
 */

EulersFormula::~EulersFormula
(
)
{
	gsl_set_error_handler(this->gslErrorHandler_p);
}


// Method
// ======
//
// Visibility : public
//
// Invoked by : * Client *
//              EulersFormula::Ctor
//
// Invokes    :

/**
 * \brief Set the number of components which should be used for the computation of Euler's formula.
 */

void
EulersFormula::setNumComponents
(
 int   numComponents
)
{
	if (numComponents <= 0)
	{
		this->numComponents = 0;
	}
	else
	{
		this->numComponents = numComponents;
	}
}


// Method
// ======
//
// Visibility : public
//
// Invoked by : * Client *
//              EulersFormula::Ctor
//
// Invokes    :

/**
 * \brief Set the angle (in Radians) which should be used for the computation of Euler's formula.
 */

void
EulersFormula::setAngleRadians
(
 long double   angleRadians
)
{
	this->angleRadians = angleRadians;
}


// Method
// ======
//
// Visibility : public
//
// Invoked by : * Client *
//
// Invokes    : EulersFormula::computeComponents
//              EulersFormula::sumComponents
//              EulersFormula::getResult

/**
 * \brief Compute Euler's formula to the specified number of components - both Real and Imaginary, and using the specified angle.
 */

std::pair<long double, long double>
EulersFormula::compute
(
)
{
	this->computeComponents();
	this->sumComponents();

	return(this->getResult());
}


// Method
// ======
//
// Visibility : private
//
// Invoked by : * Client *
//
// Invokes    :

/**
 * \brief Get the values of the specified number of components, both Real and Imaginary.
 */

std::pair<long double, long double>
EulersFormula::getResult
(
)
{
	std::pair<long double, long double>   components;


	// std::pair<std::list<long double>, std::list<long double> >complexResult(this->realSum, this->imagSum);

	components = std::make_pair(this->realSum, this->imagSum);

	return(components);
}


// Method
// ======
//
// Visibility : private
//
// Invoked by : * Client *
//
// Invokes    :

/**
 * \brief Get the values of the specified number of components, both Real and Imaginary.
 */

std::pair<std::list<long double>, std::list<long double> >
EulersFormula::getResultComponents
(
)
{
	std::pair<std::list<long double>, std::list<long double> >   components;


	components = std::make_pair(this->realComponents, this->imagComponents);

	return(components);
}


// Method
// ======
//
// Visibility : private
//
// Invoked by :
//
// Invokes    :

/**
 * \brief Compute the values for the specified number of components.
 */

void
EulersFormula::computeComponents
(
)
{
	const
	string   nameMethod = "EulersFormula::computeComponents : ";

	int      multiplier = 1;


	cout << nameMethod << "Enter" << endl;

	this->counter = 0;

	while
	(
	 this->counter <= this->numComponents
	)
	{
		long double   currentComponent;


		// Real component

		try
		{
			currentComponent = multiplier * (this->computeComponent(this->angleRadians, this->counter));
		}
		catch (runtime_error & e)
		{
			cout << nameMethod << "Caught an Exception." << endl;
			cout << nameMethod << "Exception info : " << e.what() << endl;

			break;
		}

		++(this->counter);

		// realSum += (multiplier * currentComponent);

		this->realComponents.push_back(currentComponent);

		cout << "Component = " << (this->counter - 1) << endl;

		// Imaginary component

		if (this->counter <= this->numComponents)
		{
			try
			{
				currentComponent = multiplier * (this->computeComponent(this->angleRadians, this->counter));
			}
			catch (runtime_error & e)
			{
				cout << nameMethod << "Caught an Exception." << endl;
				cout << nameMethod << "Exception info : " << e.what() << endl;
	
				break;
			}

			++(this->counter);

			// imagSum += (multiplier * currentComponent);

			this->imagComponents.push_back(currentComponent);

			cout << "Component = " << (this->counter - 1) << endl;
		}

		multiplier *= -1;
	}

	std::cout << "this->realComponents contains : " << this->realComponents.size() << " elements" << std::endl; 
	std::cout << "this->imagComponents contains : " << this->imagComponents.size() << " elements" << std::endl; 
}


// Method
// ======
//
// Visibility : private
//
// Invoked by : compute
//
// Invokes    :

/**
 * \brief Sum together all the Real components into one value, and all the Imaginary components into another value.
 */

void
EulersFormula::sumComponents
(
)
{
	const
	string   nameMethod = "EulersFormula::sumComponents : ";


	cout << nameMethod << "Enter" << endl;

	this->realSum = std::accumulate
	                (
	                 this->realComponents.begin(),
	                 this->realComponents.end(),
	                 this->realSum
	                );

	this->imagSum = std::accumulate
	                (
	                 this->imagComponents.begin(),
	                 this->imagComponents.end(),
	                 this->imagSum
	                );

	cout << nameMethod << this->realSum << endl;
	cout << nameMethod << this->imagSum << endl;

	cout << nameMethod << "Exit" << endl;
}


// Method
// ======
//
// Visibility : private
//
// Invoked by :
//
// Invokes    :

/**
 * \brief Get the values of all the necessary Real components.
 */

std::list<long double>
EulersFormula::getRealComponents
(
)
{
	const
	string   nameMethod = "EulersFormula::getRealComponents : ";


	cout << nameMethod << "Enter" << endl;

	cout << nameMethod << "Exit" << endl;
	
	return(this->realComponents);
}


// Method
// ======
//
// Visibility : private
//
// Invoked by :
//
// Invokes    :

/**
 * \brief Get the values of all the necessary Imaginary components.
 */

std::list<long double>
EulersFormula::getImagComponents
(
)
{
	const
	string   nameMethod = "EulersFormula::getImagComponents : ";


	cout << nameMethod << "Enter" << endl;

	cout << nameMethod << "Exit" << endl;
	
	return(this->imagComponents);
}


// Method
// ======
//
// Visibility : private
//
// Invoked by : computeComponents
//
// Invokes    : EulersFormula::computeComponentUsingException

long double
EulersFormula::computeComponent
(
 long double   angleRadians,
 int           numberComponent
)
noexcept
(
 false  // This method may throw Exception(s).
)
{
	const
	string        nameMethod = "EulersFormula::computeComponent : ";

	long double   currentComponent = 0;


	cout << nameMethod << "Enter" << endl;
	cout << nameMethod << "Component number = " << numberComponent << endl;

	currentComponent = this->computeComponentUsingException(angleRadians, numberComponent);

	cout << nameMethod << "Exit" << endl;

	return(currentComponent);
}


// Method
// ======
//
// Visibility : private
//
// Invoked by : computeComponent
//
// Invokes    : EulersFormula::raiseBaseToPower

long double
EulersFormula::computeComponentUsingErrorCode
(
 long double   angleRadians,
 int           numberComponent
)
noexcept
(
 false  // This method may throw Exception(s).
)
{
	const
	string          nameMethod = "EulersFormula::computeComponentUsingErrorCode : ";

	int             errorStatus;
	
	gsl_sf_result   result;
	
	long double     currentComponent = 0;

	long double     numerator,
	                denominator;


	cout << nameMethod << "Enter" << endl;

	// Compute the value of the numerator.

	numerator = this->raiseBaseToPower(angleRadians, numberComponent);

	// Compute the value of the denominator.

	errorStatus = gsl_sf_fact_e(numberComponent, & result);

	if (errorStatus != 0)
	{
		throw runtime_error("GSL Error.");
	}

	denominator = result.val;

	// Compute the value for the current component.

	currentComponent = numerator / denominator; 

	cout << nameMethod << "Exit" << endl;

	return(currentComponent);
}


// Method
// ======
//
// Visibility : private
//
// Invoked by : computeComponent
//
// Invokes    : EulersFormula::raiseBaseToPower

long double
EulersFormula::computeComponentUsingException
(
 long double   angleRadians,
 int           numberComponent
)
noexcept
(
 false  // This method may throw Exception(s).
)
{
	const
	string        nameMethod = "EulersFormula::computeComponentUsingException : ";

	long double   currentComponent = 0;

	long double   numerator;

	double        denominator;


	cout << nameMethod << "Enter" << endl;

	numerator = this->raiseBaseToPower(angleRadians, numberComponent);

	denominator = gsl_sf_fact(numberComponent);

	currentComponent = numerator / denominator; 

	cout << nameMethod << "Exit" << endl;

	return(currentComponent);
}


// Method
// ======
//
// Visibility : private
//
// Invoked by : computeComponent
//
// Invokes    :

long double
EulersFormula::raiseBaseToPower
(
 long double   base,
 int           power
)
{
	if (power == 0)
	{
		return(1);
	}
	else
	{
		return(base * this->raiseBaseToPower(base, power - 1));
	}
}


// Method
// ======
//
// Visibility : private
//
// Invoked by :
//
// Invokes    :

long double
EulersFormula::getReal
(
)
{
	return(this->realSum);
}


// Method
// ======
//
// Visibility : private
//
// Invoked by :
//
// Invokes    :

long double
EulersFormula::getImag
(
)
{
	return(this->imagSum);
}

