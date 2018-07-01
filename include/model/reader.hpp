/*
 * the management system of library Under MIT License see the license 
 * in the root directory.
 */

/*
 * Author: jimgaes123@gmail.com 2018(c)
 * the reader class.
 */
#ifndef JI_READER_CLASS
#define JI_READER_CLASS
#include "model/sqlite.hpp"
#include <string>
#include <cstdint>
class Book;
class Reader {
public:
	// nid就是说不存在id
	const int nid = INT_MAX;
private:
	
	friend class DatSource;
	bool reset(const std::string &p) {
		password = p;
		return true;
	}
public:
	// Constructor
	Reader() = default;
	Reader(const std::string &name, const std::string &num, 
		const std::string &password): name(name), num(num), password(password){}
	Reader &operator=(const Reader &reader) = default;

	int id = nid;
	std::string name;
	std::string num;	
	std::list<Book> rent;
	std::string password;
};


#endif // JI_READER_CLASS

