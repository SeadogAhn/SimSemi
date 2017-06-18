#include "Station.hpp"

SIMSEMI::CStation::CStation()
{
}

SIMSEMI::CStation::~CStation()
{
}

void SIMSEMI::CStation::init()
{
	LotContainer().swap(Lots_);
}

void SIMSEMI::CStation::destroy()
{
	LotContainer().swap(Lots_);
}

const SIMSEMI::CLot SIMSEMI::CStation::pop()
{
	CLot lot;
	if (!Lots_.empty())
	{
		lot = *Lots_.begin();
		Lots_.pop_front();
	}
	return lot;
}

void SIMSEMI::CStation::push(const CLot& lot)
{
	Lots_.push_back(lot);
}
