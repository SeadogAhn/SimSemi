#ifndef __MANIFACTURE_HPP__
#define __MANIFACTURE_HPP__

// SIMSEMI headers
#include "Types.hpp"
// standard libraries
#include <vector>
#include <utility>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Semiconductor Manufactory
    class CManufactory
    {
    public:
		// defined type
		typedef std::vector<std::pair<CMachine, enumMachineStatus> > MachineContainer;

        //! default constructor
        CManufactory();
        //! destructor
        virtual ~CManufactory();

    protected:
		

    private:
          MachineContainer Machines_;

    };
}
#endif //__MANIFACTURE_HPP__
