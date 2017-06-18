#ifndef __STATION_H__
#define __STATION_H__

// SIMSEMI headers
#include "Lot.hpp"
// standard libraries
#include <deque>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! stocker base class
    class CStation
    {
    public:
		typedef std::deque<CLot> LotContainer;
		//! default constructor
        CStation();
		//! destructor
        ~CStation();
		//! get a Lot and erase the Lot
        const CLot pop();
		//! push a Lot
        void push(const CLot& lot);

    protected:

    private:
		//! initialize
		void init();
		//! destroy
		void destroy();
		
        LotContainer Lots_; ///< conatiner of lots
    };
}

#endif //__STATION_H__
