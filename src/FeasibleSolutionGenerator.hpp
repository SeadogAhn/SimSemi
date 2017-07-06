#ifndef __FEASIBLE_SOLUTIONS_GENERATOR_HPP__
#define __FEASIBLE_SOLUTIONS_GENERATOR_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "Utility.hpp"

// standard libraries
#include <vector>
#include <deque>
#include <utility>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! generate feasible solutions for multi flexbile lot shop
	class CFeasibleSolutionGenerator
	{
	public:
		//! first is lot and second is step in pair in queue in vector
		typedef std::vector<std::deque<OperationType> > OperationQueue;
		//! default constructor
		CFeasibleSolutionGenerator();
		//! destructor
		~CFeasibleSolutionGenerator();
		//! Set operation
		/*!
			\param StepInfo each step of lots
			\param nMachineCnt
		*/
		void SetOperation(const OperationContainer& Operations, int nLotCnt, int nMachineCnt);
		//! Get a random fesible solution
		/*!
			\return to be generated a solution ran
		*/
		const OperationContainer GetRandomFeasibleSolution();
		//! Get a random fesible solution
		/*!
			\param n number of Operations, the generated Operations independently of each other.
			\solutions to be generated feasible solutions for comparing new and old
			\return to be generated a solution ran
		*/
		const OperationOrderContainer GetRandomFeasibleSolutions(size_t n, const OperationOrderContainer& solutions = OperationOrderContainer());
		//! Get neighborhood Operations
		/*!
			\param Operations a source lots
			\return a neighborhood lots
		*/
		const OperationContainer GetNeighborhoodOperProc(const OperationContainer& Operations);
		//! check a OperationContainer wheather a feasible solution
		/*!
			\param Operations
		*/
		bool CheckPolicy(const OperationContainer& Operations);
		//! evaluate Operations
		/*!
			\param Operations
		*/
		double EvaluateOperProc(const OperationContainer& Operations);
		//! make table data for drawing gantt chart
		/*!
			\param Job order container
		*/
		void MakeGanttTableData(const OperationContainer& Operations, std::string strFileName = "C:\\temp\\GanttData");
	protected:

	private:
		//! Permutate OperationContainer using the next_perMutation algorithm of standard library
		/*!
			\param Operations
		*/
		void Permutate(OperationContainer& Operations);
		//! initialize machine at each element(OperationType) in Operations
		/*!
			applied bit shift technique
			\param Operations Job container
		*/
		void InitMachine(OperationContainer& Operations);
		//! generation machine lot order
		/*!
			\param Operations
		 */
		void OrderOperationMachine( const OperationContainer& Operations );

		OperationContainer Operations_;	///< source operations
		OperationOrderContainer OperationsOrder_; ///< container of to order operations to machines
		OperationQueue OperQueue_; ///< queue in the conatiner for generating Operations randomly
		int nLotCnt_;		///< Job count
		int nMachineCnt_;	///< machine count
	};
} // namespace SIMSEMI

#endif // __FEASIBLE_SOLUTIONS_GENERATOR_HPP__
