#include "System.cpp"
#include "Node.cpp"
#include "File.cpp"
#include "Dir.cpp"
#include <gtest/gtest.h>

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

TEST(Terminal, hasChildrenFalseTest) {
	System s1;
	
	Dir d1("dir1", nullptr);

	EXPECT_FALSE(s1.hasChildren(&d1));
}

TEST(Terminal, hasChildrenTrueTest) {
	System s1;

	Dir* d1 = new Dir("a",nullptr);
	d1->addChild(new Dir("b",d1));

	EXPECT_TRUE(s1.hasChildren(d1));
}

TEST(Terminal, mkdirTestOutput) {
	System s;

	s.mkdir("a");
	s.mkdir("b");

	//test output
	testing::internal::CaptureStdout();
	s.ls("");
	std::string output = testing::internal::GetCapturedStdout();

	ASSERT_EQ("a/\nb/\n", output);
}
TEST(Terminal, mkdirTestVectorSize) {
	System s;

	s.mkdir("a");
	s.mkdir("b");

	int size = s.getCurrentFolder()->getChildren().size();

	//test children vector size
	ASSERT_EQ(2,size);
}
TEST(Terminal, mkdirTestElementTest) {
	System s;

	s.mkdir("a");
	s.mkdir("b");

	//test parent folder is root
	for (auto &d : s.getCurrentFolder()->getChildren()) {
		ASSERT_EQ("root", d->getParent()->getName());
		ASSERT_EQ(s.getCurrentFolder(), d->getParent());
	}
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
