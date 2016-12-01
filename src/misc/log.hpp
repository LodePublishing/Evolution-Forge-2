#ifndef _MISC_LOG_HPP
#define _MISC_LOG_HPP

#include <string>

extern void toDebugLog(const std::string txt);
extern void toInfoLog(const std::string txt);
extern void toWarnLog(const std::string txt);
extern void toErrorLog(const std::string txt);

#endif // _MISC_LOG_HPP