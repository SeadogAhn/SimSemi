#include "Machine.hpp"

using namespace std;
using namespace SIMSEMI;


SIMSEMI::CMachine::CMachine()
{
    Init();
}

SIMSEMI::CMachine::~CMachine()
{
    Destroy();
}

void SIMSEMI::CMachine::Init()
{
	bStartupMachine_ = false;
	bInstalledProbeCard_ = false;
}

void SIMSEMI::CMachine::Destroy()
{
	MachineState_ = eNOT_INIT;
	MachineAttribute_.Clear();
	bStartupMachine_ = false;
	bInstalledProbeCard_ = false;
}

void SIMSEMI::CMachine::SetMachineAttribute( const MachineAttributeType& ma )
{
	MachineState_ = eNOT_INIT;
	MachineAttribute_ = ma;
	bStartupMachine_ = true;
}


void SIMSEMI::CMachine::SetProbeCard( const CProbeCard& pc )
{
	if (bStartupMachine_)
	{
		ProbeCard_ = pc;
		bInstalledProbeCard_ = true;
	}
}

CLot& SIMSEMI::CMachine::OperateLot(CLot& lot)
{
	MachineState_ = eRUN;



	MachineState_ = eIDLE;
	return lot;
}

void SIMSEMI::CMachine::thread()
{

}


const double SIMSEMI::CMachine::GetSummaryUtilizationMachine()
{
	return 0.;
}
