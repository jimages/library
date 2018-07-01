#ifndef _DATASOURCE_CLASS_
#define _DATASOURCE_CLASS_
/*
 * Author: Jimages (jimages123@gmail.com)
 * Date: June 22 2018
 * Des:
 * 	The loader of books and readers.
 */
#include "model/sqlite.hpp"
#include <string>
#include <vector>
#include <string>

#define SQL(...) #__VA_ARGS__

#define DAT_FILE "data.db"
class Book;
class Reader;

class DatSource {
	Sqlite &dat;
	static constexpr const char *CREATE_SQL = SQL(
		CREATE TABLE IF NOT EXISTS main.book (
		   id INTEGER PRIMARY KEY AUTOINCREMENT ,
		  name VARCHAR(50)  NOT NULL,
		  ind VARCHAR(50) NOT NULL
		);

		CREATE TABLE IF NOT EXISTS main.reader (
		  id INTEGER PRIMARY KEY AUTOINCREMENT ,
		  name VARCHAR(50)  NOT NULL,
		  password VARCHAR(50) NOT NULL,
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
	bool CreateTable();
public:
	DatSource(): dat(Sqlite::getInstance())
	{
		CreateTable();
	}
	~DatSource()
	{
	}

	DatSource &operator=(const DatSource &a) = default;
	// 插入新的图书和读者的重载函数
	int insert(const Book &b);
	int insert(const Reader &r);
	
	// 根据id来更新用户和书籍的信息
	int update(const Reader &r);
	int update(const Book &b);
	
	// 根据id来删除书籍的信息
	int remove(const Reader &r);
	int remove(const Book &b);

	// 根据用户num获得用户
	std::vector<Reader> get_reader_by_num(const std::string &num);
	
	// 根据索引号获得书籍对象
	std::vector<Book> get_book_by_index(const std::string &index);
	std::vector<Book> get_book_by_name(const std::string &name);
	
	
	int rent_book(const Reader &r, const Book &b);
	int back_book(const Reader &r, const Book &b);
	std::vector<Book> lookup(const Reader &r);
	int set_manage_password(std::string password);


};
#endif
