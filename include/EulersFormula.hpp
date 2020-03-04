#ifndef EULERSFORMULA_HPP
#define EULERSFORMULA_HPP

#include <iostream>
#include <string>
#include <list>
#include <utility>


using std::cout;
using std::endl;
using std::string;


class
EulersFormula
{
	public :

		EulersFormula
		(
		 int           numComponents,
		 long double   angleRadians
		);
		
		~EulersFormula
		(
		);

		EulersFormula
		(
		 const
		 EulersFormula & rhs
		);

		EulersFormula &
		operator=
		(
		 const
		 EulersFormula & rhs
		);

		std::pair<long double, long double>
		compute
		(
		);

		void
		computeComponents
		(
		);

		void
		sumComponents
		(
		);

		long double
		computeComponent
		(
		 long double   angleRadians,
		 int           numberComponent
		);

		long double
		raiseBaseToPower
		(
		 long double   base,
		 int           power
		);

		long double
		getReal
		(
		);

		long double
		getImag
		(
		);


	private :

		int                                numComponents,
		                                   counter;

		long double                        angleRadians,
		                                   realSum,
		                                   imagSum;

		std::list<long double>             realComponents,
		                                   imagComponents;
	
		std::list<long double>::iterator   iter;
};

#endif
