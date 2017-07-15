#ifndef __PROBECARD_HPP__
#define __PROBECARD_HPP__

// SIMSEMI headers
#include "Types.hpp"
// standard libraries
#include <string>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Probe Card
    class CProbeCard
    {
    public:
        //! default constructor
        CProbeCard();
		//! copy constructor
		CProbeCard( const CProbeCard& rhs ) { ProbCardInfo_ = rhs.ProbCardInfo_; }
        //! destructor
        virtual ~CProbeCard();
        //! Set Product Information
        void SetProductInfo( const ProbeCardInfoType& ProbCardInfo );
        //! Get Product Information
        const ProbeCardInfoType GetProdInfo() const { return ProbCardInfo_; }

    protected:


    private:
         ProbeCardInfoType ProbCardInfo_;

    };
}
#endif //__PROBECARD_HPP__
