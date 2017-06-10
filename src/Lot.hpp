#ifndef __LOT_HPP__
#define __LOT_HPP__

// standard libries
#include <list>
// r interface header
#include <Rcpp.h>
// defined libraries by user
#include "Wafer.hpp"

//! the namespace of simulation for semiconductor EDS process
namespace SIMSEMI {
    //! LOT class
    class CLot
    {
    public:
        //! default constructor
        CLot();
        //! destructor
        virtual ~CLot();
        //! get wafer count in a LOT
        size_t getWaferCount() const { return listWafer_.size(); }
        //! set wafer yield
        void setWaferYield();

    protected:

    private:
        std::list<CWafer> listWafer_;   ///< wafer container, max 25
        int nPriority_;                 ///< Lot priority

    };
}

#endif // __LOT_HPP__
