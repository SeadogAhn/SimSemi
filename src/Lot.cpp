#include "Lot.hpp"

// r interface header
#include <Rcpp.h>

SIMSEMI::CLot::CLot()
{
}

SIMSEMI::CLot::CLot(int nLot, int nWaferCnt)
{
	nLot_ = nLot;
	if (nWaferCnt > 0) {
		Wafers_.resize(nWaferCnt);
	}
}

SIMSEMI::CLot::~CLot()
{
}

int SIMSEMI::CLot::ScrapWafer(double dblYieldLimit)
{
	int nScrapedWaferCount = 0;
	WaferContainer::iterator itor = Wafers_.begin();
	while (itor != Wafers_.end()) {
		if (*itor < dblYieldLimit) {
			Wafers_.erase(itor);
			nScrapedWaferCount++;
		}
		else {
			++itor;
		}
	}
	return 0;
}
