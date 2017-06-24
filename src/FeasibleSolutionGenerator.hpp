#ifndef __FEASIBLE_SOLUTIONS_GENERATOR_HPP__
#define __FEASIBLE_SOLUTIONS_GENERATOR_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "Utility.hpp"

// standard libraries


//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! generate feasible solutions for multi flexbile job shop
	class CFeasibleSolutionGenerator
	{
	public:
		//! default constructor
		CFeasibleSolutionGenerator();
		//! destructor
		~CFeasibleSolutionGenerator();
		//! set operation
		/*!
			\param StepInfo each step of jobs
			\param nMachineCnt
		*/
		void setOperation(const std::vector<int>& StepInfo, int nMachineCnt);
		//! get a random fesible solution
		/*!
			\return to be generated a solution ran
		*/
		const JobContainer getRandomFeasibleSolution();
		//! get a random fesible solution
		/*!
			\param n number of Jobs, the generated Jobs independently of each other.
			\return to be generated a solution ran
		*/
		const std::vector<JobContainer> getRandomFeasibleSolutions(int n);
		//! get neighborhood Jobs
		/*!
			\param Jobs a source jobs
			\return a neighborhood jobs
		*/
		const JobContainer getNeighborhoodJobs(const JobContainer& Jobs);
	protected:

	private:
		//! permutate JobContainer using the next_permutation algorithm of standard library
		/*!
			\param Jobs
		*/
		void permutate(JobContainer& Jobs);
		//! check a JobContainer wheather a feasible solution
		/*!
			\param Jobs
		*/
		bool checkPolicy(const JobContainer& Jobs);
		//! initialize machine at each element(OperationType) in Jobs
		/*!
			applied bit shift technique
			\param Jobs Job container
		*/
		void initMachine(JobContainer& Jobs);

		JobContainer Jobs_;	///< Jobs
		int nJobCnt_;		///< Job count
		int nStepCnt_;		///< step count, the step is similar to operation
		int nMachineCnt_;	///< machine count
	};
} // namespace SIMSEMI

#endif // __FEASIBLE_SOLUTIONS_GENERATOR_HPP__