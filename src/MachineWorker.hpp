#ifndef __MACHINE_WORKER_HPP__
#define __MACHINE_WORKER_HPP__

// SIMSEMI headers
#include "Utility.hpp"
// standard libraries


//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
	//! a Machine worker using thread
	class CMachineWorker : public CThread
	{
	public:
		CMachineWorker();
		~CMachineWorker();

	protected:

	private:

	};
}
#endif // __MACHINE_WORKER_HPP__
