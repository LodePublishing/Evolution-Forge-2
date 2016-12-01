#ifndef _GUI_EXPORT_HPP
#define _GUI_EXPORT_HPP

// define GUI_EXPORTS to make it a dll
#ifndef GUI_API
    #ifdef _MSC_VER
        #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #undef min
        #undef max
		#ifdef GUI_EXPORTS
		    #define GUI_API __declspec(dllexport)
		#else
		    #define GUI_API __declspec(dllimport)
		#endif
		#else
		    #define GUI_API
	# endif
#endif

#endif // _GUI_EXPORT_HPP