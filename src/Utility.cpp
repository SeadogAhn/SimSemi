#include "Utility.hpp"

using namespace std;
using namespace SIMSEMI;

// CmutexAttribute
//-----------------------------------------------------------------------------
CMutexAttribute* SIMSEMI::CMutexAttribute::sOnly_ = 0;

CMutexAttribute& SIMSEMI::CMutexAttribute::gOnly ()
{
	if (!sOnly_)
		sOnly_ = new CMutexAttribute ();
	return *sOnly_;
}

SIMSEMI::CMutexAttribute::CMutexAttribute ()
{
	pthread_mutexattr_init (&attr_);
	pthread_mutexattr_settype (value(), PTHREAD_MUTEX_RECURSIVE);
}


SIMSEMI::CMutexAttribute::~CMutexAttribute ()
{
	pthread_mutexattr_destroy (&attr_);
}

// CElapsedTime
//-----------------------------------------------------------------------------
SIMSEMI::CElapsedTime::CElapsedTime () : starting_ (0)
{
	reset ();
}


double SIMSEMI::CElapsedTime::sec () const
{
	clock_t current = clock ();
	return ((double)(current - starting_) / CLOCKS_PER_SEC);
}


void SIMSEMI::CElapsedTime::reset ()
{
	starting_ = clock ();
}

// CHiResElapsedTime
//-----------------------------------------------------------------------------
SIMSEMI::CHiResElapsedTime::CHiResElapsedTime () : starting_ (0)
{
	reset ();
}

double SIMSEMI::CHiResElapsedTime::usec () const
{
	return sec() * 1000000.;
}

double SIMSEMI::CHiResElapsedTime::msec () const
{
	return sec() * 1000;
}

double SIMSEMI::CHiResElapsedTime::sec () const
{
	struct timeval t;
	gettimeofday (&t, 0);

	double now = 1.e-6 * t.tv_usec + t.tv_sec;

	return (now - starting_);
}

void SIMSEMI::CHiResElapsedTime::reset ()
{
	struct timeval t;
	gettimeofday (&t, 0);

	starting_ = 1.e-6 * t.tv_usec + t.tv_sec;
}

//-----------------------------------------------------------------------------
//! operator<< overloading for printing OperationType to out stream directly
std::ostream& SIMSEMI::operator<<(std::ostream& os, const OperationType& op)
{
	os << op.ToString();
	return os;
}
//! operator<< overloading for printing JobContainer to out stream directly
std::ostream& SIMSEMI::operator<<(std::ostream& os, const JobContainer& Jobs)
{
	for (size_t j = 0; j < Jobs.size() - 1; j++) {
		os << Jobs[j].ToString() << ' ';
	}
	os << Jobs[Jobs.size() - 1];

	return os;
}

bool SIMSEMI::operator==(const JobContainer& j1, const JobContainer& j2)
{
	if (j1.size() != j2.size()) {
		return false;
	}
	for (JobContainer::const_iterator ci1 = j1.begin(), ci2 = j2.begin()
		; ci1 != j1.end()
		; ++ci1, ++ci2 ) {
		if (*ci1 != *ci2) {
			return false;
		}
	}
	return true;
}

bool SIMSEMI::operator!=(const JobContainer& j1, const JobContainer& j2)
{
	return !(j1==j2);
}
