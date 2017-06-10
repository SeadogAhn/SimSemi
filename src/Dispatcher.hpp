#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include "Machine.hpp"

//! the namespace of simulation for semiconductor EDS process
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
