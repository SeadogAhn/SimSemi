#ifndef __LOT_HPP__
#define __LOT_HPP__

// SIMSEMI headers
#include "Types.hpp"
// standard libraries
#include <vector>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! LOT class
    class CLot
    {
    public:
		//! container of yields of wafers
		typedef Vec_DBL WaferContainer;
        //! default constructor
        CLot();
		//! overloading constructor
		/*! construct and initialize a object by SProductAttributeType
			\param nLot Lot id
			\param nWaferCnt count of wafers
		*/
		CLot(int nLot, int nWaferCnt);
        //! destructor
        virtual ~CLot();
		//! operator==
		bool operator==(const CLot& lot) { return nLot_ == lot.nLot_; }
		//! scrap a wafer
		/*!
			\param dblYieldLimit
		*/
		int ScrapWafer( double dblYieldLimit );
		//! empty
		/*!
			\return is there no wafer in wafer container
		*/
		bool Empty() const { return Wafers_.empty(); }
		// Get members directly
		//! Get lotid
		int GetLotID() const { return nLot_; }
		//! Get wafer container
		/*!
			\return wafer container reference for setting yield by machines
		*/
		WaferContainer& GetWafers() { return Wafers_; }
		//! Get wafer container
		/*!
			\return const wafer container reference for analyzing wafer yield
		*/
		const WaferContainer& GetWafers() const { return Wafers_; }
		//! Get wafer count in a LOT
		/*!
			\return size of the Wafers_
		*/
        size_t GetWaferCount() const { return Wafers_.size(); }

    protected:

    private:
		int nLot_;				///< Lot ID
		WaferContainer Wafers_;	///< wafer container, max 25
    };
}

#endif // __LOT_HPP__
