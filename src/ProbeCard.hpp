#ifndef __PROBECARD_HPP__
#define __PROBECARD_HPP__

#include "Types.hpp"
#include <string>


//! the namespace of simulation for semiconductor EDS process
namespace SIMSEMI {
    //! Probe Card
    class CProbeCard
    {
    public:
        //! default constructor
        CProbeCard();
        //! destructor
        virtual ~CProbeCard();
        //! set Product Information
        void setProductInfo( const ProdInfoType& info );
        //! get Product Information
        const ProdInfoType getProductInfo() const { return ProdInfo_; }

    protected:


    private:
         ProdInfoType ProdInfo_;

    };
}
#endif //__PROBECARD_HPP__
