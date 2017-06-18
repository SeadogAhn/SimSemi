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

		//! operator==
		bool operator==(const CLot& lot) { return lot.strLotID_ == strLotID_; }

		// set members
        //! set product attribute
		/*!
			\param prodattr Attribute of the Product
		*/
		void setProductAttribute(const ProductAttributeType& prodattr);
		//! set wafers' yield by a tester(a machine)
        void setWaferYield( int nWaferNo, double dblYield );
		//! scrap a wafer
		/*!
			\param dblYieldLimit
		*/
		int scrapWafer( double dblYieldLimit );
		//! empty
		/*!
			\return is there no wafer in wafer container
		*/
		bool empty() const { return Wafers_.empty(); }

		// get members directly
		//! get product attribute
		const ProductAttributeType& getProductAttribute() const { return ProductAttribute_; }
		//! get lotid
		const std::string& getLotID() const { return strLotID_; }
		//! get wafer container
		const WaferContainer& getWafers() const { return Wafers_; }
		//! get wafer count in a LOT
        size_t getWaferCount() const { return Wafers_.size(); }
		//! get priority
		int getPriority() const { return nPriority_; }

    protected:

    private:
		//! create and initialize wafers in a lot
		void init();
		//! destroy a lot
		void destroy();

		ProductAttributeType ProductAttribute_; ///< Product Attribute
		std::string strLotID_;		///< Lot ID
		WaferContainer Wafers_;		///< wafer container, max 25
        int nPriority_;				///< Lot priority
    };
}

#endif // __LOT_HPP__
