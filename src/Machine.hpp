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
        eNOT_INIT	///< not start up machines
		, eEMPTY_PROBECARD	///< there is no to be installed a probe card
        , eIDLE		///< standby ~ initialized machine, to be installed a probe card and to be installed test program and so on
        , eRUN		///< be running a Lot
        , eDOWN		///< crash machine or emergency alert or pm or bm
    };

    //! Set of Tester and Prober
    class CMachine
    {
    public:
		// public type define

        //! default constructor
        CMachine();
		//! overloading constructor
		CMachine(const MachineAttributeType& ma, const CProbeCard& pc);
        //! destructor
        ~CMachine();
        //! set attribute of the machine
		/*!
			\param ma Machine attribute
			\param pc probe card
		*/
        void setMachineAttribute( const MachineAttributeType& ma );
        //! load a Probe card
		/*!
			\param ma Machine attribute
			\param pc probe card
		*/
        void setProbeCard( const CProbeCard& pc );
		//! operate a Lot
		/*!
			\param lot TKIN a lot
			\return TKOUT the lot
		*/
		CLot& operateLot(CLot& lot);

        //! get utilization of the machine
		/*!
			\return Summary of utilization of machine
		*/
        const double getSummaryUtilizationMachine();

		//! get to be set product information
		const ProcessInfoType getToBeSetProdInfo() const { return ProbeCard_.getProdInfo(); }
		//! get probe card
        const CProbeCard& getProbeCard() const { return ProbeCard_; }
		//! get atturibute of machine
        const MachineAttributeType getMachineAttribute() const { return MachineAttribute_; }
        //! get machine state
        enumMachineState getMachineState() const { return MachineState_; }

    protected:


    private:
		//! initialize
        void init();
		//! destroy
        void destroy();

		bool bStartupMachine_;
		bool bInstalledProbeCard_;

		enumMachineState MachineState_;	///< Machine Status
		MachineAttributeType MachineAttribute_; ///< Machine Attribute
        CProbeCard ProbeCard_;		///< probe card type information
	};
}
#endif //__MACHINE_HPP__
