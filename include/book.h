/*
 * the management system of library Under MIT License see the license 
 * in the root directory.
 */

/*
 * Author: jimgaes123@gmail.com 2018(c)
 * the Book class.
 */
#ifndef JI_BOOK_CLASS
#define JI_BOOK_CLASS
#include <string>
#include <type_traits>
#include "model.h"
class Book : public Model {
	int id;
	std::string _name;
	std::string _index;
	int _volume = 0;
	int _available = 0;
	friend class DatSource;
public:
	// Constructor
	Book() = default;
	Book(const std::string &name, const std::string &index, int volume, int available): _name(name), _index(index), _volume(volume), _available(available) {}
	Book(const std::string &name, const std::string &index ): _name(name), _index(index) {}
	Book &operator=(const Book &book) = default;

	// bind the readonly var to private var.
	std::add_const<decltype((_name))>::type name = _name;
	std::add_const<decltype((_index))>::type index = _index;
	std::add_const<decltype((_volume))>::type volume= _volume;
	std::add_const<decltype((_available))>::type available = _available;
};
#endif // JI_BOOK_CLASS

