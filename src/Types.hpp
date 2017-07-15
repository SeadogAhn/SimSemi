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
#include <sstream>
#include <stdexcept>

#include <Rcpp.h>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! vector types
	typedef std::vector<int>	Vec_INT;
	typedef std::vector<double> Vec_DBL;
    typedef std::vector<std::string> Vec_STR;
	//! type of product information, first is a part, second is a step
    typedef std::pair<int, int> ProcessInfoType, ProbeCardInfoType;

	//! Attribute of Products
	struct ProductAttributeType
	{
		//! clear all members
		void Clear();
		int nPart;					///< Product ID
		int nStepCnt;				///< process step count
		Vec_DBL ProcTimes;			///< process time of each test step
		double dblProdYieldMean;	///< average of yield of a product
		double dblProdYieldStdDev;	///< standard deviation of yield of a product
		double dblPrice;			///< price per wafer
	};

	//! Attribute of Machines
	struct MachineAttributeType
	{
		//! clear all members
		void Clear();
		int nMachine;				///< Mdchine ID
		double dblLevel;			///< condition level 0. ~ 1., it is related the machine performance and error
		double dblLimitRateOperation;///< maximum operation rate 0. ~ 1.
	};

	//! machine log
	struct MachineLogType
	{
		//! clear all members
		void Clear();
		//! to string
		const std::string ToString();

		int nPart;
		int nLot;
		int nStep;
		int nMachine;
		int nWaferNo;
		double dblYield;
		double dblElapsedTime;
	};

	/*! operation type
		information of the process of the operation, derived class from OperationType
		O(lot, step) depends on the lot and the step
	*/
	struct OperationType {
		//! constructor
		OperationType(int lot = -1, int step = -1, int machine = -1, double proctime = 0., double starttime = 0., double endtime = 0)
			: nLot(lot), nStep(step), nMachine(machine), dblProcTime(proctime), dblStartTime(starttime), dblEndTime(endtime) {}
		//! destructor
		~OperationType() {}
		//! init
		virtual void Init()
		{
			nLot = nStep = nMachine = -1;
			dblStartTime = dblEndTime = 0.;
		}
		//! is empty
		bool Empty() const
		{
			if (nLot == -1 || nStep == -1) {
				return true;
			}
			else {
				return false;
			}
		}
		//! overloading operator==
		bool operator==(const OperationType& o) const
		{
			if (nLot == o.nLot && nStep == o.nStep /*&& nMachine == o.nMachine*/) {
				return true;
			}
			return false;
		}
		//! overloading operator!=
		bool operator!=(const OperationType& o) const
		{
			return !(*this == o);
		}
		//! operator< overloading
		bool operator<(const OperationType& op) const
		{
			if (nLot < op.nLot || (nLot == op.nLot && nStep < op.nStep)) {
				return true;
			}
			return false;
		}
		//! for making a string using members
		const std::string ToString() const
		{
			std::ostringstream oss;
			oss << "O(" << nLot << ',' << nStep << ',' << nMachine << ',' << dblProcTime << ')';
			return oss.str();
		}

		int nLot;			///< lot id
		int nStep;			///< step id
		int nMachine;		///< machine id
		double dblProcTime;	///< process time
		double dblStartTime;///< time of the operation of the lot
		double dblEndTime;	///< Job end time
	};

	//-------------------------------------------------------------------------
	// define conatiners
	//! container of operation process type
	typedef std::vector< OperationType > OperationContainer;
	//! order operations to machine using the OperationType of the vector container
	typedef std::vector< OperationContainer > OperationOrderContainer;
}

#endif // __TYPES_HPP__
