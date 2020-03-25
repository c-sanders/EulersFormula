#ifndef EULERSFORMULA_HPP
#define EULERSFORMULA_HPP

#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <stdexcept>


using std::cout;
using std::endl;
using std::string;
using std::runtime_error;


/**
 * @brief   The EulersFormula class provides an implementation of Eulers Formula.
 * 
 * @details It makes use of the C++ STL list Class for its computations, storing all of the real components in one STL list, and all
 *          of the imaginary components in another.
 */

class
EulersFormula
{
	public :

		static
		bool           errorStatus;

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

		void
		setNumComponents
		(
		 int   numComponents
		);

		void
		setAngleRadians
		(
		 long double   angleRadians
		);

		std::pair<long double, long double>
		compute
		(
		);

		std::pair<long double, long double>
		getResult
		(
		);
		
		std::pair<std::list<long double>, std::list<long double> >
		getResultComponents
		(
		);


	private :

		static
		void
		errorHandlerGSL
		(
		 const
		 char * reason_p,
		 const
		 char * file_p,
		 int    lineNumber,
		 int    errnoGSL
		)
		/*
		throw
		(
		 // runtime_error
		 const
		 string
		)*/;

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
		)
		noexcept
		(
		 false
		);

		long double
		getReal
		(
		);

		long double
		getImag
		(
		);

		std::list<long double>
		getRealComponents
		(
		);

		std::list<long double>
		getImagComponents
		(
		);

		long double
		raiseBaseToPower
		(
		 long double   base,
		 int           power
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
