#include "Machine.hpp"

using namespace std;
using namespace SIMSEMI;


SIMSEMI::CMachine::CMachine()
{
    init();
}

SIMSEMI::CMachine::~CMachine()
{
    destroy();
}

void SIMSEMI::CMachine::init()
{
	bStartupMachine_ = false;
	bInstalledProbeCard_ = false;
}

void SIMSEMI::CMachine::destroy()
{
	MachineState_ = eNOT_INIT;
	MachineAttribute_.clear();
	bStartupMachine_ = false;
	bInstalledProbeCard_ = false;
}

void SIMSEMI::CMachine::setMachineAttribute( const MachineAttributeType& ma )
{
	MachineState_ = eNOT_INIT;
	MachineAttribute_ = ma;
	bStartupMachine_ = true;
}


void SIMSEMI::CMachine::setProbeCard( const CProbeCard& pc )
{
	if (bStartupMachine_)
	{
		ProbeCard_ = pc;
		bInstalledProbeCard_ = true;
	}
}

CLot& SIMSEMI::CMachine::operateLot(CLot& lot)
{
	MachineState_ = eRUN;
	


	MachineState_ = eIDLE;
	return lot;
}

const double SIMSEMI::CMachine::getSummaryUtilizationMachine()
{
	return 0.;
}
