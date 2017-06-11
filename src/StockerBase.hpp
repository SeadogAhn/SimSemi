#ifndef __STOCKER_H__
#define __STOCKER_H__

// SIMSEMI headers
#include "Lot.hpp"
// standard libraries
#include <queue>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! stocker base class
    class CStockerBase
    {
    public:
		typedef std::map<std::string, CLot> LotContainer;
        CStockerBase();
        virtual ~CStockerBase();

        const CLot pop() const { return Lots_.pop(); }
        void push(const CLot& lot) { Lots_.push(lot); }

    protected:

    private:
        LotContainer Lots_;

    };

}

#endif //__STOCKER_H__
