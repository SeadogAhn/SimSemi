#ifndef __MANIFACTURE_HPP__
#define __MANIFACTURE_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "Machine.hpp"
#include "ProbeCard.hpp"
#include "Stocker.hpp"

// standard libraries
#include <vector>
#include <map>
#include <utility>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Semiconductor Manufactory
    class CManufactory
    {
    public:
		// defined type
		typedef std::vector<CMachine> MachineContainer;
		typedef std::vector<CProbeCard> ProbeCardContainer;

        //! default constructor
        CManufactory();
        //! destructor
        virtual ~CManufactory();

    protected:


    private:
		CStocker StockerInput_;		///< stock input lots
		CStocker StockerHold_;		///< sotck held lots
		MachineContainer Machines_;	///< container of machines
		ProbeCardContainer ProbeCards_;	///< container of probecards

    };
}
#endif //__MANIFACTURE_HPP__
