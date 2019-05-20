

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

#include "..\Transform\ProcessTransform.h"
#include <gtest\gtest.h>

class TransformTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_transform = std::make_unique< ProcessTransform>();
	}

	std::unique_ptr<ProcessTransform> _transform;

	void DisplayResult(const std::string& expected, const std::string& output)
	{
		std::cout << "Expected=>" << expected << " <--> Ouput=" << output << "\n";

		ASSERT_STREQ(expected.c_str(), output.c_str());
	}
};

TEST_F(TransformTest, key_transform_test1)
{
	const std::string input = "Hello";
	const std::vector<std::string> cmds = { "H", "V", "-1" };

	std::string result = _transform->Execute(input, cmds);

	DisplayResult("Hjqqa", result);
}

TEST_F(TransformTest, key_transform_test2)
{
	const std::string input = "Hello";
	const std::vector<std::string> cmds = { "H", "V", "V", "H" };

	std::string result = _transform->Execute(input, cmds);

	DisplayResult("Hello", result);
}

TEST_F(TransformTest, key_transform_test3)
{
	const std::string input = "Hello";
	const std::vector<std::string> cmds = { "1", "H", "V", "-5", "5", "H", "V", "-1" };

	std::string result = _transform->Execute(input, cmds);

	DisplayResult("Hello", result);
}

TEST_F(TransformTest, key_transform_test4)
{
	const std::string input = "Hello";
	const std::vector<std::string> cmds = { "60", "H", "V", "-45"};

	std::string result = _transform->Execute(input, cmds);
	
	DisplayResult("H3jjm", result);
}

TEST_F(TransformTest, key_transform_test5)
{
	const std::string input = "World hello";
	const std::vector<std::string> cmds = { "H", "V", "-1" };

	std::string result = _transform->Execute(input, cmds);

	DisplayResult("Wahqu rjqqa", result);
}

TEST_F(TransformTest, key_transform_test6)
{
	const std::string input = "World hello";
	const std::vector<std::string> cmds = { "1", "H", "V", "-5", "5", "H", "V", "-1" };

	std::string result = _transform->Execute(input, cmds);

	DisplayResult("World hello", result);
}

TEST_F(TransformTest, key_transform_test7)
{
	const std::string input = "World hello";
	const std::vector<std::string> cmds = { "60", "H", "V", "-45" };

	std::string result = _transform->Execute(input, cmds);

	DisplayResult("Wm2jc ;3jjm", result);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}