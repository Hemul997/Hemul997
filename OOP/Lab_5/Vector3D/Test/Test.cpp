// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <float.h>
#include "../Vector3D/Vector3D.h"
BOOST_AUTO_TEST_SUITE(class_Vector3D)


struct BinaryOperatorsFixture_
{
	BinaryOperatorsFixture_()
		: firstVector(0, 1, 1)
		, secondVector(1, 1, 2)
		, thirdVector(2, 2, 3)
	{}
	CVector3D firstVector;
	CVector3D secondVector;
	CVector3D thirdVector;
};
struct OperatorMultiplicationFixture_
{
	OperatorMultiplicationFixture_()
		: vector(2, 4, 8)
		, firstVector(3 * vector)
		, secondVector(0 * vector)
		, thirdVector(-1 * vector)
		, resultFirstVector(6, 12, 24)
		, resultSecondVector(0, 0, 0)
		, resultThirdVector(-vector)
	{}

	CVector3D vector;

	CVector3D firstVector;
	CVector3D secondVector;
	CVector3D thirdVector;

	CVector3D resultFirstVector;
	CVector3D resultSecondVector;
	CVector3D resultThirdVector;
};
struct OperatorDelFixture_
{
	OperatorDelFixture_()
		: vector(1, 2, 3)
		, firstVector(vector / 1)
		, secondVector(vector / 0)
		, thirdVector(vector / -1)
		, resultFirstVector(1, 2, 3)
		, resultSecondVector(resultFirstVector)
		, resultThirdVector(-resultFirstVector)
	{}
	CVector3D vector;

	CVector3D firstVector;
	CVector3D secondVector;
	CVector3D thirdVector;

	CVector3D resultFirstVector;
	CVector3D resultSecondVector;
	CVector3D resultThirdVector;
};

	BOOST_AUTO_TEST_CASE(can_create_zero_vector)
	{
		CVector3D emptyVector;
		BOOST_CHECK_EQUAL(emptyVector.x, 0);
		BOOST_CHECK_EQUAL(emptyVector.y, 0);
		BOOST_CHECK_EQUAL(emptyVector.z, 0);
	}
	BOOST_AUTO_TEST_CASE(can_create_not_zero_vector)
	{
		CVector3D newVector(2, 4, 8);
		BOOST_CHECK_EQUAL(newVector.x, 2);
		BOOST_CHECK_EQUAL(newVector.y, 4);
		BOOST_CHECK_EQUAL(newVector.z, 8);
	}
	BOOST_AUTO_TEST_CASE(can_get_vector_length)
	{
		CVector3D newVector(8, 6, 0);

		double vectorLength = newVector.GetLength();
		double resultVectorLength = 10;

		BOOST_CHECK_EQUAL(vectorLength, resultVectorLength);
	}
	BOOST_AUTO_TEST_CASE(unarny_plus_returns_equal_vector)
	{
		CVector3D newVector(0, 0, 1);
		BOOST_CHECK(+newVector == newVector);
	}
	BOOST_AUTO_TEST_CASE(unarny_minus_returns_vector_with_inverse_direction)
	{
		CVector3D newVector(2, 4, 8);
		CVector3D resultVector(-2, -4, -8);

		BOOST_CHECK(-newVector == resultVector);
	}
	BOOST_FIXTURE_TEST_CASE(can_add_vectors, BinaryOperatorsFixture_)
	{
		CVector3D vectorsSum = firstVector + secondVector + thirdVector;

		CVector3D resultVector(3, 4, 6);

		BOOST_CHECK(resultVector == vectorsSum);
	}

	BOOST_FIXTURE_TEST_CASE(can_subtract_vectors, BinaryOperatorsFixture_)
	{
		CVector3D vectorsDiffirence = firstVector - secondVector - thirdVector;

		CVector3D resultVector(-3, -2, -4);

		BOOST_CHECK(resultVector == vectorsDiffirence);
	}
	BOOST_AUTO_TEST_CASE(can_increase_magnitude_of_vector)
	{
		CVector3D vectorOne(1, 2, 3);
		CVector3D vectorTwo(3, 2, 1);

		CVector3D expectedVector(4, 4, 4);

		vectorOne += vectorTwo;

		BOOST_CHECK(expectedVector == vectorOne);
	}

	BOOST_AUTO_TEST_CASE(can_decrease_magnitude_of_vector)
	{
		CVector3D vectorOne(1, 2, 3);
		CVector3D vectorTwo(1, 1, 1);

		CVector3D expectedVector(0, 1, 2);

		vectorOne -= vectorTwo;

		BOOST_CHECK(expectedVector == vectorOne);
	}
	BOOST_FIXTURE_TEST_CASE(can_multiply_scalar_by_vector, OperatorMultiplicationFixture_)
	{
		BOOST_CHECK(resultFirstVector == firstVector);
		BOOST_CHECK(resultSecondVector == secondVector);
		BOOST_CHECK(resultThirdVector == thirdVector);
	}

	BOOST_FIXTURE_TEST_CASE(can_divide_vector_by_scalar, OperatorDelFixture_)
	{
		BOOST_CHECK(resultFirstVector == firstVector);
		BOOST_CHECK(resultSecondVector == secondVector);
		BOOST_CHECK(resultThirdVector == thirdVector);
	}

	BOOST_AUTO_TEST_CASE(can_increase_magnitude_of_vector_by_multiplying_vector_and_scalar)
	{
		CVector3D vector(1, 2, 3);
		CVector3D expectedVector(10, 20, 30);
		vector *= 10;

		BOOST_CHECK(expectedVector == vector);
	}

	BOOST_AUTO_TEST_CASE(can_decrease_magnitude_of_vector_by_deviding_vector_and_scalar)
	{
		CVector3D vector(1, 2, 3);
		CVector3D resultVector(0.1, 0.2, 0.3);
		CVector3D differsVector;

		vector /= 10;
		differsVector = resultVector - vector;
		BOOST_CHECK(differsVector.x < DBL_EPSILON, differsVector.y < DBL_EPSILON, differsVector.z < DBL_EPSILON);

		vector /= 0;
		differsVector = resultVector - vector;
		BOOST_CHECK(differsVector.x < DBL_EPSILON, differsVector.y < DBL_EPSILON, differsVector.z < DBL_EPSILON);

		vector /= -1;
		differsVector = resultVector + vector;
		BOOST_CHECK(differsVector.x < DBL_EPSILON, differsVector.y < DBL_EPSILON, differsVector.z < DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(can_compare_vectors)
	{
		CVector3D firstVector(1, 2, 3);
		CVector3D secondVector(6, 5, 3);
		CVector3D thirdVector(1, 2, 3);

		BOOST_CHECK(firstVector != secondVector);
		BOOST_CHECK(firstVector == thirdVector);
	}
	BOOST_AUTO_TEST_SUITE_END()