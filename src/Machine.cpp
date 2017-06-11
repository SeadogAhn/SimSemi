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
	destroy();
	pMachineAttribute_ = NULL;
	pProbeCard_ = NULL;
}

void SIMSEMI::CMachine::destroy()
{
	MachineState_ = eNOT_INIT;
	if (pMachineAttribute_) delete pMachineAttribute_;
	if (pProbeCard_) delete pProbeCard_;
}

void SIMSEMI::CMachine::initMachine(const MachineAttributeType& ma, const CProbeCard& pc)
{
	init();
	pMachineAttribute_ = new MachineAttributeType(ma);
	pProbeCard_ = new CProbeCard(pc);
	MachineState_ = eIDLE;
}

CLot& SIMSEMI::CMachine::proceedLot(CLot& lot)
{
	MachineState_ = eRUN;
	
	MachineState_ = eIDLE;
	return lot;
}

const double SIMSEMI::CMachine::getSummaryUtilizationMachine()
{
	return 0.;
}
