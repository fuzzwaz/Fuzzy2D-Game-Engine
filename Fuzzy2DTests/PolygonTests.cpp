#include "pch.h"
#include "CppUnitTest.h"
#include "../Fuzzy2D/Polygon.h"
#include "../Fuzzy2D/Common.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PhysicsTests
{
	TEST_CLASS(PolygonTests)
	{
	public:
		PolygonTests()
		{
			_polygonA.AddVertexPoint({ Vector2(1,0), Vector2(0,1), Vector2(-1, 0), Vector2(0,-1) });
		}

		TEST_METHOD(Test_101_Rotate_45_Degrees)
		{
			Polygon testPolygon = _polygonA;
			testPolygon.Rotate(45);

			const auto vertices = testPolygon.GetVertices();
			
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(0), Vector2(0.707, 0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(1), Vector2(-0.707, 0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(2), Vector2(-0.707, -0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(3), Vector2(0.707, -0.707)));
			
			Assert::IsTrue(true);
		}

		TEST_METHOD(Test_102_Rotate_n45_Degrees)
		{
			Polygon testPolygon = _polygonA;
			testPolygon.Rotate(-45);

			const auto vertices = testPolygon.GetVertices();
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(0), Vector2(0.707, -0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(1), Vector2(0.707, 0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(2), Vector2(-0.707, 0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(3), Vector2(-0.707, -0.707)));
		}

		TEST_METHOD(Test_103_Rotate_90_Degrees)
		{
			Polygon testPolygon = _polygonA;
			testPolygon.Rotate(90);

			const auto vertices = testPolygon.GetVertices();
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(0), Vector2(0, 1)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(1), Vector2(-1, 0)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(2), Vector2(0, -1)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(3), Vector2(1, 0)));
		}

		TEST_METHOD(Test_104_Rotate_n90_Degrees)
		{
			Polygon testPolygon = _polygonA;
			testPolygon.Rotate(-90);

			const auto vertices = testPolygon.GetVertices();
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(0), Vector2(0, -1)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(1), Vector2(1, 0)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(2), Vector2(0, 1)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(3), Vector2(-1, 0)));
		}

		TEST_METHOD(Test_105_Rotate_360_Degrees)
		{
			Polygon testPolygon = _polygonA;
			testPolygon.Rotate(360);

			const auto vertices = testPolygon.GetVertices();
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(0), Vector2(1, 0)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(1), Vector2(0, 1)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(2), Vector2(-1, 0)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(3), Vector2(0, -1)));
		}

		TEST_METHOD(Test_106_Rotate_225_Degrees)
		{
			Polygon testPolygon = _polygonA;
			testPolygon.Rotate(225);

			const auto vertices = testPolygon.GetVertices();
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(0), Vector2(-0.707, -0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(1), Vector2(0.707, -0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(2), Vector2(0.707, 0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(3), Vector2(-0.707, 0.707)));
		}

		TEST_METHOD(Test_107_180_RotatedPolygon_Rotate_45_Degrees)
		{
			Polygon testPolygon = _polygonA;
			testPolygon.Rotate(180);
			testPolygon.Rotate(45);

			const auto vertices = testPolygon.GetVertices();
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(0), Vector2(-0.707, -0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(1), Vector2(0.707, -0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(2), Vector2(0.707, 0.707)));
			Assert::IsTrue(CommonHelpers::AreEqual(vertices->at(3), Vector2(-0.707, 0.707)));
		}

		TEST_METHOD(Test_201_GetNumOfVertices_4_Vertices)
		{
			Polygon testPolygon = _polygonA;
			const int expectedNum = 4;
			const int actualNum = testPolygon.GetNumOfVertices();

			Assert::AreEqual(expectedNum, actualNum);
		}

		TEST_METHOD(Test_301_ClockwisePerpendicular_InputVector_Zero_Two_OutputVector_Two_Zero)
		{
			const Vector2 inputVector(0, 2);

			const Vector2 outputVector = ClockwisePerpendicularVector(inputVector);
			const Vector2 expectedResultVector(2, 0);

			Assert::IsTrue(outputVector == expectedResultVector);
		}

		TEST_METHOD(Test_302_CounterClockwisePerpendicular_InputVector_Zero_Two_OutputVector_nTwo_Zero)
		{
			const Vector2 inputVector(0, 2);

			const Vector2 outputVector = CounterClockwisePerpendicularVector(inputVector);
			const Vector2 expectedResultVector(-2, 0);

			Assert::IsTrue(outputVector == expectedResultVector);
		}

		TEST_METHOD(Test_303_ClockwisePerpendicular_InputVector_One_One_OutputVector_One_nOne)
		{
			const Vector2 inputVector(1, 1);

			const Vector2 outputVector = ClockwisePerpendicularVector(inputVector);
			const Vector2 expectedResultVector(1, -1);

			Assert::IsTrue(outputVector == expectedResultVector);
		}

		TEST_METHOD(Test_304_CounterClockwisePerpendicular_InputVector_One_One_OutputVector_nOne_One)
		{
			const Vector2 inputVector(1, 1);

			const Vector2 outputVector = CounterClockwisePerpendicularVector(inputVector);
			const Vector2 expectedResultVector(-1, 1);

			Assert::IsTrue(outputVector == expectedResultVector);
		}

		TEST_METHOD(Test_305_ClockwisePerpendicular_InputVector_Five_Zero_OutputVector_Zero_nFive)
		{
			const Vector2 inputVector(5, 0);

			const Vector2 outputVector = ClockwisePerpendicularVector(inputVector);
			const Vector2 expectedResultVector(0, -5);

			Assert::IsTrue(outputVector == expectedResultVector);
		}

		TEST_METHOD(Test_306_CounterClockwisePerpendicular_InputVector_Five_Zero_OutputVector_Zero_Five)
		{
			const Vector2 inputVector(5, 0);

			const Vector2 outputVector = CounterClockwisePerpendicularVector(inputVector);
			const Vector2 expectedResultVector(0, 5);

			Assert::IsTrue(outputVector == expectedResultVector);
		}

	private:
		Polygon _polygonA;
	};
}
