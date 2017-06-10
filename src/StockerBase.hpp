#ifndef __STOCKER_H__
#define __STOCKER_H__

#include <queue>
#include "Lot.hpp"


//! the namespace of simulation for semiconductor EDS process
namespace SIMSEMI {
    //! stocker base class
    class CStockerBase
    {
    public:
        CStockerBase();
        virtual ~CStockerBase();

        const CLot pop() const { return queueLot_.pop(); }
        void push(const CLot& lot) { queueLot_.push(lot); }

    protected:

    private:
        std::priority_queue<CLot> queueLot_;

    };

}

#endif //__STOCKER_H__
