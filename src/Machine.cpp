#include "Machine.hpp"

using namespace std;


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
    strMachineName_ = "1";
    dblOperationRate_ = 90;
}

void SIMSEMI::CMachine::destroy()
{
    strMachineName_.clear();
    dblOperationRate_ = 0;
}

SIMSEMI::enumMachineStat SIMSEMI::CMachine::getMachineStatus()
{
    return eNOT_INIT;
}
