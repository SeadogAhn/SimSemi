#ifndef __MACHINE_HPP__
#define __MACHINE_HPP__

#include <string>
#include "ProbeCard.hpp"

//! the namespace of simulation for semiconductor EDS process
namespace SIMSEMI {

    enum enumMachineStat {
        eNOT_INIT           ///< not installed any probecard
        , eINITIALIZING     ///< initializing machine, install probe card and setup test program and so on
        , eIDLE             ///< idle
        , eRUNNING          ///< running a Lot
        , eDOWN             ///< crash machine or emergency alert
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
        void setProbeCard(const CProbeCard& pc) { cProbeCard_ = pc; }
        //! set rate of Operation
        void setOperationRate(double er) { dblOperationRate_ = er; }
        //! set Name of Machine
        void setMachineName(const std::string& strMachineName) { strMachineName_ = strMachineName; }


        //! setProbeCard
        const CProbeCard getProbeCard() const { return cProbeCard_; }
        //! set rate of Operation
        const double getOperationRate() const { return dblOperationRate_; }
        //! set Name of Machine
        const std::string getMachineName() const { return strMachineName_; }

        //! get machine status
        /*!
            \return Enumeration of Machine status
         */
        enumMachineStat getMachineStatus();

    protected:


    private:

        void init();
        void destroy();

        CProbeCard cProbeCard_;         ///< probe card type information
        double dblOperationRate_;       ///< rate of operation, normally 90%
        std::string strMachineName_;    ///< name of machine

    };

}
#endif //__MACHINE_HPP__
