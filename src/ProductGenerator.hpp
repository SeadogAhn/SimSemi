#ifndef __PRODUCT_GENERATOR_HPP__
#define __PRODUCT_GENERATOR_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "Lot.hpp"
#include "ProductSpecification.hpp"

// standard libraries


//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Product Generator
    class CProductGenerator : public CProductSpecification
    {
    public:
		typedef std::vector< CLot > LotContainer;
		// key : partid, value : lot
		typedef std::map< int, LotContainer > ProductContainer;
		//! ;default constructor
    	CProductGenerator();
		//! destructor
    	~CProductGenerator();
		//! initialize Master Plan
		/*!
			\param strFileName a file name of master plan
		*/
		void InitProductMasterPlan(const std::string& strFileName);
		//! Get the container of the products
		/*!
			\param Product Container
		*/
		const ProductContainer& GetProducts() const { return Products_; }

    private:
		//! make Lots
		LotContainer MakeLots(int nQuantity);

		ProductContainer Products_;	///< container of lots
    };
}

#endif // __PRODUCT_GENERATOR_HPP__
