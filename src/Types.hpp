#ifndef __TYPES_HPP__
#define __TYPES_HPP__

// SIMSEMI headers
#include "Define.hpp"
// standard libraries
#include <map>
#include <vector>
#include <utility>
#include <string>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    // vector types
    typedef std::vector<std::string> Vec_STR;

    // type of product information, first is a partid, second is a sortflag(is same stepid)
    typedef std::pair<std::string, std::string> ProdInfoType;

	//! Attribute of Products
	struct SProductAttributeType
	{
		std::string strPartID;		///< Product ID
		std::vector vecTestTime;	///< Test time of each test step
		double dblProdYieldMean;	///< average of yield of a product
		double dblProdYieldStdDev;	///< standard deviation of yield of a product
		//! get Count of the Process Step 
		/*! \return Step Count */
		int getStepCount() const { return vecTestTime.size(); }
	};

	//! Attribute of Machines
	struct MachineAttributeType
	{
		std::string strEqpID;		///< equipment ID
		std::string strModel;		///< equipment type, kind of maker
		double dblLevel;			///< condition level 0. ~ 1., it is related the machine performance and error
		double dblLimitRateOperation;///< maximum operation rate 0. ~ 1.
	};

	struct MachineLogType
	{
		std::string strPartID;
		std::string strLotID;
		int nWaferNo;
		int nStep;
		double dblElapsedTime;
	};

}

#endif // __TYPES_HPP__
