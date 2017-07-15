#include "Stocker.hpp"

#include <algorithm>

using namespace std;

SIMSEMI::CStocker::CStocker()
{
}

SIMSEMI::CStocker::~CStocker()
{
}

const SIMSEMI::CLot SIMSEMI::CStocker::Unload(const CLot& lot)
{
	LotContainer::iterator itor = find(Lots_.begin(), Lots_.end(), lot);

	// there is no the same lot in the container
	if ( itor == Lots_.end() )
	{
		return CLot();
	}
	else {
		// return a Lot before erase the Lot in the container
		CLot l = *itor;
		Lots_.erase(itor);
		return l;
	}
}

void SIMSEMI::CStocker::Load(const CLot& lot)
{
	Lots_.push_back(lot);
}
