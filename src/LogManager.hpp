/*------------------------------------------------------------------------------------
* finename    : LogManager.h
* eng'r name  : Seadog Ahn(seadog.ahn@gmail.com)
* reference code : ddj -> http://www.ddj.com/cpp/201804215
*-----------------------------------------------------------------------------------*/

#ifndef __LOGMANAGER_HPP__
#define __LOGMANAGER_HPP__

// standard libraries
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <sys/time.h>

//! the namespace of the simulation for the manufacturing semiconductor process
namespace SIMSEMI {
	inline std::string NowTime();

	enum TLogLevel { logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4 };

	template <typename T>
	class CLog
	{
	public:
		CLog();
		virtual ~CLog();
		std::ostringstream& Get(TLogLevel level = logINFO);
	public:
		static TLogLevel& ReportingLevel();
		static std::string ToString(TLogLevel level);
		static TLogLevel FromString(const std::string& level);
	protected:
		std::ostringstream os;
	private:
		CLog(const CLog&);
		CLog& operator =(const CLog&);
	};

	class Output2FILE {
	public:
		static FILE*& Stream()
		{
			static FILE* pStream = stderr;
			return pStream;
		}

		static void Output(const std::string& msg)
		{
			FILE* pStream = Stream();
			if (!pStream)
				return;
			std::fprintf(pStream, "%s", msg.c_str());
			std::fflush(pStream);
		}
	};

	typedef CLog<Output2FILE> CLogManager;

	template <typename T>
	CLog<T>::CLog()
	{
	}

	template <typename T>
	std::ostringstream& CLog<T>::Get(TLogLevel level)
	{
		os << "- " << NowTime();
		os << " " << ToString(level) << ": ";
		os << std::string(level > logDEBUG ? level - logDEBUG : 0, '\t');
		return os;
	}

	template <typename T>
	CLog<T>::~CLog()
	{
		os << std::endl;
		T::Output(os.str());
	}

	template <typename T>
	TLogLevel& CLog<T>::ReportingLevel()
	{
		static TLogLevel reportingLevel = logDEBUG4;
		return reportingLevel;
	}

	template <typename T>
	std::string CLog<T>::ToString(TLogLevel level)
	{
		static const char* const buffer[] = { "ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4" };
		return buffer[level];
	}

	template <typename T>
	TLogLevel CLog<T>::FromString(const std::string& level)
	{
		if (level == "DEBUG4")	return logDEBUG4;
		if (level == "DEBUG3")	return logDEBUG3;
		if (level == "DEBUG2")	return logDEBUG2;
		if (level == "DEBUG1")	return logDEBUG1;
		if (level == "DEBUG")	return logDEBUG;
		if (level == "INFO")	return logINFO;
		if (level == "WARNING")	return logWARNING;
		if (level == "ERROR")	return logERROR;

		CLog<T>().Get(logWARNING) << "Unknown logging level '" << level << "'. Using INFO level as default.";
		return logINFO;
	}

	#ifndef FILELOG_MAX_LEVEL
	#define FILELOG_MAX_LEVEL logDEBUG4
	#endif

	#define FILE_LOG(level) \
		if (level > FILELOG_MAX_LEVEL) ;\
		else if (level > CLogManager::ReportingLevel() || !Output2FILE::Stream()) ; \
		else CLogManager().Get(level)

	inline std::string NowTime()
	{
		char buffer[11];
		time_t t;
		time(&t);
		tm r = { 0 };
		strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
		struct timeval tv;
		gettimeofday(&tv, 0);
		char result[100] = { 0 };
		std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000);
		return result;
	}

}
#endif //__LOGMANAGER_HPP__