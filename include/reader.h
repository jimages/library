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
#include <string>
#include <list>
#include <type_traits>
#include "book.h"
#include "model.h"
class Reader: public Model{
	int id;
	std::string _name;
	std::string _num;	
	std::list<Book> _rent;
	std::string _password;
	
	
	bool reset(const std::string &p) {
		_password = p;
		return true;
	}
public:
	// Constructor
	Reader() = default;
	Reader(const std::string &name, const std::string &num, 
		const std::string password): _name(name), _num(num), _password(password){}
	Reader &operator=(const Reader &reader) = default;

	// bind the readonly var to private var.
	std::add_const<decltype((_name))>::type name = _name;
	std::add_const<decltype((_num))>::type num = _num;
	std::add_const<decltype((_rent))>::type rent = _rent;


};
#endif // JI_READER_CLASS

