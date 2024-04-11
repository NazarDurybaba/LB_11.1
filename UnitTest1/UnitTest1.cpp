#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_11.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestProcessBIN1)
        {
            // Arrange
            const std::string testData = "abc123def456";
            const char* testInputFileName = "testfile_input.bin";
            const char* testOutputFileName = "testfile_output.bin";

            // Create test input file
            std::ofstream testInputFile(testInputFileName, std::ios::binary);
            testInputFile.write(testData.c_str(), testData.size());
            testInputFile.close();

            // Act
            ProcessBIN1(testInputFileName, testOutputFileName);

            // Assert
            std::ifstream testOutputFile(testOutputFileName, std::ios::binary);
            std::stringstream buffer;
            buffer << testOutputFile.rdbuf();
            std::string output = buffer.str();
            Assert::AreEqual(std::string("abcdef"), output);
        }

        TEST_METHOD(TestSortBIN)
        {
            // Arrange
            const std::string testData = "cba";
            const char* testFileName = "testfile_sort.bin";

            // Create test input file
            std::ofstream testFile(testFileName, std::ios::binary);
            testFile.write(testData.c_str(), testData.size());
            testFile.close();

            // Act
            SortBIN(testFileName);

            // Assert
            std::ifstream testOutputFile(testFileName, std::ios::binary);
            std::stringstream buffer;
            buffer << testOutputFile.rdbuf();
            std::string output = buffer.str();
            Assert::AreEqual(std::string("abc"), output);
        }
	};
}
