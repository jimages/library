/*
 * Author: Jimages (jimages123@gmail.com)
 * Date: June 22 2018
 * Des:
 * 	The loader of books and readers.
 */
#ifndef LI_DATSOURCE_CLASS_H_
#define LI_DATSOURCE_CLASS_H_

#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include "book.h"
#include "reader.h"
#include "sqlite3.h"

#define SQL(...) #__VA_ARGS__

#define DAT_FILE "data.db"
class DatSource {
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
				return exec(CREATE_SQL);
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
	int exec(const std::string &sql)
	{
		char *errmsg = nullptr;
		try {
			if (con == nullptr)
				throw std::runtime_error("NO Database found.");
			sqlite3_exec(con, sql.c_str() ,NULL, NULL, &errmsg);
			if (errmsg)
				throw std::runtime_error(errmsg);
		} catch (std::runtime_error &e) {
			sqlite3_free(errmsg);
			std::cerr << e.what() << std::endl;
			throw;
		}
		return 0;
	}


public:
	DatSource() 
	{
		DatInit();
	}
	int insert_book(const Book &b)
	{
		std::string sql = boost::str(boost::format(
				"INSERT INTO book (name, ind) VALUES"
				"(\"%1%\",\"%2%\");")
					% b.name
					% b.index);
		return exec(sql);
	}
	/*
	int update_book(const Book &b)
	{
	}
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
