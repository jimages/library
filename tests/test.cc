#include "reader.h"
#include "book.h"
#include "datsource.h"
#include "gtest/gtest.h"

TEST(DatSource, Init) {
	ASSERT_NO_THROW(DatSource d);
}
TEST(DatSource, Book) {
	DatSource data;
	Book b("name","index");
	EXPECT_NO_THROW(data.insert_book(b));
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

