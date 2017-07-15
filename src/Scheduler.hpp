#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

// SIMSEMI headers
#include "Types.hpp"
#include "HeuristicAlgorithm.hpp"
#include "GeneticAlgorithm.hpp"
#include "PSOAlgorithm.hpp"
#include "ACOAlgorithm.hpp"

// standard libraries

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
    //! Scheduler
    class CScheduler
    {
    public:
		//! default constructor
		CScheduler();
		//! destructor
		~CScheduler();
		//! make schedule using a optimization algorithm
		/*!
			\param Products information of generated products
		*/
		void MakeSchedule();

    protected:

    private:
		//! make a data Set of the gantt chart
		/*!
			return a file name
		*/
		const std::string MakeGanttData();

		//! heuristic algorithm
		CHeuristicAlgorithm HeuristicAlgo_;
		//! genetic algorithm
		CGeneticAlgorithm GeneticAlgo_;
		//! ant colony optimization algirthm
		CACOAlgorithm AcoAlgo_;
		//! particle swarm optimization algorithm
		CPSOAlgorithm PsoAlgo_;
    };
}

#endif // __SCHEDULER_HPP__
