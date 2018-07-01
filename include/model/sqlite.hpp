#ifndef LI_SQLITE_CLASS_H_
#define LI_SQLITE_CLASS_H_
#include "sqlite3.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <iostream>
class Sqlite {
	sqlite3 *con;
	static Sqlite *sql;
public:
	using QueryR = std::pair<int , std::list<std::vector<std::string>>>;
	int exec_all(const std::string &sql,
			int (*callback)(void*,int,char**,char**) = nullptr,
			void *arg = nullptr);
	static Sqlite &getInstance()
	{
		if (!sql) sql = new Sqlite();
		return *sql;
	}
	QueryR exec_one(const std::string &sql);
private:
	explicit Sqlite(std::string filepath = "data.db")
	{
		if(SQLITE_OK != sqlite3_open(filepath.c_str() , &con))
			throw std::runtime_error(sqlite3_errmsg(con));
	}
	virtual ~Sqlite() throw(std::runtime_error)
	{
		if(SQLITE_OK != sqlite3_close(con))
			throw std::runtime_error(sqlite3_errmsg(con));
	}
	Sqlite &operator=(const Sqlite &o) = default;
};
#endif // LI_MODEL_CLASS_H_
