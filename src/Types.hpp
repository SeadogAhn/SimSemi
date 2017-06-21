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

	//! operation type
	/*
		O (job, step, machine), and time is depend on the job and the step and the rate of the performance of the machine
	*/
	struct OperationType {
		//! constructor overloading, include default values
		OperationType(int i = -1, int j = -1, int k = -1, int t = -1) :job(i), step(j), machine(k), prctime(t) {}
		int job;
		int step;
		int machine;
		int prctime;
		//! is empty
		bool empty() const
		{
			if (job == -1 || step == -1 || machine == -1 || prctime == -1) {
				return true;
			}
			else {
				return false;
			}
		}
		//! operator== overloading
		bool operator==(const OperationType& op) const
		{
			if (job == op.job && step == op.step && machine == op.machine) {
				return true;
			}
			return false;
		}

		bool operator!=(const OperationType& op) const
		{
			return !(*this == op);
		}
		//! operator< overloading
		bool operator<(const OperationType& op) const
		{
			if (job < op.job || (job == op.job && step < op.step)) {
				return true;
			}
			return false;
		}
		//! for making a string using members
		const std::string ToString() const
		{
			std::ostringstream oss;
			oss << "O(" << job << ',' << step << ',' << machine << ')';
			return oss.str();
		}
	};

	//! type define the container of OperationTypes
	typedef std::vector<OperationType> JobContainer;

}

#endif // __TYPES_HPP__
