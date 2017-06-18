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
		//! set product count
		void setProducts( int n );

    protected:
		

    private:
		CProductGenerator ProductGenerator_;
		CScheduler Scheduler_;
		CDispatcher Dispatcher_;
		CManufactory Manufactory_;

    };
}
#endif //__MANIFACTURING_OPERATION_HPP__
