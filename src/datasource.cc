/*
 * Author: Jimages (jimages123@gmail.com)
 * Date: June 22 2018
 * Des:
 * 	The loader of books and readers.
 */
#include "model/book.hpp"
#include "model/reader.hpp"
#include "model/dat_source.hpp"
#include "model/sqlite.hpp"
#include <string>
#include <vector>
#include <type_traits>
#include <boost/format.hpp>
#include <iostream>
#include <list>
#include <fstream>
#include <memory>
#include <utility>
#include <vector>
#include <stdexcept>
#include <string>

bool DatSource::CreateTable()
{
	return dat.exec_all(CREATE_SQL);
}
int DatSource::set_manage_password(std::string password)
{
	std::fstream f("pass", f.out);
	f << password;
	f.close();
	return 0;
}
int DatSource::rent_book(const Reader &r, const Book &b)
{
	dat.exec_one(boost::str(boost::format(
					"INSERT INTO rent (book_id, reader_id) VALUES (%1%, %2%);")
					% b.id
					% r.id
					));
	return 0;
}
int DatSource::back_book(const Reader &r, const Book &b)
	{
		dat.exec_one(boost::str(boost::format(
						"UPDATE rent SET is_back = 1 WHERE book_id = %1% and reader_id = %2%;")
						% b.id
						% r.id
						));
		return 0;
	}
std::vector<Book> DatSource::lookup(const Reader &r)
{
	auto re = dat.exec_one(boost::str(boost::format(
					"SELECT * from book inner join rent r on r.book_id = book.id where r.reader_id = %1% and is_back = 0")
				% r.id));
	std::vector<Book> res;
	for (auto i : re.second)
	{
		res.emplace_back(i[1], i[2]);
		res.back().id = std::stoi(i[0]);
	}
	return res;
}
// 插入新的读者的重载函数
int DatSource::insert(const Reader &b)
{
	if (b.id != b.nid)
		throw std::runtime_error("it shall not have id");
	std::string sql = boost::str(boost::format(
			"INSERT INTO reader (name, password, num) VALUES"
			"(\"%1%\", \"%2%\", \"%3%\");")
				% b.name
				% b.password
				% b.num);
	return dat.exec_one(sql).first;
}
// 根据id来更新读者的关系
int DatSource::update(const Reader &r)
{
	if (r.id == r.nid)
		throw std::runtime_error("No id found.");
	std::string sql = boost::str(boost::format(
		"UPDATE reader SET "
		"name = \"%1%\"," 
		"password = \"%2%\" ,"
		"num= \"%3%\" where id = %4%;"
		)
		% r.name
			% r.password
			% r.num
			% r.id
	);
	auto re = dat.exec_one(sql);
	return re.first;
}
int DatSource::remove(const Reader &r)
{
	if (r.id == r.nid)
		throw std::runtime_error("No id found.");
	std::string sql = boost::str(boost::format(
			"DELETE FROM reader "
			"where id = %1%;"
		)
			% r.id
	);
	auto re = dat.exec_one(sql);
	return re.first;

}
// 根据用户num获得用户
std::vector<Reader> DatSource::get_reader_by_num(const std::string &num)
{
	std::string sql = boost::str(boost::format(
			"SELECT * FROM reader "
			"where num = '%1%';"
		)
			% num
	);
	auto re = dat.exec_one(sql);
	std::vector<Reader> result;
	for (auto &user :re.second) {
	Reader r(user[1],
		 user[2],
		 user[3]);
	r.id = std::stoi(user[0]);
	result.push_back(r);
	}

	return result;
}

// 插入新的图书的重载函数
int DatSource::insert(const Book &b)
{
	if (b.id != b.nid)
		throw std::runtime_error("It shall not have id.");
	std::string sql = boost::str(boost::format(
			"INSERT INTO book (name, ind) VALUES"
			"(\"%1%\",\"%2%\");")
				% b.name
				% b.index);
	return dat.exec_one(sql).first;
}
// 根据id来更新书籍的信息
int DatSource::update(const Book &b)
{
	if (b.id == b.nid)
		throw std::runtime_error("No id found.");
	std::string sql = boost::str(boost::format(
			"UPDATE book SET "
			"name = \"%1%\"," 
			"ind = \"%2%\" where id = %3%;"
		)
			% b.name
			% b.index
			% b.id
	);
	auto re = dat.exec_one(sql);
	return re.first;
}
int DatSource::remove(const Book &b)
{
	if (b.id == b.nid)
		throw std::runtime_error("No id found.");
	std::string sql = boost::str(boost::format(
			"DELETE FROM book "
			"where id = %1%;"
		)
			% b.id
	);
	auto re = dat.exec_one(sql);
	return re.first;
}
// 根据索引号获得书籍对象
std::vector<Book> DatSource::get_book_by_index(const std::string &index)
{
	std::string sql = boost::str(boost::format(
			"SELECT * FROM book "
			"where ind = '%1%';"
		)
			% index
	);
	auto re = dat.exec_one(sql);
	std::vector<Book> r;
	for (auto i : re.second)
	{
		r.emplace_back(i[1], i[2]);
		r.back().id = std::stoi(i[0]);
	}
	return r;
}
std::vector<Book> DatSource::get_book_by_name(const std::string &index)
{
	std::string sql = boost::str(boost::format(
			"SELECT * FROM book "
			"where name = \"%1%\";"
		)
			% index
	);
	auto re = dat.exec_one(sql);
	std::vector<Book> r;
	for (auto i : re.second)
	{
		r.emplace_back(i[1], i[2]);
		r.back().id = std::stoi(i[0]);
	}
	return r;
}
