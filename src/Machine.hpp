#ifndef __MACHINE_HPP__
#define __MACHINE_HPP__

// SIMSEMI headers
#include "ProbeCard.hpp"
// standard library
#include <string>

// SIMSEMI headers

// standard libraries



//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {

    enum enumMachineStatus {
        eNOT_INIT	///< not installed any probecard
        , eINIT		///< initializing machine, install probe card and setup test program and so on
        , eIDLE		///< idle
        , eRUN		///< running a Lot
		, eEND		///< end process	
        , eDOWN		///< crash machine or emergency alert or pm or bm
    };

    //! Set of Tester and Prober
    class CMachine
    {
    public:
        //! default constructor
        CMachine();
        //! destructor
        virtual ~CMachine();

        //! setProbeCard
		/*!
			\param pc probe card
		*/
        void setProbeCard(const CProbeCard& pc) { cProbeCard_ = pc; }
        //! set rate of Operation
		/*!
			\param 
		*/
        void setMachineAttribute(double er) { dblOperationRate_ = er; }
        //! set Name of Machine
        void setMachineName(const std::string& strMachineName) { strMachineName_ = strMachineName; }

        //! setProbeCard
        const CProbeCard getProbeCard() const { return cProbeCard_; }
        //! get rate of Operation
        const double getSummaryUtilization() const { return dblOperationRate_; }
        //! get Name of Machine
        const std::string getMachineName() const { return strMachineName_; }
		//! 
		//! test a Lot
		/*!
			\param lot test a lot
		*/
		CLot& testLot(CLot& lot);

		//! set defualt test time
        /*!
            \param m default test time, unit is minute
         */
        void setDefTestTime( int m ) { nTestTime_ = m; }
        //! get TestTime
        /*!
            \return defualt test time * yield
         */
        double getTestTime() { return static_cast<double>(nTestTime_) * dblYield; }


        //! get machine status
        /*!
            \return Enumeration of Machine status
         */
        enumMachineStatus getMachineStatus();

    protected:


    private:
		//! initialize
        void init();
		//! destroy
        void destroy();

        CProbeCard cProbeCard_;         ///< probe card type information    
        std::string strMachineName_;    ///< name of machine
		std::vector<MachineLogType> Log_;	///< logger
    };
}
#endif //__MACHINE_HPP__
