#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

// SIMSEMI headers
#include "Types.hpp"

// standard libraries
#include <pthread.h>
#include <cstdlib>
#include <limits>
#include <time.h>
#include <sys/time.h>  // For gettimeofday(), timeval


//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {

	//! CMutexAttribute
	/*! Our version of CLock resuses the same pthread_mutexattr_t object
	    each time. This object initializes it. The value() method returns
	    a pointer that you can pass to pthread_mutex_init
	*/
	class CMutexAttribute
	{
	public:
		static CMutexAttribute& gOnly();

		pthread_mutexattr_t* value() { return &attr_; }

	private:
		static CMutexAttribute* sOnly_;

		pthread_mutexattr_t attr_;

		CMutexAttribute();
		~CMutexAttribute();
	};

	//! Thread locker
	class CLock
	{
	public:
		CLock()
		{
			pthread_mutex_init(&lock_, CMutexAttribute::gOnly().value());
		}
		~CLock() { pthread_mutex_destroy(&lock_); }

		CLock(const CLock&)
		{
			pthread_mutex_init(&lock_, CMutexAttribute::gOnly().value());
		}

		CLock& operator= (const CLock&) { return *this; }


		// Get the lock
		bool lock() const
		{
			return pthread_mutex_lock(&lock_) == 0;
		}

		// Release the lock
		bool unlock() const
		{
			return pthread_mutex_unlock(&lock_) == 0;
		}

	private:
		mutable pthread_mutex_t lock_;
	};

	//! Thread base class
	class CThread
	{
	public:
		CThread() : threadid_(0) {}
		virtual ~CThread() { if (threadid_ != 0) stop(); }

		int threadid() const { return (int)threadid_; }

		//! Start the thread running
		bool start()
		{
			int status;
			status = pthread_create(&threadid_, 0, thread_, this);
			return (status == 0);
		}

		//! Stop the thread. Ungraceful and may result in locking/resource problems.
		bool stop()
		{
			pthread_cancel(threadid_);
			return true;
		}

		//! Wait for thread to complete
		bool wait(unsigned int seconds = 0)
		{
			// Time is ignored here
			char* rc;
			pthread_join(threadid_, (void**)&rc);
			return true;
		}

		//! Sleep for the specified amount of time.
		void sleep(unsigned int msec)
		{
			struct timespec spec, rspec;
			spec.tv_sec = msec / 1000;
			spec.tv_nsec = (msec % 1000) * 1000000;
			nanosleep(&spec, &rspec);
		}

	protected:
		static void* thread_(void* obj)
		{
			// Call the overriden thread function
			CThread* t = reinterpret_cast<CThread*>(obj);
			t->thread();
			return 0;
		}

		//! Thread function, Override this in derived classes.
		virtual void thread() {}

		pthread_t threadid_;
	};

	//! ElapsedTime
	class CElapsedTime
	{
	public:
		//! Record the current time
		CElapsedTime ();
		// Return elapsed time, in milliseconds or sec
		double msec () const { return sec() * 1000;}
		double sec  () const;
		// ReSet the current time
		void reSet ();
	private:
		clock_t starting_;	///< Starting time
	};

	//! High-resolution Simple elapsed time class
	class CHiResElapsedTime
	{
	public:
		//! Record the current time
		CHiResElapsedTime ();
		//! Return elapsed time, in microseconds.
		double usec () const;
		//! Return elapsed time, in milliseconds.
		double msec () const;
		//! Return elapsed time, in seconds
		double sec () const;
		//! ReSet the current time
		void reSet ();

	private:
		double starting_;	///< Starting time
	};

	//! Generating integer random number class
	/*!
		range [ nRangeMin_, nRangeMax_ )
	*/
	class CIntRandom {
	public:
		CIntRandom( int nMin = 0, int nMax = RAND_MAX )
		{
			nRangeMin_ = nMin;
			nRangeMax_ = nMax;
		}

		void SetRange( int nMin = 0, int nMax = RAND_MAX )
		{
			nRangeMin_ = nMin;
			nRangeMax_ = nMax;
		}

		int execNumberGenerate()
		{
			srand( (unsigned)time(NULL) );
			return ( ( rand() % ( nRangeMax_ - nRangeMin_ ) ) + nRangeMin_ );
		}

	private:
		int nRangeMin_;
		int nRangeMax_;
	};

	///////////////////////////////////////////////////////////////////////////
	// operator overloading

	// OperationContainer & OperationType operators
	//! operator<< overloading for printing OperationType to out stream directly
	std::ostream& operator<<(std::ostream& os, const OperationType& op);
	//! operator<< overloading for printing OperationContainer to out stream directly
	std::ostream& operator<<(std::ostream& os, const OperationContainer& Operations);
	//! compare equare
	bool operator==(const OperationContainer& j1, const OperationContainer& j2);
	//! compare not equare
	bool operator!=(const OperationContainer& j1, const OperationContainer& j2);
	/*! overloading operator<
		opeartor< is meaning that makespan is less and total workload, max workload are greater.
		comparison priority is makespan -> total workload -> max workload.
	*/
	bool operator<(const EvaluationOfSolutionType& eos1, const EvaluationOfSolutionType& eos2);
	/*! overloading operator<
		opeartor< is meaning that makespan is less and total workload, max workload are greater.
		comparison priority is makespan -> total workload -> max workload.
	*/
	bool operator>(const EvaluationOfSolutionType& eos1, const EvaluationOfSolutionType& eos2);

	///////////////////////////////////////////////////////////////////////////
	// utility functions

	template < typename Container = std::vector<std::string> >
	void fnStringSpliter( Container& container, std::string const & strSource, const char* const chDelimiters = " \t\n,|")
	{
		const std::string::size_type len = strSource.length();
		std::string::size_type i = 0;

		while (i < len)
		{
			// Eat leading whitespace
			i = strSource.find_first_not_of(chDelimiters, i);
			if (i == std::string::npos)
				return;   // Nothing left but white space

			// Find the end of the token
			std::string::size_type j = strSource.find_first_of(chDelimiters, i);

			// Push token
			if (j == std::string::npos) {
				container.push_back(strSource.substr(i));
				return;
			}
			else {
				container.push_back(strSource.substr(i, j-i));
			}
			// Set up for next loop
			i = j + 1;
		}
	}
}

#endif // __UTILITY_HPP__
