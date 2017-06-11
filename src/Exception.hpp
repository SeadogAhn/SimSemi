#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

// SIMSEMI headers

// standard libraries
#include <exception>

//! the namespace of the simulation for the manufacturing semiconductor process
//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {

	class Exception : public exception
	{
	public:
		virtual const char* what() const throw();
	};
}

#endif //__EXCEPTION_HPP__