#ifndef __MACHINE_HPP__
#define __MACHINE_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "Utility.hpp"
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
    class CMachine : public CThread
    {
    public:
		// public type define

        //! default constructor
        CMachine();
		//! overloading constructor
		CMachine(const MachineAttributeType& ma, const CProbeCard& pc);
        //! destructor
        ~CMachine();
        //! Set attribute of the machine
		/*!
			\param ma Machine attribute
			\param pc probe card
		*/
        void SetMachineAttribute( const MachineAttributeType& ma );
        //! load a Probe card
		/*!
			\param ma Machine attribute
			\param pc probe card
		*/
        void SetProbeCard( const CProbeCard& pc );
		//! operate a Lot
		/*!
			\param lot TKIN a lot
			\return TKOUT the lot
		*/
		CLot& OperateLot(CLot& lot);

        //! Get utilization of the machine
		/*!
			\return Summary of utilization of machine
		*/
        const double GetSummaryUtilizationMachine();

		//! Get to be Set product information
		const ProcessInfoType GetToBeSetProdInfo() const { return ProbeCard_.GetProdInfo(); }
		//! Get probe card
        const CProbeCard& GetProbeCard() const { return ProbeCard_; }
		//! Get atturibute of machine
        const MachineAttributeType GetMachineAttribute() const { return MachineAttribute_; }
        //! Get machine state
        enumMachineState GetMachineState() const { return MachineState_; }

    protected:


    private:
		//! initialize
        void Init();
		//! Destroy
        void Destroy();
		//! thread worker
		void thread();

		bool bStartupMachine_;
		bool bInstalledProbeCard_;

		enumMachineState MachineState_;	///< Machine Status
		MachineAttributeType MachineAttribute_; ///< Machine Attribute
        CProbeCard ProbeCard_;		///< probe card type information
	};
}
#endif //__MACHINE_HPP__
