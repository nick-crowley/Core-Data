#include "library/core.data.h"
#include "core/LogStream.h"
using namespace core;

// Define program meta-data
//metadata std::string_view meta::Settings<program_name> = "Core.Data Simple database Application";
//metadata std::string_view meta::Settings<program_version> = "Demo";

//! @brief  Entry-point
int16_t
intern run(std::wstring_view const cmdLine)
try {
	// Create log-file only if user provided "-log" commandline switch
	if (cmdLine.contains(L"-log")) 
		clog.createLogFile("appDatabase.log");
	else
		clog.attach(std::cout);
	startupBanner();
	
	clog << Important{"Creating in-memory database"};
	using enum data::ConnectionFlags;
	data::Connection db = data::Connection::open("whatever.db", Create|Memory|ReadWrite);

	clog << Important{"Creating 'Employees' table"};
	db.execute("CREATE TABLE IF NOT EXISTS Employees (ID INTEGER PRIMARY KEY,"
                                                     "Name TEXT NOT NULL,"
                                                     "Salary REAL)");
	db.execute("INSERT INTO Employees VALUES ('1', 'Darren', '24000')");
	db.execute("INSERT INTO Employees VALUES ('2', 'Susan', '55000')");

	clog << Important{"Querying database..."};
	for (auto [name,salary] : db.execute<std::string,float>("SELECT Name, Salary FROM Employees"))
		clog << Important{"-> Found employee: name={} salary={}", name, salary};

	return 0;
}
catch (std::exception const& e)
{
	clog << e;
	return -1;
}

int 
wmain(int argc, wchar_t* argv[]) {
	return ::run(argc > 1 ? argv[1] : L"");
}