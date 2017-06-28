#ifndef __PRODUCT_GENERATOR_HPP__
#define __PRODUCT_GENERATOR_HPP__

// SIMSEMI headers
#include "Types.hpp"

// standard libraries
#include <vector>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Product Generator
    class CProductGenerator
    {
    public:
		//! ;default constructor
    	CProductGenerator();
		//! overloading constructor
		/*!
			\param n kind of products
		*/
		explicit CProductGenerator( int n );
		//! destructor
    	~CProductGenerator();
		//! set count of products
		void setSizeOfProducts( int n );
		//! get the container of the products
		const ProductContainer& getProducts() const { return Products_; }

    private:
		//! make a attribute of a product
		const ProductAttributeType makeProductAttribute( int i );
		//! generate a random number between 1 and 3
		int genStepSize();
		//! generate a random number for testing time a wafer
		/*!
			\param n times
			\return container of to be generated test times
		*/
		const ProductAttributeType::TestTimeContainer genTestTime( int n );


		ProductContainer Products_; ///< container of products
    };
}

#endif // __PRODUCT_GENERATOR_HPP__
