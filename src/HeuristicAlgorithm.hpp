#ifndef __HEURISTIC_ALGORITHM_HPP__
#define __HEURISTIC_ALGORITHM_HPP__

// SIMSEMI headers
#include "FeasibleSolutionGenerator.hpp"
// standard libraries


//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
	//! Heuristic algorithm
	class CHeuristicAlgorithm
	{
	public:
		//! default constructor
		CHeuristicAlgorithm(int population = 1, int loop = 1);
		//! destructor
		~CHeuristicAlgorithm();
		//! execute to generate a optimal solution
		/*!
			\param StepInfo each step of lots
			\param nMachineCnt number of machines
		*/
		void ExecOptimalSolutionGeneration(const OperationContainer& Operations, int nLotCnt, int nMachineCnt);
		//! Get to be generated a Job container of a global best solution
		const OperationContainer& GetOptimalSolution() const { return GlobalBestSolution_; }
		//! Get evaluated values
		const Vec_DBL& GetEvaluatedVals() const { return EvaluatedVals_; }
	protected:

	private:
		//! initialize all memebers
		void Init(int population, int loop);
		//! Set population size
		/*!
			\param n size of population
		*/
		void SetPopulation();
		//! Selection
		void Selection();

		// member variables
		OperationOrderContainer Population_;	///< population is generated lot containers randomly
		OperationContainer GlobalBestSolution_;	///< global best solution
		OperationContainer LocalBestSolution_;	///< local best solution

		int nPopulationSize_;		///< population size
		int nGenerationLoopLimit_;	///< generation loop limit
		Vec_DBL EvaluatedVals_;		///< evaluated values of the generated feasible solutions
		CFeasibleSolutionGenerator FeasibleSolutionGenerator_;	///< feasible solution generator
	};
}

#endif //__HEURISTIC_ALGORITHM_HPP__
