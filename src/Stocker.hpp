#ifndef __STOCKER_HPP__
#define __STOCKER_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "Lot.hpp"
// standard libraries
#include <list>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! stocker class
    class CStocker
    {
    public:
		typedef std::list<CLot> LotContainer;
		//! default constructor
        CStocker();
		//! destructor
        ~CStocker();

		//! unload a lot
        const CLot unload(const CLot& lot);
		//! load a lot
        void load(const CLot& lot);

    protected:

    private:
        LotContainer Lots_;		///< container of lots

    };

}

#endif //__STOCKER_HPP__
