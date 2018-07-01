#include "model/sqlite3.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "model/sqlite.hpp"

Sqlite *Sqlite::sql;
int Sqlite::exec_all(const std::string &sql,
		int (*callback)(void*,int,char**,char**), void *arg) {
	char *errmsg = nullptr;
	try {
		if (con == nullptr)
			throw std::runtime_error("NO Database found.");
		if (SQLITE_OK != sqlite3_exec(con, sql.c_str(), 
						callback, arg, &errmsg))
			throw std::runtime_error(sqlite3_errmsg(con));
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		throw;
		return -1;
	}
	return 0;
}
Sqlite::QueryR Sqlite::exec_one(const std::string &sql)
{

	sqlite3_stmt *stmt = nullptr;
	char *errmsg = nullptr;
	std::list<std::vector<std::string>> re_sets;
	try {
		if (con == nullptr)
			throw std::runtime_error("NO Database found.");
		if ( SQLITE_OK != sqlite3_prepare_v2( con, sql.c_str(),
				-1, &stmt, nullptr))
			throw std::runtime_error(sqlite3_errmsg(con));
		if (SQLITE_OK != sqlite3_prepare_v2(con, sql.c_str(),
						   -1, &stmt, nullptr))
			throw std::runtime_error(sqlite3_errmsg(con));
		auto res = sqlite3_step(stmt);
		while (res == SQLITE_ROW) {
			auto count = sqlite3_column_count(stmt);
			std::vector<std::string> node;
			for (auto n = 0; n < count; ++n)
				 node.emplace_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, n)));
			re_sets.push_back(std::move(node));
			res = sqlite3_step(stmt);
		}
		if ( res == SQLITE_DONE)
			sqlite3_reset(stmt);
		else
			throw std::runtime_error(sqlite3_errmsg(con));
		if (SQLITE_OK != sqlite3_finalize(stmt))
			throw std::runtime_error(sqlite3_errmsg(con));
		return std::make_pair(0, std::move(re_sets));
	} catch (std::runtime_error &e) {
		sqlite3_finalize(stmt);
		sqlite3_free(errmsg);
		std::cerr << e.what() << std::endl;
		throw;
	}
}
