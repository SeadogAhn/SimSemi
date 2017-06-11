#include "Utility.h"

// CmutexAttribute
//-----------------------------------------------------------------------------
CmutexAttribute* SIMSEMI::CmutexAttribute::sOnly_ = 0;

CmutexAttribute& SIMSEMI::CmutexAttribute::gOnly ()
{
	if (!sOnly_)
		sOnly_ = new CmutexAttribute ();
	return *sOnly_;
}

SIMSEMI::CmutexAttribute::CmutexAttribute ()
{ 
	pthread_mutexattr_init (&attr_);
	pthread_mutexattr_settype (value(), PTHREAD_MUTEX_RECURSIVE);
}


SIMSEMI::CmutexAttribute::~CmutexAttribute ()
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
