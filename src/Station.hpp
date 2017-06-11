#ifndef __STATION_H__
#define __STATION_H__

// SIMSEMI headers
#include "Lot.hpp"
// standard libraries
#include <queue>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! stocker base class
    class CStation
    {
    public:
		typedef std::queue<CLot> LotContainer;
        CStation();
        virtual ~CStation();

        const CLot& pop() const { return Lots_.pop(); }
        void push(const CLot& lot) { Lots_.push(lot); }

    protected:

    private:
        LotContainer Lots_;

    };

}

#endif //__STATION_H__
