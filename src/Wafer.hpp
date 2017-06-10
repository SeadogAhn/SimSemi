#ifndef __WAFER_HPP__
#define __WAFER_HPP__

#include <string>

//! the namespace of simulation for semiconductor EDS process
namespace SIMSEMI {
    //! Wafer Class is include lot and wafer information
    class CWafer
    {
    public:
        //! default constructor
        CWafer();
        //! destructor
        ~CWafer();
        //! initialize all member variables
        void init();
        //! set defualt test time
        /*!
            \param m default test time, unit is minute
         */
        void setDefTestTime( int m ) { nTestTime_ = m; }
        //! get TestTime
        /*!
            \return defualt test time * yield
         */
        double getTestTime() const { return static_cast<double>(nTestTime_) * dblYield; }

        std::string strLotID;   ///< LOT ID
        int nWaferNo;           ///< Wafer Number
        int nNetDie;            ///< netdie
        int nTestDie;           ///< testdie
        double dblYield;        ///< yield of wafer

    protected:

    private:
        int nTestTime_;          ///< unit is minute
    };

}
#endif // __WAFER_HPP__
