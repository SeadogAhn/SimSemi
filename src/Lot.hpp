#ifndef __LOT_HPP__
#define __LOT_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "Wafer.hpp"
// standard libraries
#include <vector>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! LOT class
    class CLot
    {
    public:
		typedef std::vector<CWafer> WaferContainer;
        //! default constructor
        CLot();
		//! overloading constructor
		/*! construct and initialize a object by SProductAttributeType
			\param prodattr Attribute of the Product
		*/
		CLot(const ProductAttributeType& prodattr);
        //! destructor
        virtual ~CLot();
        //! set product's attribute
		/*!
			\param prodattr Attribute of the Product
		*/
		void setProductAttribute(const ProductAttributeType& prodattr);
		//! get wafer count in a LOT
        size_t getWaferCount() const { return Wafers_.size(); }
		//! set wafers' yield by a tester(a machine)
        void setWaferYield();
		//! scrap a wafer
		/*!
		*/
		int scrapWafer();
    protected:

    private:
        WaferContainer Wafers_;		///< wafer container, max 25
        int nPriority_;             ///< Lot priority

		//! create and initialize wafers in a lot
		void init();
		//! destroy a lot
		void destroy();
    };
}

#endif // __LOT_HPP__
