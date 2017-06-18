#include "Lot.hpp"

// r interface header
#include <Rcpp.h>

SIMSEMI::CLot::CLot()
{
}

SIMSEMI::CLot::CLot(const ProductAttributeType& prodattr)
{
}

SIMSEMI::CLot::~CLot()
{
}

void SIMSEMI::CLot::init()
{
	ProductAttribute_.clear();
	strLotID_.clear();
	Wafers_.clear();
	nPriority_ = 0;
}

void SIMSEMI::CLot::destroy()
{
}

void SIMSEMI::CLot::setProductAttribute(const ProductAttributeType& prodattr)
{
}

void SIMSEMI::CLot::setWaferYield( int nWaferNo, double dblYield )
{

}

int SIMSEMI::CLot::scrapWafer( double dblYieldLimit )
{
	return 0;
}
