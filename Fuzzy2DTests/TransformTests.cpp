#include "pch.h"
#include "CppUnitTest.h"
#include "../Fuzzy2D/Physics/Transform.h"
#include "../Fuzzy2D/Transform.cpp"
#include "../Fuzzy2D/Vector2.cpp"
#include "../Fuzzy2D/RigidBody.cpp"
#include "../Fuzzy2D/Common.cpp"
#include "../Fuzzy2D/Collider.cpp"
#include "../Fuzzy2D/ErrorHandler.cpp"
#include "../Fuzzy2D/Polygon.cpp"
#include "../Fuzzy2D/NullRigidBody.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PhysicsTests
{
	TEST_CLASS(TransformTests)
	{
	public:
		TEST_METHOD(Test_101_SetOrientationAngle_45_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(45);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(0.707, -0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_102_SetOrientationAngle_90_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(90);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_103_SetOrientationAngle_0_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(0);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(0, -1);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_104_SetOrientationAngle_135_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(135);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(0.707, 0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_105_SetOrientationAngle_180_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(180);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(0, 1);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_106_SetOrientationAngle_225_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(225);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(-0.707, 0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_107_SetOrientationAngle_270_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(270);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(-1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_108_SetOrientationAngle_315_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(315);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(-0.707, -0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_109_SetOrientationAngle_360_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(360);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(0,-1);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_110_SetOrientationAngle_Negative_45_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(-45);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(-0.707, -0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_111_SetOrientationAngle_Negative_90_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(-90);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(-1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_112_SetOrientationAngle_Negative_225_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(-225);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(0.707, 0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_113_SetOrientationAngle_405_ForwardVectorRotatedSuccessfully)
		{
			Transform transform;
			transform.SetOrientationAngle(405);

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(0.707, -0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_201_SetForwardVector_45_OrientationRotatedSuccessfully)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(0.707,-0.707));

			const double resultingOrientation = transform.GetOrientationAngle();
			const double expectedOrientation = 45.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_202_SetForwardVector_90_OrientationRotatedSuccessfully)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(1, 0));

			const double resultingOrientation = transform.GetOrientationAngle();
			const double expectedOrientation = 90.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_203_SetForwardVector_135_OrientationRotatedSuccessfully)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(0.707, 0.707));

			const double resultingOrientation = transform.GetOrientationAngle();
			const double expectedOrientation = 135.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_204_SetForwardVector_180_OrientationRotatedSuccessfully)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(0, 1));

			const double resultingOrientation = transform.GetOrientationAngle();
			const double expectedOrientation = 180.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_205_SetForwardVector_225_OrientationRotatedSuccessfully)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(-0.707, 0.707));

			const double resultingOrientation = transform.GetOrientationAngle();
			const double expectedOrientation = -135.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_206_SetForwardVector_270_OrientationRotatedSuccessfully)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(-1, 0));

			const double resultingOrientation = transform.GetOrientationAngle();
			const double expectedOrientation = -90.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_207_SetForwardVector_315_OrientationRotatedSuccessfully)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(-0.707, -0.707));

			const double resultingOrientation = transform.GetOrientationAngle();
			const double expectedOrientation = -45.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_208_SetForwardVector_ZeroVector_ForwardVectorUnchanged)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(1, 0)); //Change the forward vector initially to have something to compare with

			transform.SetForwardVector(Vector2(0, 0));

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_209_SetForwardVector_ZeroVector_OrientationUnchanged)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(1, 0)); //Change the forward vector initially to have something to compare with

			transform.SetForwardVector(Vector2(0, 0));

			const double resultingOrientation = transform.GetOrientationAngle();
			const double expectedOrientation = 90.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_210_SetForwardVector_90_LargeMagnitude_ForwardVectorNormalizedAndSetSuccessfully)
		{
			Transform transform;
			transform.SetForwardVector(Vector2(20, 0));

			const Vector2 resultingForward = transform.GetForwardVector();
			const Vector2 expectedForward(1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_301_SetOrientationAngle_45_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(45);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(0.707, -0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_302_SetOrientationAngle_90_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(90);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_303_SetOrientationAngle_0_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(0);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(0, -1);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_304_SetOrientationAngle_135_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(135);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(0.707, 0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_305_SetOrientationAngle_180_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(180);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(0, 1);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_306_SetOrientationAngle_225_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(225);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(-0.707, 0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_307_SetOrientationAngle_270_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(270);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(-1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_308_SetOrientationAngle_315_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(315);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(-0.707, -0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_309_SetOrientationAngle_360_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(360);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(0, -1);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_310_SetOrientationAngle_Negative_45_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(-45);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(-0.707, -0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_311_SetOrientationAngle_Negative_90_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(-90);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(-1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_312_SetOrientationAngle_Negative_225_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(-225);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(0.707, 0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_313_SetOrientationAngle_405_ForwardVectorRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetOrientationAngle(405);

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(0.707, -0.707);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_401_SetForwardVector_45_OrientationRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(0.707, -0.707));

			const double resultingOrientation = testTransform.GetOrientationAngle();
			const double expectedOrientation = 45.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_402_SetForwardVector_90_OrientationRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(1, 0));

			const double resultingOrientation = testTransform.GetOrientationAngle();
			const double expectedOrientation = 90.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_403_SetForwardVector_135_OrientationRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(0.707, 0.707));

			const double resultingOrientation = testTransform.GetOrientationAngle();
			const double expectedOrientation = 135.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_404_SetForwardVector_180_OrientationRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(0, 1));

			const double resultingOrientation = testTransform.GetOrientationAngle();
			const double expectedOrientation = 180.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_405_SetForwardVector_225_OrientationRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(-0.707, 0.707));

			const double resultingOrientation = testTransform.GetOrientationAngle();
			const double expectedOrientation = -135.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_406_SetForwardVector_270_OrientationRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(-1, 0));

			const double resultingOrientation = testTransform.GetOrientationAngle();
			const double expectedOrientation = -90.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_407_SetForwardVector_315_OrientationRotatedSuccessfully)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(-0.707, -0.707));

			const double resultingOrientation = testTransform.GetOrientationAngle();
			const double expectedOrientation = -45.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_408_SetForwardVector_ZeroVector_ForwardVectorUnchanged)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(1, 0)); //Change the forward vector initially to have something to compare with

			testTransform.SetForwardVector(Vector2(0, 0));

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}

		TEST_METHOD(Test_409_SetForwardVector_ZeroVector_OrientationUnchanged)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(1, 0)); //Change the forward vector initially to have something to compare with

			testTransform.SetForwardVector(Vector2(0, 0));

			const double resultingOrientation = testTransform.GetOrientationAngle();
			const double expectedOrientation = 90.0;

			Assert::IsTrue(resultingOrientation == expectedOrientation);
		}

		TEST_METHOD(Test_410_SetForwardVector_90_LargeMagnitude_ForwardVectorNormalizedAndSetSuccessfully)
		{
			Transform testTransform;
			testTransform.SetForwardVector(Vector2(20, 0));

			const Vector2 resultingForward = testTransform.GetForwardVector();
			const Vector2 expectedForward(1, 0);

			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.x, expectedForward.x));
			Assert::IsTrue(CommonHelpers::AreEqual(resultingForward.y, expectedForward.y));
		}
	};
}