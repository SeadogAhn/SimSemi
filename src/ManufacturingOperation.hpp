#ifndef __MANIFACTURING_OPERATION_HPP__
#define __MANIFACTURING_OPERATION_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "ProductGenerator.hpp"
#include "Scheduler.hpp"
#include "Dispatcher.hpp"
#include "Manufactory.hpp"

// standard libraries
#include <vector>
#include <utility>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Manufacturing Operation System (MOS)
    class CManufacturingOperation
    {
    public:
        //! default constructor
        CManufacturingOperation();
        //! destructor
        ~CManufacturingOperation();
		//! generate products
		/*!
			\param strProductSpecFileName product specification file name
			\param strMasterPlanFileName product master plan file name
		*/
		void GenerateProducts(const std::string& strProductSpecFileName, const std::string& strMasterPlanFileName);
		//! get products
		/*!
			return generated product from CProductGenerator object
		*/
		const CProductGenerator::ProductContainer& GetProducts() const;

    protected:

    private:
		CProductGenerator ProductGenerator_;
		CScheduler Scheduler_;
		CDispatcher Dispatcher_;
		CManufactory Manufactory_;

    };
}
#endif //__MANIFACTURING_OPERATION_HPP__
