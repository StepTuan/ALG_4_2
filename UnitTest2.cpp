#include "pch.h"
#include "CppUnitTest.h"
#include"../ALG_4_2/Line.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(code)
		{
			string input = "hello friend";
			Line S(input);
			string expected = "1101111011011000111011001000111110010000";
			Assert::AreEqual(expected, S.get_code());
		}
		
		TEST_METHOD(compression_ratio)
		{
			string input = "aaabb";
			Line S(input);
			double a = 40;
			double b = 5;
			double expected = a / b;
			Assert::AreEqual(expected, S.get_compression_ratio());
		}
		
		TEST_METHOD(decode)
		{
			string input = "bbtestaa";
			Line S(input);
			string expected = input;
			Assert::AreEqual(expected, S.get_decode());
		}
	};
}
