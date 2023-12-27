#include "library/core.data.h"
#include "core/LogStream.h"
using namespace core;

// Define program meta-data
//metadata std::string_view meta::Settings<program_name> = "Core.Data Database I/O Application";
//metadata std::string_view meta::Settings<program_version> = "Demo";

//! @brief  Entry-point
int16_t
intern run(std::wstring_view const cmdLine)
try {
	// Create log-file only if user provided "-log" commandline switch
	if (cmdLine.contains(L"-log")) 
		clog.createLogFile("appDatabase.log");
	startupBanner();
	
	// TODO:
	return 0;
}
catch (std::exception const& e)
{
	clog << e;
	return -1;
}

// Entry point
int 
wmain(int argc, wchar_t* argv[]) {
	return ::run(argc > 1 ? argv[1] : L"");
}