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
		//!	Get constainer of the lots
		const LotContainer& GetLots() const { return Lots_; }
		//! unload a lot
        const CLot Unload(const CLot& lot);
		//! load a lot
        void Load(const CLot& lot);

    protected:

    private:
        LotContainer Lots_;	///< container of lots
    };
}

#endif //__STOCKER_HPP__
