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
	reSet ();
}


double SIMSEMI::CElapsedTime::sec () const
{
	clock_t current = clock ();
	return ((double)(current - starting_) / CLOCKS_PER_SEC);
}


void SIMSEMI::CElapsedTime::reSet ()
{
	starting_ = clock ();
}

// CHiResElapsedTime
//-----------------------------------------------------------------------------
SIMSEMI::CHiResElapsedTime::CHiResElapsedTime () : starting_ (0)
{
	reSet ();
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

void SIMSEMI::CHiResElapsedTime::reSet ()
{
	struct timeval t;
	gettimeofday (&t, 0);

	starting_ = 1.e-6 * t.tv_usec + t.tv_sec;
}

//-----------------------------------------------------------------------------
//! operator<< overloading for printing OperationType to out stream directly
std::ostream& SIMSEMI::operator<<(std::ostream& os, const SIMSEMI::OperationType& op)
{
	os << op.ToString();
	return os;
}
//! operator<< overloading for printing OperationContainer to out stream directly
std::ostream& SIMSEMI::operator<<(std::ostream& os, const SIMSEMI::OperationContainer& Operations)
{
	for (size_t j = 0; j < Operations.size() - 1; j++) {
		os << Operations[j].ToString() << ' ';
	}
	os << Operations[Operations.size() - 1];

	return os;
}

bool SIMSEMI::operator==(const SIMSEMI::OperationContainer& j1, const SIMSEMI::OperationContainer& j2)
{
	if (j1.size() != j2.size()) {
		return false;
	}
	for (OperationContainer::const_iterator ci1 = j1.begin(), ci2 = j2.begin() ; ci1 != j1.end() ; ++ci1, ++ci2 ) {
		if (*ci1 != *ci2) {
			return false;
		}
	}
	return true;
}

bool SIMSEMI::operator!=(const SIMSEMI::OperationContainer& j1, const SIMSEMI::OperationContainer& j2)
{
	return !(j1==j2);
}

/*! overloading operator<
	opeartor< is meaning that makespan is less and total workload, max workload are greater.
	comparison priority is makespan -> total workload -> max workload.
*/
bool SIMSEMI::operator<(const SIMSEMI::EvaluationOfSolutionType& eos1, const SIMSEMI::EvaluationOfSolutionType& eos2)
{
	if (eos1.dblMakespan < eos2.dblMakespan) {
		return true;
	}
	else if (eos1.dblMakespan == eos2.dblMakespan
		&& eos1.dblTotalWorkload > eos2.dblTotalWorkload ) {
		return true;
	}
	else if (eos1.dblMakespan == eos2.dblMakespan
		&& eos1.dblTotalWorkload == eos2.dblTotalWorkload
		&& eos1.dblMaxWorkload > eos2.dblMaxWorkload) {
		return true;
	}
	return false;
}
/*! overloading operator<
	opeartor< is meaning that makespan is less and total workload, max workload are greater.
	comparison priority is makespan -> total workload -> max workload.
*/
bool SIMSEMI::operator>(const SIMSEMI::EvaluationOfSolutionType& eos1, const SIMSEMI::EvaluationOfSolutionType& eos2)
{
	if (eos1.dblMakespan > eos2.dblMakespan) {
		return true;
	}
	else if (eos1.dblMakespan == eos2.dblMakespan
		&& eos1.dblTotalWorkload < eos2.dblTotalWorkload ) {
		return true;
	}
	else if (eos1.dblMakespan == eos2.dblMakespan
		&& eos1.dblTotalWorkload == eos2.dblTotalWorkload
		&& eos1.dblMaxWorkload < eos2.dblMaxWorkload) {
		return true;
	}
	return false;
}