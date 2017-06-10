#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include "Define.hpp"

#include <map>
#include <vector>
#include <utility>
#include <string>

//! the namespace of simulation for semiconductor EDS process
namespace SIMSEMI {
    // vector types
    typedef std::vector<std::string> Vec_STR;

    // type of product information, first is a partid, second is a sortflag(is same stepid)
    typedef std::pair<std::string, std::string> ProdInfoType;

}

#endif // __TYPES_HPP__
