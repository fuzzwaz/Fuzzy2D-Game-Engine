#include "pch.h"
#include "CppUnitTest.h"
#include "../Fuzzy2D/RigidBody.h"
#include "../Fuzzy2D/Common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PhysicsTests
{
	TEST_CLASS(RigidBodyTests)
	{
	public:
		RigidBodyTests() {}

		TEST_METHOD(Test_101_ApplyMovementForces_AccelerateToMaxSpeed_VelocityMagnitudeMatchesSpeed)
		{
			RigidBody testRB;
			testRB.SetAcceleration(Vector2(6000, 0));
			testRB.ApplyMovementForces(50);

			const float maxSpeed = testRB.GetSpeed();
			const float velocityMagnitude = testRB.GetVelocity().Magnitude();

			Assert::IsTrue(CommonHelpers::AreEqual(maxSpeed, velocityMagnitude));
		}

		TEST_METHOD(Test_102_ApplyMovementForces_AccelerateToMaxSpeed_StopAccelerating_VelocityMagnitudeDoesNotMatcheSpeed)
		{
			RigidBody testRB;
			testRB.SetAcceleration(Vector2(6000, 0));
			testRB.ApplyMovementForces(50);
			testRB.SetAcceleration(Vector2(0, 0));
			testRB.ApplyMovementForces(1);

			const float maxSpeed = testRB.GetSpeed();
			const float velocityMagnitude = testRB.GetVelocity().Magnitude();

			Assert::IsFalse(CommonHelpers::AreEqual(maxSpeed, velocityMagnitude));
		}

		TEST_METHOD(Test_103_ApplyMovementForces_NoDecleration_AccelerateToMaxSpeed_StopAccelerating_VelocityMagnitudeMatchesSpeed)
		{
			RigidBody testRB;
			testRB.SetAcceleration(Vector2(6000, 0));
			testRB.SetDecelerationSpeed(0);
			testRB.ApplyMovementForces(50);
			testRB.SetAcceleration(Vector2(0, 0));
			testRB.ApplyMovementForces(1);

			const float maxSpeed = testRB.GetSpeed();
			const float velocityMagnitude = testRB.GetVelocity().Magnitude();

			Assert::IsTrue(CommonHelpers::AreEqual(maxSpeed, velocityMagnitude));
		}
		TEST_METHOD(Test_104_ApplyMovementForces_NoDecleration_ImpulseVelocity_VelocityInstantlyMatchesSpeed)
		{
			RigidBody testRB;
			testRB.SetDecelerationSpeed(0);
			testRB.AddImpulseVelocity(Vector2(500, 0));
			testRB.ApplyMovementForces(1);

			const float expectedSpeed = 500;
			const float velocityMagnitude = testRB.GetVelocity().Magnitude();

			Assert::IsTrue(CommonHelpers::AreEqual(expectedSpeed, velocityMagnitude));
		}

		TEST_METHOD(Test_105_ApplyMovementForces_ImpulseVelocity_ImpulseVelocityDeceleratesOverTime)
		{
			RigidBody testRB;
			testRB.AddImpulseVelocity(Vector2(500, 0));
			testRB.ApplyMovementForces(100);

			const float expectedSpeed = 0;
			const float velocityMagnitude = testRB.GetVelocity().Magnitude();

			Assert::IsTrue(CommonHelpers::AreEqual(expectedSpeed, velocityMagnitude));
		}

	private:
	};
}
