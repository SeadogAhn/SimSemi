#include "Types.hpp"

#include <sstream>

void SIMSEMI::ProductAttributeType::clear()
{
	strPartID.clear();
	TestTimes.clear();
	nSteps = 0;
	dblProdYieldMean = 0.;
	dblProdYieldStdDev = 0.;
	dblPrice = 0.;
}

void SIMSEMI::MachineAttributeType::clear()
{
	strEqpID.clear();
	strModel.clear();
	dblLevel = 0.;
	dblLimitRateOperation = 0.;
}

void SIMSEMI::MachineLogType::clear()
{
	strPartID.clear();
	strLotID.clear();
	nWaferNo = 0;
	nStep = 0;
	dblElapsedTime = 0.;
}

const std::string SIMSEMI::MachineLogType::ToString()
{
	std::ostringstream oss;

	oss << strPartID
		<< ',' << nStep
		<< ',' << strLotID
		<< ',' << nWaferNo
		<< ',' << dblElapsedTime
		;

	return oss.str();
}
