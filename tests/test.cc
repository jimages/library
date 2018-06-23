#include "reader.h"
#include "book.h"
#include "datsource.h"
#include "gtest/gtest.h"

class DatSourceTest : public ::testing::Test {
protected:
	DatSource *ptr;
	virtual void SetUp() {
	}
};

TEST_F(DatSourceTest, Init) {
	ASSERT_NO_THROW(ptr = new DatSource());
}
TEST_F(DatSourceTest, Book) {
	EXPECT_NO_THROW({
		Book b("name","index");
		ptr->insert_book(b);
		});
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

