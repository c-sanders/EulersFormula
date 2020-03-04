#include <EulersFormula.hpp>

#include <numeric>

#include <gsl/gsl_sf_gamma.h>
// factorial function

// 0.764842187284488426 + j0.644217687237691054
// 0.764842187284488426 + j0.644217687237691054


EulersFormula::EulersFormula
(
 int           numComponents,
 long double   angleRadians
)
:
numComponents(numComponents),
angleRadians(angleRadians)
{
	const
	string   nameMethod = "EulersFormula Ctor : ";


	cout << nameMethod << "Enter" << endl;

	this->counter = 0;
	this->realSum = 0;
	this->imagSum = 0;

	cout << nameMethod << "Exit" << endl;
}


EulersFormula::~EulersFormula
(
)
{
	cout << "Euler Dtor" << endl;
}


std::pair<long double, long double>
EulersFormula::compute
(
)
{
	this->computeComponents();
	this->sumComponents();

	std::pair<long double, long double>complexResult(this->realSum, this->imagSum);

	return(complexResult);
}


void
EulersFormula::computeComponents
(
)
{
	const
	string   nameMethod = "EulersFormula::computeComponents : ";

	int      multiplier = 1;


	cout << nameMethod << "Enter" << endl;

	while
	(
	 this->counter <= this->numComponents
	)
	{
		long double   currentComponent;


		// Real component

		currentComponent = multiplier * (this->computeComponent(this->angleRadians, this->counter));

		++(this->counter);

		// realSum += (multiplier * currentComponent);

		this->realComponents.push_back(currentComponent);

		cout << "Component = " << (this->counter - 1) << endl;

		// Imaginary component

		if (this->counter <= this->numComponents)
		{
			currentComponent = multiplier * (this->computeComponent(this->angleRadians, this->counter));

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


long double
EulersFormula::computeComponent
(
 long double   angleRadians,
 int           numberComponent
)
{
	long double   currentComponent = 0;


	currentComponent = this->raiseBaseToPower(angleRadians, numberComponent) / gsl_sf_fact(numberComponent);

	return(currentComponent);
}


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


long double
EulersFormula::getReal
(
)
{
	return(this->realSum);
}


long double
EulersFormula::getImag
(
)
{
	return(this->imagSum);
}

