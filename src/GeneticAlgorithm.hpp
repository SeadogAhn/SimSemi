#ifndef __GENETIC_ALGORITHM_HPP__
#define __GENETIC_ALGORITHM_HPP__

// SIMSEMI headers
#include "FeasibleSolutionGenerator.hpp"
// standard libraries


//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
	//! genetic algorithm
	class CGeneticAlgorithm
	{
	public:
		//! default constructor
		/*!
			\param population Population size
		 	\param loop the number of the looping
		 	\param Crossover Crossover Rate
		 	\param Mutation Mutation Rate
		 */
		CGeneticAlgorithm(int population = 5000, int loop = 500, double Crossover = 1., double Mutation = 0.2);
		//! destructor
		~CGeneticAlgorithm();
		//! execute to generate a optimal solution
		/*!
			\param Operations operations
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
		void Init(int population, int loop, double Crossover, double Mutation);
		//! Set population size
		void SetPopulation();
		//! Get a best solution in lotscontainer
		const OperationContainer GetBestSolutionInPopulation(const OperationOrderContainer& population);
		//! Selection
		void Selection();
		//! Crossover
		void Crossover();
		//! Mutation
		void Mutation();

		//! population is generated lot containers randomly
		OperationOrderContainer Population_;
		//! global best solution
		OperationContainer GlobalBestSolution_;
		// parents
		OperationContainer Parent1_;
		OperationContainer Parent2_;
		// child
		OperationContainer Offspring_;

		//! population size
		int nPopulationSize_;
		//! generation loop limit
		int nGenerationLoopLimit_;
		//! Crossover rate
		double dblCrossoverRate_;
		//! Mutation rate
		double dblMutationRate_;
		//! evaluated values of the generated feasible solutions
		Vec_DBL EvaluatedVals_;
		//! feasible solution generator
		CFeasibleSolutionGenerator FeasibleSolutionGenerator_;
	};
}

#endif // __GENETIC_ALGORITHM_HPP__
