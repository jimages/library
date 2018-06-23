/*
 * Author: Jimages (jimages123@gmail.com)
 * Date: June 22 2018
 * Des:
 * 	The loader of books and readers.
 */
#ifndef LI_DATSOURCE_CLASS_H_
#define LI_DATSOURCE_CLASS_H_

#include "book.h"
#include "reader.h"
#include "sqlite3.h"
#include <boost/format.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>
#include <stdexcept>
#include <string>

#define SQL(...) #__VA_ARGS__

#define DAT_FILE "data.db"
class DatSource {
	using QueryR = std::pair<int , std::list<std::vector<std::string>>>;
	static constexpr const char *CREATE_SQL = SQL(
		CREATE TABLE IF NOT EXISTS main.book (
		   id INTEGER PRIMARY KEY AUTOINCREMENT ,
		  name VARCHAR(50)  NOT NULL,
		  ind VARCHAR(50) NOT NULL
		);

		CREATE TABLE IF NOT EXISTS main.reader (
		  id INTEGER PRIMARY KEY AUTOINCREMENT ,
		  name VARCHAR(50)  NOT NULL,
		  pasword VARCHAR(50) NOT NULL,
		  num VARCHAR(50)  NOT NULL
		);

		CREATE TABLE IF NOT EXISTS main.rent(
		  id INTEGER PRIMARY KEY AUTOINCREMENT,
		  book_id INT NOT NULL,
		  reader_id INT NOT NULL,
		  is_back INT DEFAULT FALSE,
		    FOREIGN KEY (reader_id) REFERENCES reader(id)
		      ON DELETE CASCADE ,
		    FOREIGN KEY (book_id) REFERENCES book(id)
		      ON DELETE CASCADE);
	);
	sqlite3 *con;
	bool CreateTable()
	{
		return exec_all(CREATE_SQL);
	}
	bool DatInit()
	{
		if(SQLITE_OK != sqlite3_open(DAT_FILE, &con)) {
			throw std::runtime_error(sqlite3_errmsg(con));
			return -1;
		}
		CreateTable();
		return 0;
	}
	int exec_all(const std::string &sql,
			int (*callback)(void*,int,char**,char**) = nullptr,
			void *arg = nullptr) {
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
		

	QueryR exec_one(const std::string &sql)
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
public:
	DatSource() 
	{
		DatInit();
	}

	~DatSource()
	{
		sqlite3_close(con);
	}

	int insert_book(const Book &b)
	{
		std::string sql = boost::str(boost::format(
				"INSERT INTO book (name, ind) VALUES"
				"(\"%1%\",\"%2%\");")
					% b.name
					% b.index);
		return exec_one(sql).first;
	}
	int update_book(const Book &b)
	{
		std::string sql = boost::str(boost::format(
				"UPDATE book SET "
				"name = \"%1%\"," 
				"ind = \"%2%\" where id = %3%;"
			)
				% b.name
				% b.index
				% b.id
		);
		auto re = exec_one(sql);
		return re.first;
	}
	/*
	int delete_book(const Book &b)
	{
	}
	int get_book(const Book &b)
	{
	}
	int get_reader(const Reader &r)
	{
	}
	int update_reader(const Reader &r)
	{
	}
	int delete_reader(const Reader &r)
	{
	}
	int rent_book(const Book &b, const Reader &r)
	{
	}
	int back_book(const Book &b)
	{
	}
	*/
};
#endif // LI_DATSOURCE_CLASS_H_
