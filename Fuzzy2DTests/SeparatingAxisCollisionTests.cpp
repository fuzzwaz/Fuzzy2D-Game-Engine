#include "pch.h"
#include "CppUnitTest.h"
#include "../Fuzzy2D/SeparatingAxisCollision.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PhysicsTests
{
	TEST_CLASS(SeparatingAxisCollisionTests)
	{
	public:

		SeparatingAxisCollisionTests()
		{
			_colliderA.SetAssociatedRigidBody(&rigidBody);
			_colliderA.SetPosition(origin);
			_colliderA._Polygon.AddVertexPoint({ Vector2(2, 8), Vector2(5, 0), Vector2(10, 8) });

			_colliderB.SetAssociatedRigidBody(&rigidBody);
			_colliderB.SetPosition(origin);
			_colliderB._Polygon.AddVertexPoint({ Vector2(2, 8), Vector2(5, 0), Vector2(10, 8), Vector2(5, 16) });
		}

		TEST_METHOD(Test_101_IsColliding_TriangleA_Polygon_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(2, 3), Vector2(2, -2), Vector2(10, -2), Vector2(10, 3) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderA, testCollider);
			Assert::IsTrue(IsColliding);

			delete testCollider;
		}
		
		TEST_METHOD(Test_102_IsColliding_TriangleA_Polygon_Not_Collding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(2, -1), Vector2(2, -2), Vector2(10, -2), Vector2(10, -1) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderA, testCollider);
			Assert::IsFalse(IsColliding);

			delete testCollider;
		}

		TEST_METHOD(Test_103_IsColliding_TriangleA_Polygon_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(2, 0), Vector2(2, -2), Vector2(10, -2), Vector2(10, 0) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderA, testCollider);
			Assert::IsTrue(IsColliding);

			delete testCollider;
		}
		
		TEST_METHOD(Test_104_IsColliding_TriangleA_Triangle_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(5, 4), Vector2(9, 2), Vector2(10, 4) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderA, testCollider);
			Assert::IsTrue(IsColliding);

			delete testCollider;
		}

		TEST_METHOD(Test_105_IsColliding_TriangleA_Triangle_Not_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(8, 3), Vector2(9, 2), Vector2(10, 4) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderA, testCollider);
			Assert::IsFalse(IsColliding);

			delete testCollider;
		}

		TEST_METHOD(Test_106_IsColliding_PolygonB_Polygon_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(5, 14), Vector2(9, 12), Vector2(10, 13), Vector2(9, 16) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderB, testCollider);
			Assert::IsTrue(IsColliding);

			delete testCollider;
		}
		
		TEST_METHOD(Test_107_IsColliding_PolygonB_Polygon_Not_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(7, 14), Vector2(9, 12), Vector2(10, 13), Vector2(9, 16) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderB, testCollider);
			Assert::IsFalse(IsColliding);

			delete testCollider;
		}

		TEST_METHOD(Test_108_IsColliding_PolygonB_Polygon_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(5, 8), Vector2(5, 6), Vector2(7, 6), Vector2(7, 8) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderB, testCollider);
			Assert::IsTrue(IsColliding);

			delete testCollider;
		}

		TEST_METHOD(Test_109_IsColliding_PolygonB_Polygon_PositionOffset_Not_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->SetPosition(Vector2(6, 0));
			testCollider->_Polygon.AddVertexPoint({ Vector2(5, 8), Vector2(5, 6), Vector2(7, 6), Vector2(7, 8) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderB, testCollider);
			Assert::IsFalse(IsColliding);

			delete testCollider;
		}

		TEST_METHOD(Test_110_IsColliding_PolygonB_Polygon_PositionOffset_Colliding)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->SetPosition(Vector2(5, 0));
			testCollider->_Polygon.AddVertexPoint({ Vector2(5, 8), Vector2(5, 6), Vector2(7, 6), Vector2(7, 8) });

			const bool IsColliding = SeparatingAxisCollision::IsColliding(&_colliderB, testCollider);
			Assert::IsTrue(IsColliding);

			delete testCollider;
		}

		TEST_METHOD(Test_111_IsColliding_PolygonB_Point_Colliding)
		{
			const Vector2 testPoint(5, 5);

			const bool IsColliding = SeparatingAxisCollision::IsColliding(testPoint , &_colliderB);
			Assert::IsTrue(IsColliding);
		}

		TEST_METHOD(Test_112_IsColliding_PolygonB_Point_Not_Colliding)
		{
			const Vector2 testPoint(7, 1);

			const bool IsColliding = SeparatingAxisCollision::IsColliding(testPoint, &_colliderB);
			Assert::IsFalse(IsColliding);
		}

		TEST_METHOD(Test_113_IsCircleCollider_Colliding)
		{
			Collider* testColliderA = CreateTestCollider();
			testColliderA->SetIsCircular(true);
			testColliderA->SetRadius(5);
			testColliderA->SetPosition(Vector2(0, -10));

			Collider* testColliderB = CreateTestCollider();
			testColliderB->SetIsCircular(true);
			testColliderB->SetRadius(5);

			const bool IsColliding = SeparatingAxisCollision::IsCircleColliding(testColliderA, testColliderB);
			Assert::IsTrue(IsColliding);

		}

		TEST_METHOD(Test_114_IsCircleCollider_NotColliding)
		{
			Collider* testColliderA = CreateTestCollider();
			testColliderA->SetIsCircular(true);
			testColliderA->SetRadius(5);
			testColliderA->SetPosition(Vector2(0, -10));

			Collider* testColliderB = CreateTestCollider();
			testColliderB->SetIsCircular(true);
			testColliderB->SetRadius(4);

			const bool IsColliding = SeparatingAxisCollision::IsCircleColliding(testColliderA, testColliderB);
			Assert::IsFalse(IsColliding);

		}

		TEST_METHOD(Test_115_IsColliding_UsingCircluarDetection_Colliding)
		{
			Collider* testColliderA = CreateTestCollider();
			testColliderA->SetIsCircular(true);
			testColliderA->SetRadius(5);
			testColliderA->SetPosition(Vector2(0, -10));

			Collider* testColliderB = CreateTestCollider();
			testColliderB->SetIsCircular(true);
			testColliderB->SetRadius(5);

			const bool IsColliding = SeparatingAxisCollision::IsColliding(testColliderA, testColliderB);
			Assert::IsTrue(IsColliding);

		}

		TEST_METHOD(Test_116_IsColliding_IgnoresCircluarDetection_NotColliding)
		{
			Collider* testColliderA = CreateTestCollider();
			testColliderA->_Polygon.AddVertexPoint({ Vector2(0,0), Vector2(0.5,-1), Vector2(1,0) });
			testColliderA->SetIsCircular(true);
			testColliderA->SetRadius(5);
			testColliderA->SetPosition(Vector2(0, -10));

			Collider* testColliderB = CreateTestCollider();
			testColliderB->_Polygon.AddVertexPoint({ Vector2(0,0), Vector2(0.5,1), Vector2(1,0) });
			testColliderB->SetIsCircular(false); //Despite circles colliding, it should to polygon collision check because this is false
			testColliderB->SetRadius(5);

			const bool IsColliding = SeparatingAxisCollision::IsColliding(testColliderA, testColliderB);
			Assert::IsFalse(IsColliding);

		}

		TEST_METHOD(Test_201_CalculateCollisionPoint_PolygonA_Single_Vertex_Collision)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(2, 3), Vector2(2, -2), Vector2(10, -2), Vector2(10, 3) });

			Vector2 collisionPoint = SeparatingAxisCollision::CalculateCollisionPoint(&_colliderA, testCollider);
			const Vector2 expectedResult(5, 0);

			Assert::IsTrue(collisionPoint == expectedResult);

			delete testCollider;
		}

		TEST_METHOD(Test_202_CalculateCollisionPoint_PolygonA_Double_Vertex_Collision)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(8, 5), Vector2(8, 7), Vector2(11, 5), Vector2(12, 6), Vector2(11, 7) });

			Vector2 collisionPoint = SeparatingAxisCollision::CalculateCollisionPoint(&_colliderA, testCollider);
			Vector2 expectedResult(8, 6);

			Assert::IsTrue(collisionPoint == expectedResult);

			delete testCollider;
		}

		TEST_METHOD(Test_203_CalculateCollisionPoint_PolygonB_Single_Vertex_Polygon_Offset_Double_Vertex_Collision)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->SetPosition(Vector2(0, 2));
			testCollider->_Polygon.AddVertexPoint({ Vector2(8, 5), Vector2(8, 7), Vector2(11, 5), Vector2(12, 6), Vector2(11, 7) });

			Vector2 collisionPoint = SeparatingAxisCollision::CalculateCollisionPoint(&_colliderB, testCollider);
			Vector2 expectedResult(8.67, 8);

			Assert::IsTrue( CommonHelpers::AreEqual(collisionPoint,expectedResult) );

			delete testCollider;
		}

		TEST_METHOD(Test_301_CalculateMinMixProjection_PerpVector_nEight_nThree)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(2,8), Vector2(5,0), Vector2(10,8) });
			const Vector2 perpendicular(-8, -3);

			Extents outputPair = SeparatingAxisCollision::CalculateMinMixProjection(perpendicular, testCollider);
			Extents expectedResultPair(-104.0, -40.0);

			Assert::IsTrue(outputPair == expectedResultPair);
		}

		TEST_METHOD(Test_302_CalculateMinMixProjection_PerpVector_Eight_nFive)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(2,8), Vector2(5,0), Vector2(10,8) });
			const Vector2 perpendicular(8, -5);

			Extents outputPair = SeparatingAxisCollision::CalculateMinMixProjection(perpendicular, testCollider);
			Extents expectedResultPair(-24.0, 40.0);

			Assert::IsTrue(outputPair == expectedResultPair);
		}

		TEST_METHOD(Test_303_CalculateMinMixProjection_PerpVector_Zero_Eight)
		{
			Collider* testCollider = CreateTestCollider();
			testCollider->_Polygon.AddVertexPoint({ Vector2(2,8), Vector2(5,0), Vector2(10,8) });
			const Vector2 perpendicular(0, 8);

			Extents outputPair = SeparatingAxisCollision::CalculateMinMixProjection(perpendicular, testCollider);
			Extents expectedResultPair(0.0, 64.0);

			Assert::IsTrue(outputPair == expectedResultPair);
		}
		
		TEST_METHOD(Test_401_IsSeparatingAxis_Not_Separating)
		{
			Extents extentsA(-42.0, 6.0);
			Extents extentsB(-10.0, 35.0);

			const bool IsSeparating = SeparatingAxisCollision::IsSeparatingAxis(extentsA, extentsB);
			const bool expectedSeparating = false;

			Assert::IsTrue(IsSeparating == expectedSeparating);
		}
		
		TEST_METHOD(Test_402_IsSeparatingAxis_Separating)
		{
			Extents extentsA(-42.0, 6.0);
			Extents extentsB(10.0, 35.0);

			const bool IsSeparating = SeparatingAxisCollision::IsSeparatingAxis(extentsA, extentsB);
			const bool expectedSeparating = true;

			Assert::IsTrue(IsSeparating == expectedSeparating);
		}
		
	private:
		Vector2 origin;
		RigidBody rigidBody;

		Collider _colliderA;
		Collider _colliderB;

		Collider* CreateTestCollider()
		{
			Collider* testCollider = new Collider();
			testCollider->SetAssociatedRigidBody(&rigidBody);
			testCollider->SetPosition(origin);
			return testCollider;
		}
	};
}
