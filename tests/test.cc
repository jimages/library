#include "model/reader.hpp"
#include "model/book.hpp"
#include "model/dat_source.hpp"
#include "operator.hpp"
#include "gtest/gtest.h"
#include <string>
#include <cstdlib>

class DatSourceTest : public ::testing::Test {
protected:
	DatSource *ptr;
	std::string tmp;
	virtual void SetUp() {
		std::srand(std::time(nullptr));
		tmp = std::to_string(std::rand());
		ASSERT_NO_THROW(ptr = new DatSource());
	}
	virtual void TearDown() {
		delete ptr;
	}
};

TEST_F(DatSourceTest, Insert) 
{
	// Init
	EXPECT_NO_THROW({
		Book b(tmp,tmp);
		ptr->insert(b);
		});
	EXPECT_NO_THROW({
		Reader r(tmp,tmp,tmp);
		ptr->insert(r);
		});
}

TEST_F(DatSourceTest, Query)
{

	// Query
	EXPECT_EQ(ptr->get_book_by_index(tmp).size(), 1);
	EXPECT_GT(ptr->get_book_by_name(tmp).size(), 0);
	EXPECT_EQ(ptr->get_reader_by_num(tmp).size(), 1);
}
TEST_F(DatSourceTest, Update)
{
	// Update
	auto new_tmp = std::to_string(std::rand());
	auto b = ptr->get_book_by_index(tmp)[0];
	b.name = new_tmp;
	EXPECT_NO_THROW(ptr->update(b));
	EXPECT_EQ(ptr->get_book_by_name(new_tmp).size(), 1);

	auto r = ptr->get_reader_by_num(tmp)[0];
	r.name = new_tmp;
	EXPECT_NO_THROW(ptr->update(r));
	EXPECT_STREQ((ptr->get_reader_by_num(tmp))[0].name.c_str(), new_tmp.c_str());
}
TEST_F(DatSourceTest, Remove)
{
	auto b = ptr->get_book_by_index(tmp)[0];
	auto r = ptr->get_reader_by_num(tmp)[0];
	// remove
	EXPECT_NO_THROW(ptr->remove(b));
	EXPECT_EQ(ptr->get_book_by_name(tmp).size(), 0);
	EXPECT_NO_THROW(ptr->remove(r));
	EXPECT_EQ(ptr->get_book_by_name(tmp).size(), 0);
}
class Library: public ::testing::Test {
protected:
	DatSource *ptr;
	std::string tmp;
	virtual void SetUp() {
		std::srand(std::time(nullptr));
		tmp = std::to_string(std::rand());
		ASSERT_NO_THROW(ptr = new DatSource());
	}
	virtual void TearDown() {
		delete ptr;
	}
};

TEST_F(Library, RentAndBack)
{
	// Create a user.
	Reader r("Wang" + tmp, "12110" + tmp, "123");
	ptr->insert(r);

	// Create a book.
	Book b(tmp + "name", tmp + "index");
	ptr->insert(b);

	// We should get the id.
	auto nr = ptr->get_reader_by_num("12110" + tmp)[0];
	auto nb = ptr->get_book_by_index(tmp + "index")[0];
	ASSERT_NO_THROW(ptr->rent_book(nr, nb));
	EXPECT_EQ(ptr->lookup(nr).size(),1);
	ASSERT_NO_THROW(ptr->back_book(nr, nb));
	EXPECT_EQ(ptr->lookup(nr).size(),0);
}
	
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

