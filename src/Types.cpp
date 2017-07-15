#include "Types.hpp"

#include <sstream>

void SIMSEMI::ProductAttributeType::Clear()
{
	ProcTimes.clear();
	nPart = nStepCnt = -1;
	dblProdYieldMean = dblProdYieldStdDev = dblPrice = 0.;
}

void SIMSEMI::MachineAttributeType::Clear()
{
	nMachine = -1;
	dblLevel = dblLimitRateOperation = 0.;
}

void SIMSEMI::MachineLogType::Clear()
{
	nPart = nLot = nWaferNo = nStep = nMachine = -1;
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
