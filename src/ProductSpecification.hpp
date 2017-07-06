#ifndef __PRODUCT_SPECIFICATION_HPP__
#define __PRODUCT_SPECIFICATION_HPP__

// SIMSEMI headers
#include "Types.hpp"
// standard libraries
#include <map>


//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Product Specification class
    class CProductSpecification
    {
    public:
		//! key : partid, value product attribute
		typedef std::map<int, ProductAttributeType> ProductAttributeContainer;
		//! default constructor
        CProductSpecification();
		//! destructor
        virtual ~CProductSpecification();
		//! set specification
		/*!
			\param pa ProductAttributeType
		*/
		virtual void InitProductSpecification(const std::string& strFileName);
		//! get specification
		/*!
			\param nPart partid
			\return if there is nPart in ProductAttributes_ then return ProductAttribute otherwise null
		*/
		virtual const ProductAttributeType* GetProductAttribute(int nPart);
    protected:
		//! add specification
		/*!
			\param pa Product Attribute
		*/
		void AddProductAttribute(const ProductAttributeType& pa);
		//! set specification
		/*!
			\param nPart part id
		*/
		void RemoveProductAttribute(const int& nPart);
	private:
		ProductAttributeContainer ProductAttributes_;	///< product attribute container
	};
}

#endif //__PRODUCT_SPECIFICATION_HPP__
