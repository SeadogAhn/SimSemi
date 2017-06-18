#ifndef __TYPES_HPP__
#define __TYPES_HPP__

// SIMSEMI headers
#include "Define.hpp"
// standard libraries
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <ostream>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! vector types
    typedef std::vector<std::string> Vec_STR;
    //! type of product information, first is a partid, second is a sortflag(is same stepid)
    typedef std::pair<std::string, std::string> ProcessInfoType, ProbeCardInfoType;

	//! Attribute of Products
	struct ProductAttributeType
	{
		typedef std::vector<double> TestTimeContainer;
		//! clear all members
		void clear();

		std::string strPartID;			///< Product ID
		TestTimeContainer TestTimes;	///< Test time of each test step
		int nSteps;						///< process step count
		double dblProdYieldMean;		///< average of yield of a product
		double dblProdYieldStdDev;		///< standard deviation of yield of a product
		double dblPrice;				///< price per wafer
	};

	//! Attribute of Machines
	struct MachineAttributeType
	{
		//! clear all members
		void clear();
		std::string strEqpID;			///< equipment ID
		std::string strModel;			///< equipment type, kind of maker
		double dblLevel;				///< condition level 0. ~ 1., it is related the machine performance and error
		double dblLimitRateOperation;	///< maximum operation rate 0. ~ 1.
	};

	struct MachineLogType
	{
		//! clear all members
		void clear();
		//! to string
		const std::string toString();

		std::string strPartID;
		std::string strLotID;
		int nWaferNo;
		int nStep;
		double dblElapsedTime;
	};

	//! a type of element of chromosomes for optimizing fjsp scheduling
	struct OperationType
	{
		size_t nJob;
		size_t nOperation;
		size_t nMachine;
	};
}

#endif // __TYPES_HPP__
