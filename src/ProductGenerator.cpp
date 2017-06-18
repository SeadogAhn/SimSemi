#include "ProductGenerator.hpp"

#include <Rcpp.h>

using namespace std;
using namespace Rcpp;

SIMSEMI::CProductGenerator::CProductGenerator()
{
}

SIMSEMI::CProductGenerator::~CProductGenerator()
{
	Products_.clear();
}

SIMSEMI::CProductGenerator::CProductGenerator( int n )
{
	setSizeOfProducts( n );
}

void SIMSEMI::CProductGenerator::setSizeOfProducts( int n )
{
	Products_.clear();
	for ( int i = 0 ; i < n ; i++ )
	{
		Products_.push_back( makeProductAttribute(i) );
	}
}

const SIMSEMI::ProductAttributeType SIMSEMI::CProductGenerator::makeProductAttribute( int i )
{
	ProductAttributeType pa;

	char buffer[20] = { 0, };
	sprintf(buffer, "PART%03d", i);
	pa.strPartID = buffer;
	pa.nSteps = genStepSize();

	pa.TestTimes = genTestTime( pa.nSteps );

	pa.dblProdYieldMean = 0.;
	pa.dblProdYieldStdDev = 0.;
	pa.dblPrice = 0;

	return pa;
}

int SIMSEMI::CProductGenerator::genStepSize()
{
	double r = R::runif(0,1);

	/*
		STEP 1 : 20%, STEP 2 : 75%, STEP 3 : 5%
		hence if r is 1 smaller than 0.2
		and if r is 3 greater than 0.95
		otherwise 2
	*/

	if ( r < SIMSEMI_D_STEP_1_RATE ) {
		return 1;
	}
	else if ( r > SIMSEMI_D_STEP_1_RATE + SIMSEMI_D_STEP_2_RATE ) {
		return 3;
	}
	else {
		return 2;
	}
}

const SIMSEMI::ProductAttributeType::TestTimeContainer SIMSEMI::CProductGenerator::genTestTime( int n )
{
	ProductAttributeType::TestTimeContainer ts(n);

	for (int i = 0 ; i < n ; i++ ) {
		ts[i] = R::runif(SIMSEMI_D_TEST_TIME_MIN, SIMSEMI_D_TEST_TIME_MAX);
	}

	return ts;
}
