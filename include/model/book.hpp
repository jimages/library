/*
 * the management system of library Under MIT License see the license 
 * in the root directory.
 */

/*
 * Author: jimgaes123@gmail.com 2018(c)
 * the Book class.
 */
#ifndef _BOOK_CLASS_
#define _BOOK_CLASS_
#include <iostream>
#include <climits>
#include <cstdint>
#include <string>
class Reader;
class Book {
public:
	const int nid = INT_MAX;
private:
	friend class DatSource;
public:
	// Constructor
	Book() = default;
	Book(const std::string &name, const std::string &index): 
		name(name), index(index) {}
	Book &operator=(const Book &book);

public:
	int id = INT_MAX;
	std::string name;
	std::string index;
	friend std::ostream &operator<< (std::ostream &out, const Book &b);
};
inline std::ostream &operator<< (std::ostream &out, const Book &b)
{
	out << b.name << " " << b.index << std::endl;
	return out;
}
#endif
