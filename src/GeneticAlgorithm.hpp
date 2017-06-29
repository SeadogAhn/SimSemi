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
		 	\param crossover Crossover Rate
		 	\param mutation Mutation Rate
		 */
		CGeneticAlgorithm(int population = 5000, int loop = 500, double crossover = 0.6, double mutation = 0.2);
		//! destructor
		~CGeneticAlgorithm();
		//! execute to generate a optimal solution
		/*!
			\param StepInfo each step of jobs
			\param nMachineCnt number of machines
		*/
		void execOptimalSolutionGeneration(const Vec_INT& StepInfo, int nMachineCnt);
		//! get to be generated a Job container of a global best solution
		const JobContainer& getOptimalSolution() const { return GlobalBestSolution_; }
		//! get evaluated values
		const Vec_DBL& getEvaluatedVals() const { return EvaluatedVals_; }
	protected:

	private:
		//! initialize all memebers
		void init(int population, int loop, double crossover, double mutation);
		//! set population size
		/*!
			\param n size of population
		*/
		void setPopulation();
		//! selection
		void selection();
		//! crossover
		void crossover();
		//! mutation
		void mutation();
		//! decoding
		void decode();
		//! encoding
		void encode();
		//! statistics summary
		void statistics();

		//! population is generated job containers randomly
		JobsContainer Population_;
		//! global best solution
		JobContainer GlobalBestSolution_;
		// parents
		JobContainer Parent1_;
		JobContainer Parent2_;
		// child
		JobContainer Offspring_;

		//! population size
		int nPopulationSize_;
		//! generation loop limit
		int nGenerationLoopLimit_;
		//! crossover rate
		double dblCrossoverRate_;
		//! mutation rate
		double dblMutationRate_;
		//! evaluated values of the generated feasible solutions
		Vec_DBL EvaluatedVals_;
		//! feasible solution generator
		CFeasibleSolutionGenerator FeasibleSolutionGenerator_;
	};
}

#endif // __GENETIC_ALGORITHM_HPP__
