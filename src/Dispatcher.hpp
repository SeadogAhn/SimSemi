#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

// SIMSEMI headers

// standard libraries

#include "Machine.hpp"

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! lot dispatcher
    class CDispatcher
    {
    public:
        //! default constructor
        CDispatcher();
        //! destructor
        virtual ~CDispatcher();
        //! find a idle machine
        CMachine* findIdleMachine();

    protected:

    private:

    };
}

#endif // __DISPATCHER_HPP__
