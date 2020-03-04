# ACLOCAL_AMFLAGS(-I m4)


bin_PROGRAMS                       = test_eulers_formula


# Library
# =======

lib_LTLIBRARIES                    = libeulers_formula.la

libeulers_formula_la_SOURCES       = EulersFormula.cpp

libeulers_formula_la_CPPFLAGS      = -I${top_srcdir}/include ${GSL_CFLAGS}


# Binary
# ======
#
# At compile time, the -std=c++11 Compiler option is required in order to use the nullptr keyword.

test_eulers_formula_INCLUDES       = EulersFormula.hpp

test_eulers_formula_SOURCES        = ${test_eulers_formula_INCLUDES} \
                                     testEulersFormula.cpp \
                                     EulersFormula.cpp

test_eulers_formula_CPPFLAGS       = -I${top_srcdir}/include ${GSL_CFLAGS}

test_eulers_formula_CXXFLAGS       = ${BOOST_CPPFLAGS} -std=c++11

test_eulers_formula_LDFLAGS        = ${BOOST_LDFLAGS}

test_eulers_formula_LDADD          = ${GSL_LIBS}


.PHONY: displaySettings
displaySettings:

	@echo "srcdir               = ${srcdir}"
	@echo "abs_srcdir           = ${abs_srcdir}"
	@echo "top_srcdir           = ${top_srcdir}"
	@echo "builddir             = ${builddir}"

