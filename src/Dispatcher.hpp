#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

// SIMSEMI headers
#include "Lot.hpp"
#include "Machine.hpp"
#include "Stocker.hpp"

// standard libraries

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! lot dispatcher
    class CDispatcher
    {
    public:
        //! default constructor
        CDispatcher();
        //! destructor
        ~CDispatcher();

		int MoveLotFromStockerToMachine( CLot& l, CStocker& s, CMachine& m );
		int MoveLotFromMachineToStocker( CLot& l, CMachine& m, CStocker& s );


    protected:

    private:

    };
}

#endif // __DISPATCHER_HPP__
