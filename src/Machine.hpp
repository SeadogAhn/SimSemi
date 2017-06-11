#ifndef __MACHINE_HPP__
#define __MACHINE_HPP__

// SIMSEMI headers
#include "Lot.hpp"
#include "ProbeCard.hpp"
// standard libraries
#include <string>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {

	//! State of a Machine
    enum enumMachineState {
        eNOT_INIT	///< not installed any probecard
        , eIDLE		///< initializing machine, install probe card and setup test program and so on
        , eRUN		///< running a Lot
        , eDOWN		///< crash machine or emergency alert or pm or bm
    };

    //! Set of Tester and Prober
    class CMachine
    {
    public:
		// public type define

        //! default constructor
        CMachine();
        //! destructor
        virtual ~CMachine();

        //! initMachine
		/*!
			\param ma Machine attribute
			\param pc probe card
		*/
        void initMachine(const MachineAttributeType& ma, const CProbeCard& pc);
		//! proceed a Lot
		/*!
			\param lot TKIN a lot
			\return TKOUT the lot
		*/
		CLot& proceedLot(CLot& lot);

        //! get rate of Operation
		/*!
			\return Summary of utilization of machine
		*/
        const double getSummaryUtilizationMachine();
        //! setProbeCard
		/*!
			
		*/
        const CProbeCard& getProbeCard() const { return *pProbeCard_; }
		//! get Name of Machine
        const MachineAttributeType& getMachineAttribute() const { return *pMachineAttribute_; }

        //! get machine status
        /*!
            \return Enumeration of Machine state
         */
        enumMachineState getMachineState() const { return MachineState_; }

    protected:


    private:
		//! initialize
        void init();
		//! destroy
        void destroy();

		MachineAttributeType* pMachineAttribute_; ///< Machine Attribute
		enumMachineState MachineState_;	///< Machine Status
        CProbeCard* pProbeCard_;		///< probe card type information
	};
}
#endif //__MACHINE_HPP__
