#ifndef __GENETIC_ALGORITHM_HPP__
#define __GENETIC_ALGORITHM_HPP__

// SIMSEMI headers

// standard libraries


//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
	//! genetic algorithm
	class CGeneticAlgorithm
	{
	public:
		CGeneticAlgorithm();
		~CGeneticAlgorithm();


	protected:

		void selection();
		void crossover();
		void mutation();
		void decode();
		void statistics();


	private:

	};
}

#endif // __GENETIC_ALGORITHM_HPP__
