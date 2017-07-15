#include "ManufacturingOperation.hpp"

using namespace std;

SIMSEMI::CManufacturingOperation::CManufacturingOperation()
{
}

SIMSEMI::CManufacturingOperation::~CManufacturingOperation()
{
}

void SIMSEMI::CManufacturingOperation::GenerateProducts(const std::string& strProductSpecFileName, const std::string& strMasterPlanFileName)
{
	ProductGenerator_.InitProductSpecification(strProductSpecFileName);
	ProductGenerator_.InitProductMasterPlan(strMasterPlanFileName);
}

const SIMSEMI::CProductGenerator::ProductContainer& SIMSEMI::CManufacturingOperation::GetProducts() const
{
	return ProductGenerator_.GetProducts();
}
