#include "pch.h"
#include "CppUnitTest.h"
#include "../Fuzzy2D/RigidBody.h"
#include "../Fuzzy2D/CollisionResponse.h"
#include "../Fuzzy2D/CollisionResponse.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace  PhysicsTests
{
	TEST_CLASS(CollisionResponseTests)
	{
	public:
		CollisionResponseTests()
		{
			
		}
		TEST_METHOD(Test_101_CalculateResultingImpulseVelocity_Negative_PartialBounce)
		{
			RigidBody rigidBodyA;
			rigidBodyA.SetInputVelocity(Vector2(5, 0));
			rigidBodyA.SetInvertedMass(0.1);
			rigidBodyA.SetElasticityCoefficient(1);

			RigidBody rigidBodyB;
			rigidBodyB.SetInputVelocity(Vector2(-3, 0));
			rigidBodyB.SetInvertedMass(0.1);
			rigidBodyB.SetElasticityCoefficient(1);

			const Vector2 collisionNormal(1, 0);

			const Vector2 collisionVelocity = CollisionResponse::CalculateResultingImpulseVelocity(rigidBodyA, rigidBodyB, collisionNormal);

			Assert::IsTrue(CommonHelpers::AreEqual(collisionVelocity, Vector2(-8, 0)));
		}

		TEST_METHOD(Test_102_CalculateResultingImpulseVelocity_ZeroInvertedMass_NoBounce)
		{
			RigidBody rigidBodyA;
			rigidBodyA.SetInputVelocity(Vector2(5, 0));
			rigidBodyA.SetInvertedMass(0);
			rigidBodyA.SetElasticityCoefficient(1);

			RigidBody rigidBodyB;
			rigidBodyB.SetInputVelocity(Vector2(-30, 0));
			rigidBodyB.SetInvertedMass(0.5);
			rigidBodyB.SetElasticityCoefficient(1);

			const Vector2 collisionNormal(1, 0);

			const Vector2 collisionVelocity = CollisionResponse::CalculateResultingImpulseVelocity(rigidBodyA, rigidBodyB, collisionNormal);

			Assert::IsTrue(CommonHelpers::AreEqual(collisionVelocity, Vector2(0, 0)));
		}

		TEST_METHOD(Test_103_CalculateResultingImpulseVelocity_Negative_PerfectBounce)
		{
			RigidBody rigidBodyA;
			rigidBodyA.SetInputVelocity(Vector2(5, 0));
			rigidBodyA.SetInvertedMass(0.1);
			rigidBodyA.SetElasticityCoefficient(1);

			RigidBody rigidBodyB;
			rigidBodyB.SetInputVelocity(Vector2(0, 0));
			rigidBodyB.SetInvertedMass(0);
			rigidBodyB.SetElasticityCoefficient(0);

			const Vector2 collisionNormal(1, 0);

			const Vector2 collisionVelocity = CollisionResponse::CalculateResultingImpulseVelocity(rigidBodyA, rigidBodyB, collisionNormal);

			Assert::IsTrue(CommonHelpers::AreEqual(collisionVelocity, Vector2(-10, 0)));
		}

		TEST_METHOD(Test_104_CalculateResultingImpulseVelocity_Negative_PerfectXBounce_YVelocityUnchanged)
		{
			RigidBody rigidBodyA;
			rigidBodyA.SetInputVelocity(Vector2(5, 10));
			rigidBodyA.SetInvertedMass(0.1);
			rigidBodyA.SetElasticityCoefficient(1);

			RigidBody rigidBodyB;
			rigidBodyB.SetInputVelocity(Vector2(0, 0));
			rigidBodyB.SetInvertedMass(0);
			rigidBodyB.SetElasticityCoefficient(0);

			const Vector2 collisionNormal(1, 0);

			const Vector2 collisionVelocity = CollisionResponse::CalculateResultingImpulseVelocity(rigidBodyA, rigidBodyB, collisionNormal);

			Assert::IsTrue(CommonHelpers::AreEqual(collisionVelocity, Vector2(-10, 0)));
		}

		TEST_METHOD(Test_105_CalculateResultingImpulseVelocity_Negative_PartialBounce)
		{
			RigidBody rigidBodyA;
			rigidBodyA.SetInputVelocity(Vector2(5, 0));
			rigidBodyA.SetInvertedMass(0.1);
			rigidBodyA.SetElasticityCoefficient(0.5);

			RigidBody rigidBodyB;
			rigidBodyB.SetInputVelocity(Vector2(-3, 0));
			rigidBodyB.SetInvertedMass(0.1);
			rigidBodyB.SetElasticityCoefficient(1);

			const Vector2 collisionNormal(1, 0);

			const Vector2 collisionVelocity = CollisionResponse::CalculateResultingImpulseVelocity(rigidBodyA, rigidBodyB, collisionNormal);

			Assert::IsTrue(CommonHelpers::AreEqual(collisionVelocity, Vector2(-6, 0)));
		}

		TEST_METHOD(Test_106_CalculateResultingImpulseVelocity_CollisionAngleTooLarge_NoBounce)
		{
			RigidBody rigidBodyA;
			rigidBodyA.SetInputVelocity(Vector2(5, 0));
			rigidBodyA.SetInvertedMass(0.1);
			rigidBodyA.SetElasticityCoefficient(0.5);

			RigidBody rigidBodyB;
			rigidBodyB.SetInputVelocity(Vector2(-3, 0));
			rigidBodyB.SetInvertedMass(0.1);
			rigidBodyB.SetElasticityCoefficient(1);

			const Vector2 collisionNormal(-5, 0);

			const Vector2 collisionVelocity = CollisionResponse::CalculateResultingImpulseVelocity(rigidBodyA, rigidBodyB, collisionNormal);

			Assert::IsTrue(CommonHelpers::AreEqual(collisionVelocity, Vector2(0, 0)));
		}

	private:
	};
}
