#include "ManufacturingOperation.hpp"

using namespace std;

SIMSEMI::CManufacturingOperation::CManufacturingOperation()
{
}

SIMSEMI::CManufacturingOperation::~CManufacturingOperation()
{
}

void SIMSEMI::CManufacturingOperation::setProducts( int n )
{
	ProductGenerator_.setSizeOfProducts(n);
}

