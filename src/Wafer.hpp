#ifndef __WAFER_HPP__
#define __WAFER_HPP__

// SIMSEMI headers

// standard libraries

#include <string>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Wafer Class is include lot and wafer information
    class CWafer
    {
    public:
        int nWaferNo;           ///< Wafer Number
        int nNetDie;            ///< netdie
        int nTestDie;           ///< testdie
		int nRetestCount;		///< tetested count
        double dblYield;        ///< yield of wafer
    };
}
#endif // __WAFER_HPP__
