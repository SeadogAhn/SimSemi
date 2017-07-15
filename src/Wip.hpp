#ifndef __WIP_HPP__
#define __WIP_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "Lot.hpp"
// standard libraries
#include <list>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! stocker class
    class CWip
    {
    public:
		//! default constructor
        CWip();
		//! destructor
        ~CWip();
		//! initialize lot list

		//! Update Lot Status
        void UpdateLotStatus(int nPart, const CLot& lot);

    protected:

    private:

    };
}

#endif //__WIP_HPP__
