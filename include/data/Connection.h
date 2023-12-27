/* o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o */ /*!
* @copyright	Copyright (c) 2023, Nick Crowley. All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without modification, are permitted
* provided that the following conditions are met:
* 
* 1. Redistributions of source code must retain the above copyright notice, this list of conditions
*    and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice, this list of
*    conditions and the following disclaimer in the documentation and/or other materials provided
*    with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
* FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
* WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
* The views and conclusions contained in the software and documentation are those of the author 
* and should not be interpreted as representing official policies, either expressed or implied, of
* the projects which contain it.
*/
// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=o Preprocessor Directives o~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o
#pragma once
// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o Header Files o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o
#include "library/core.data.h"
#include "data/SharedHandle.h"
// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o Name Imports o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o

// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o Forward Declarations o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o

// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~o Macro Definitions o-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o

// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~o Constants & Enumerations o~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o
namespace core::data
{
	enum class ConnectionFlags {
		ReadOnly     = SQLITE_OPEN_READONLY,     //!< The database is opened in read-only mode.
		ReadWrite    = SQLITE_OPEN_READWRITE,    //!< The database is opened for reading and writing if possible, or reading only if the file is write protected by the operating system.
		Create       = SQLITE_OPEN_CREATE,       //!< The database is opened for reading and writing, and is created if it does not already exist.
		Uri          = SQLITE_OPEN_URI,          //!< The filename can be interpreted as a URI if this flag is set.
		Memory       = SQLITE_OPEN_MEMORY,       //!< The database will be opened as an in-memory database.
		NoMutex      = SQLITE_OPEN_NOMUTEX,      //!< The new database connection will use the "multi-thread" threading mode.
		FullMutex    = SQLITE_OPEN_FULLMUTEX,    //!< The new database connection will use the "serialized" threading mode.
		SharedCache  = SQLITE_OPEN_SHAREDCACHE,  //!< The database is opened shared cache enabled, overriding the default shared cache setting provided by sqlite3_enable_shared_cache().
		PrivateCache = SQLITE_OPEN_PRIVATECACHE, //!< The database is opened shared cache disabled, overriding the default shared cache setting provided by sqlite3_enable_shared_cache().
		ExResCode    = SQLITE_OPEN_EXRESCODE,    //!< The database connection comes up in "extended result code mode".
		NoFollow     = SQLITE_OPEN_NOFOLLOW,     //!< The database filename is not allowed to contain a symbolic link
	};
}
namespace core::meta
{
	metadata bool Settings<bitwise_enum, data::ConnectionFlags> = true;
}
// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-o Class Declarations o-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o
namespace core::data
{
	class Connection 
	{	
		// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-o Types & Constants o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~o
	
		// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=o Representation o-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~o
	private:
		SharedDatabase  Handle;
		// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-o Construction & Destruction o=~-~=~-~=~-~=~-~=~-~=~-~=~-~o
	public:
		explicit
		Connection(SharedDatabase db) 
		  : Handle{ThrowIfEmpty(db)}
		{}
		// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o Copy & Move Semantics o-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~o
	public:
		satisfies(Connection,
			IsCopyable,
			IsMovable,
			NotEqualityComparable,
			NotSortable
		);
		// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=o Static Methods o-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~o
	public:
		Connection
		static open(std::string_view filename, nstd::bitset<ConnectionFlags> flags = ConnectionFlags::ReadWrite|ConnectionFlags::Create) {
			::sqlite3* handle{};
			if (auto r = ::sqlite3_open_v2(filename.data(), &handle, flags.value(), win::Unused<char const*>); r != SQLITE_OK)
				throw runtime_error{"sqlite3_open() failed: {}", sqlite3_errmsg(handle)};
			return Connection{SharedDatabase{handle}};
		}

	private:
		template <nstd::Integer Integer>
		Integer
		static convertTo(char const* value) {
			return static_cast<Integer>(::atoll(value));
		}
		
		template <nstd::FloatingPoint Decimal>
		Decimal
		static convertTo(char const* value) {
			return static_cast<Decimal>(::atof(value));
		}

		template <nstd::Stringish Stringish>
			requires nstd::AnyOf<Stringish, char const*, std::string>
		Stringish
		static convertTo(char const* value) {
			return Stringish{value};
		}

		template <typename... Results, size_t... Idx>
			requires nstd::AtLeastOneType<Results...>
		std::tuple<Results...>
		static tupleFromStringArray(char* values[], std::index_sequence<Idx...>) {
			return std::make_tuple<Results...>(Connection::convertTo<Results>(values[Idx])...);
		}
		// o~=~-~=~-~=~-~=~-~=~-~=~-~=~o Observer Methods & Operators o~-~=~-~=~-~=~-~=~-~=~-~=~-~o
	public:
		void
		execute(std::string_view statement) const {
			char* errmsg{};
			if (auto r = ::sqlite3_exec(*this->Handle, statement.data(), nullptr, nullptr, &errmsg); r != SQLITE_OK) {
				final_act(errmsg) noexcept { ::sqlite3_free(errmsg); };
				throw runtime_error{"sqlite3_exec() failed: {}", errmsg};
			}
		}
		
		template <typename... Results>
			requires nstd::AtLeastOneType<Results...>
		std::vector<std::tuple<Results...>>
		execute(std::string_view statement) const {
			using ResultTuple = std::tuple<Results...>;

			auto const
			tupleFromResult = [](void* param, int numColumns, char* values[], char* columns[]) -> int {
				if (numColumns != sizeof...(Results))
					return SQLITE_ERROR;

				auto& results = *static_cast<std::vector<ResultTuple>*>(param);
				results.push_back(Connection::tupleFromStringArray<Results...>(values, std::make_index_sequence<sizeof...(Results)>{}));
				return SQLITE_OK;
			};

			char*                    msg{};
			std::vector<ResultTuple> rows{};
			if (auto r = ::sqlite3_exec(*this->Handle, statement.data(), tupleFromResult, &rows, &msg); r != SQLITE_OK) {
				final_act(msg) noexcept { ::sqlite3_free(msg); };
				throw runtime_error{"sqlite3_exec() failed: {}", msg};
			}
			return rows;
		}
		// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-o Mutator Methods & Operators o~-~=~-~=~-~=~-~=~-~=~-~=~-~o
	};
}
// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-o Non-member Methods o-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o

// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~o Global Functions o~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o

// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=-~o Test Code o~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o

// o~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=-o End of File o-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~-~=~o