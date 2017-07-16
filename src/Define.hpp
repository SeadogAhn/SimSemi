#ifndef __DEFINE_HPP__
#define __DEFINE_HPP__

#define SIMSEMI_D_MIN_CNT_WAFER_IN_LOT  1
#define SIMSEMI_D_MAX_CNT_WAFER_IN_LOT  25

#define SIMSEMI_D_MAX_CNT_HOT_LOT       3

#define SIMSEMI_D_STEP_LIMIT			3
#define SIMSEMI_D_STEP_1_RATE			0.2
#define SIMSEMI_D_STEP_2_RATE			0.75
#define SIMSEMI_D_STEP_3_RATE			0.5

#define SIMSEMI_D_TEST_TIME_MIN			5.0
#define SIMSEMI_D_TEST_TIME_MEAN		45.0
#define SIMSEMI_D_TEST_TIME_MAX			120.0

#ifdef _DEBUG
#include <iostream>
#include <typeinfo>
#define SIMSEMI_MEMBER_FUNC				std::cout << typeid(*this).name() << "::" << __FUNCTION__
#define SIMSEMI_MEMBER_FUNC_START		SIMSEMI_MEMBER_FUNC << ":START" << std::endl;
#define SIMSEMI_MEMBER_FUNC_END			SIMSEMI_MEMBER_FUNC << ":END" << std::endl;
#else
#define SIMSEMI_MEMBER_FUNC
#define SIMSEMI_MEMBER_FUNC_START
#define SIMSEMI_MEMBER_FUNC_END
#endif

#endif // __DEFINE_HPP
