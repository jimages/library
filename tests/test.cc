#include "reader.h"
#include "book.h"
#include "datsource.h"
#include "gtest/gtest.h"

TEST(DatSource, Init) {
	ASSERT_NO_THROW(DatSource d);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

