#include "Types.hpp"

#include <sstream>

void SIMSEMI::ProductAttributeType::Clear()
{
	ProcTimes.clear();
	nPart = nStepCnt = 0;
	dblProdYieldMean = dblProdYieldStdDev = dblPrice = 0.;
}

void SIMSEMI::MachineAttributeType::Clear()
{
	nMachine = 0;
	dblLevel = dblLimitRateOperation = 0.;
}

void SIMSEMI::MachineLogType::Clear()
{
	nPart = nLot = nWaferNo = nStep = nMachine = 0;
	dblElapsedTime = 0.;
}

const std::string SIMSEMI::MachineLogType::ToString()
{
	std::ostringstream oss;

	oss << nPart
		<< ',' << nLot
		<< ',' << nWaferNo
		<< ',' << nStep
		<< ',' << nMachine
		<< ',' << dblYield
		<< ',' << dblElapsedTime
		;

	return oss.str();
}
