#include "pch.h"
#include "CppUnitTest.h"
#include "../Fuzzy2D/Vector2.h"
#include "../Fuzzy2D/RigidBody.h"
#include "../Fuzzy2D/Collider.h"
#include "../Fuzzy2D/CollisionManager.h"
#include "../Fuzzy2D/CollisionManager.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PhysicsTests
{
	TEST_CLASS(CollisionManagerTests)
	{
	public:
		CollisionManagerTests()
		{
			_rigidBodyA.SetInputVelocity(Vector2(5, 0));
			_rigidBodyA.SetInvertedMass(0.1);
			_rigidBodyA.SetElasticityCoefficient(1);

			_rigidBodyB.SetInputVelocity(Vector2(-3, 0));
			_rigidBodyB.SetInvertedMass(0.1);
			_rigidBodyB.SetElasticityCoefficient(1);

			_colliderA.SetAssociatedRigidBody(&_rigidBodyA);
			_colliderA.SetPosition(_origin);
			_colliderA._Polygon.AddVertexPoint({ Vector2(2, 8), Vector2(5, 0), Vector2(10, 8), Vector2(5, 16) });
			_colliderD.SetColliderType(ColliderType::PLAYER);

			_colliderB.SetAssociatedRigidBody(&_rigidBodyB);
			_colliderB.SetPosition(_origin);
			_colliderB._Polygon.AddVertexPoint({ Vector2(1, 1), Vector2(3, 1), Vector2(1, 3), Vector2(3, 3) });

			_colliderC.SetAssociatedRigidBody(&_rigidBodyB);
			_colliderC.SetPosition(_origin);
			_colliderC._Polygon.AddVertexPoint({ Vector2(10, 1), Vector2(11, 3), Vector2(9, 3) });

			_colliderD.SetAssociatedRigidBody(&_rigidBodyB);
			_colliderD.SetPosition(_origin);
			_colliderD._Polygon.AddVertexPoint({ Vector2(7, 9), Vector2(10, 10), Vector2(8, 13) });
			_colliderD.SetColliderType(ColliderType::ENEMY);
		}

		TEST_METHOD(Test_101_SimulateCurrentCollisions_ThreeOtherColliders_SingleCollision)
		{
			CollisionManager collisionManager;
			Collider aCopy = _colliderA, bCopy = _colliderB, cCopy = _colliderC, dCopy = _colliderD;

			collisionManager.AddCollider(&aCopy); //Colliding with D
			collisionManager.AddCollider(&bCopy);
			collisionManager.AddCollider(&cCopy);
			collisionManager.AddCollider(&dCopy); //Colliding with A

			collisionManager.SimulateCurrentCollisions();

			Assert::IsTrue(aCopy.GetCollisionResponseInfo()._IsColliding);
			Assert::IsTrue(aCopy.GetCollisionResponseInfo()._Batons.size() == 1);
			Assert::IsTrue(aCopy.GetCollisionResponseInfo()._Batons.at(0)._Type == ColliderType::ENEMY);
			Assert::IsTrue(CommonHelpers::AreEqual(aCopy.GetCollisionResponseInfo()._ImpulseVector, Vector2(-3.01, -3.87)));
		}

		TEST_METHOD(Test_102_SimulateCurrentCollisions_ThreeOtherColliders_SingleCollision_IgnoresColliderType)
		{
			CollisionManager collisionManager;
			Collider aCopy = _colliderA, bCopy = _colliderB, cCopy = _colliderC, dCopy = _colliderD;
			aCopy.SetColliderIgnoreTypes({ColliderType::ENEMY});

			collisionManager.AddCollider(&aCopy); //Colliding with D, but ignoring Enemies
			collisionManager.AddCollider(&bCopy);
			collisionManager.AddCollider(&cCopy);
			collisionManager.AddCollider(&dCopy); //Colliding with A

			collisionManager.SimulateCurrentCollisions();

			Assert::IsFalse(aCopy.GetCollisionResponseInfo()._IsColliding);
		}

		TEST_METHOD(Test_103_SimulateCurrentCollisions_ThreeOtherColliders_SingleCollision_IgnoresSelf)
		{
			CollisionManager collisionManager;
			Collider aCopy = _colliderA, bCopy = _colliderB;

			collisionManager.AddCollider(&aCopy);
			collisionManager.AddCollider(&bCopy);
			collisionManager.AddCollider(&aCopy);
			collisionManager.AddCollider(&aCopy);

			collisionManager.SimulateCurrentCollisions();

			Assert::IsFalse(aCopy.GetCollisionResponseInfo()._IsColliding);
		}

		TEST_METHOD(Test_104_SimulateCurrentCollisions_StaticCollider_ThreeOtherColliders_SingleCollision_NoImpulseResponseForOne)
		{
			CollisionManager collisionManager;
			Collider aCopy = _colliderA, bCopy = _colliderB, cCopy = _colliderC, dCopy = _colliderD;
			aCopy.SetIsStatic(true);

			RigidBody dBody = _rigidBodyB;
			dBody.SetInputVelocity(Vector2(0, 20));
			dCopy.SetAssociatedRigidBody(&dBody);

			collisionManager.AddCollider(&aCopy); //Colliding with D but is Static
			collisionManager.AddCollider(&bCopy);
			collisionManager.AddCollider(&cCopy);
			collisionManager.AddCollider(&dCopy); //Colliding with A

			collisionManager.SimulateCurrentCollisions();

			//A registers the hit but has no resulting response vector because it's static
			Assert::IsTrue(aCopy.GetCollisionResponseInfo()._IsColliding);
			Assert::IsTrue(CommonHelpers::AreEqual(aCopy.GetCollisionResponseInfo()._ImpulseVector, Vector2(0, 0)));

			//D registers the hit and  DOES have resulting response vector because it's not static
			Assert::IsTrue(dCopy.GetCollisionResponseInfo()._IsColliding);
			Assert::IsFalse(CommonHelpers::AreEqual(dCopy.GetCollisionResponseInfo()._ImpulseVector, Vector2(0, 0)));
		}

		TEST_METHOD(Test_105_SimulateCurrentCollisions_ThreeOtherColliders_SingleCollision_IgnoresInactive)
		{
			CollisionManager collisionManager;
			Collider aCopy = _colliderA, bCopy = _colliderB, cCopy = _colliderC, dCopy = _colliderD;
			dCopy.SetIsActive(false);

			collisionManager.AddCollider(&aCopy); //Colliding with D
			collisionManager.AddCollider(&bCopy);
			collisionManager.AddCollider(&cCopy);
			collisionManager.AddCollider(&dCopy); //Colliding with A but is inactive

			collisionManager.SimulateCurrentCollisions();

			Assert::IsFalse(aCopy.GetCollisionResponseInfo()._IsColliding);
		}

		TEST_METHOD(Test_106_SimulateCurrentCollisions_TriggerCollider_ThreeOtherColliders_SingleCollision_NoImpulseResponseForBoth)
		{
			CollisionManager collisionManager;
			Collider aCopy = _colliderA, bCopy = _colliderB, cCopy = _colliderC, dCopy = _colliderD;
			aCopy.SetIsTrigger(true);

			RigidBody dBody = _rigidBodyB;
			dBody.SetInputVelocity(Vector2(0, 20));
			dCopy.SetAssociatedRigidBody(&dBody);

			collisionManager.AddCollider(&aCopy); //Colliding with D but is Static
			collisionManager.AddCollider(&bCopy);
			collisionManager.AddCollider(&cCopy);
			collisionManager.AddCollider(&dCopy); //Colliding with A

			collisionManager.SimulateCurrentCollisions();

			//A registers the hit but has no resulting response vector because it's static
			Assert::IsTrue(aCopy.GetCollisionResponseInfo()._IsColliding);
			Assert::IsTrue(CommonHelpers::AreEqual(aCopy.GetCollisionResponseInfo()._ImpulseVector, Vector2(0, 0)));

			//D registers the hit and  DOES have resulting response vector because it's not static
			Assert::IsTrue(dCopy.GetCollisionResponseInfo()._IsColliding);
			Assert::IsTrue(CommonHelpers::AreEqual(dCopy.GetCollisionResponseInfo()._ImpulseVector, Vector2(0, 0)));
		}

		TEST_METHOD(Test_107_SimulateCurrentCollisions_ThreeOtherColliders_NoCollision)
		{
			CollisionManager collisionManager;
			Collider aCopy = _colliderA, bCopy = _colliderB, cCopy = _colliderC, dCopy = _colliderD;

			dCopy.SetPosition(Vector2(2.5,0)); //Shifting d away from a

			collisionManager.AddCollider(&aCopy);
			collisionManager.AddCollider(&bCopy);
			collisionManager.AddCollider(&cCopy);
			collisionManager.AddCollider(&dCopy);

			collisionManager.SimulateCurrentCollisions();

			Assert::IsFalse(aCopy.GetCollisionResponseInfo()._IsColliding);
			Assert::IsFalse(dCopy.GetCollisionResponseInfo()._IsColliding);
		}

		TEST_METHOD(Test_107_SimulateCurrentCollisions_ThreeOtherColliders_ThreeWayCollision)
		{
			CollisionManager collisionManager;
			Collider aCopy = _colliderA, dCopy1 = _colliderD, dCopy2 = _colliderD, dCopy3 = _colliderD;

			collisionManager.AddCollider(&aCopy); //A collides with all three D colliders
			collisionManager.AddCollider(&dCopy1);
			collisionManager.AddCollider(&dCopy2);
			collisionManager.AddCollider(&dCopy3);

			collisionManager.SimulateCurrentCollisions();

			Assert::IsTrue(aCopy.GetCollisionResponseInfo()._IsColliding);
			Assert::IsTrue(aCopy.GetCollisionResponseInfo()._Batons.size() == 3);
		}


	private:
		Vector2 _origin;
		RigidBody _rigidBodyA;
		RigidBody _rigidBodyB;

		Collider _colliderA;
		Collider _colliderB;
		Collider _colliderC;
		Collider _colliderD;
	};
}