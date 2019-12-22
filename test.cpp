#include "../Terminal/System.cpp"
#include "../Terminal/Node.cpp"
#include "../Terminal/File.cpp"
#include "../Terminal/Dir.cpp"
#include "pch.h"

TEST(Terminal, sameParentTest) {
	Dir d1("dir1",nullptr);
	Dir d2("dir2", nullptr);

	EXPECT_EQ(d1.getParent(),d2.getParent());
}

TEST(Terminal, alreadyExistsTest) {
	System s1;
	s1.mkdir("dir1");

	EXPECT_TRUE(s1.alreadyExists("dir1"));
}

TEST(Terminal, hasChildrenTest) {
	System s1;
	
	Dir d1("dir1", nullptr);

	EXPECT_FALSE(s1.hasChildren(&d1));
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}