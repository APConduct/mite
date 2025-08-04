#include <gtest/gtest.h>
import mite;

using namespace mite::flat;

TEST(PointArithmetic, AdditionAssignmentOperator) {
    Point<int> p1(3, 4);
    const Point<int> p2(1, 2);
    p1 += p2;
    EXPECT_EQ(p1.x(), 4);
    EXPECT_EQ(p1.y(), 6);
}

TEST(PointArithmetic, SubtractionAssignmentOperator) {
    Point<int> p1(5, 7);
    Point<int> p2(2, 3);
    p1 -= p2;
    EXPECT_EQ(p1.x(), 3);
    EXPECT_EQ(p1.y(), 4);
}

TEST(PointMutators, SetXCoordinate) {
    Point<int> p(3, 4);
    p.at_x(10);
    EXPECT_EQ(p.x(), 10);
    EXPECT_EQ(p.y(), 4);
}

TEST(PointMutators, SetYCoordinate) {
    Point<int> p(3, 4);
    p.at_y(15);
    EXPECT_EQ(p.x(), 3);
    EXPECT_EQ(p.y(), 15);
}

TEST(PointMutators, ChainedMutatorCalls) {
    Point<int> p(0, 0);
    Point<int>& result = p.at_x(5).at_y(10);
    EXPECT_EQ(result.x(), 5);
    EXPECT_EQ(result.y(), 10);
    EXPECT_EQ(&result, &p);
}

TEST(PointDistance, DistanceWithDifferentTypes) {
    Point<int> p1(0, 0);
    Point<double> p2(3.0, 4.0);
    EXPECT_DOUBLE_EQ(p1.distance_from(p2), 5.0);
}

TEST(PointDistance, DistanceFromSamePoint) {
    Point<double> p(5.0, 3.0);
    EXPECT_DOUBLE_EQ(p.distance_from(p), 0.0);
}

TEST(PointDistance, NegativeCoordinateDistances) {
    Point<int> p1(-3, -4);
    Point<int> p2(0, 0);
    EXPECT_EQ(p1.x_from(p2), 3);
    EXPECT_EQ(p1.y_from(p2), 4);
}

TEST(PointCasting, CastToSameType) {
    Point<int> p(3, 4);
    Point<int> result = p.cast<int>();
    EXPECT_EQ(result.x(), 3);
    EXPECT_EQ(result.y(), 4);
}

TEST(PointCasting, CastFromFloatToInt) {
    Point<double> p(3.7, 4.9);
    Point<int> result = p.cast<int>();
    EXPECT_EQ(result.x(), 3);
    EXPECT_EQ(result.y(), 4);
}

TEST(PointArithmetic, MultiplicationWithZero) {
    Point<int> p(5, 3);
    Point<int> result = p * 0;
    EXPECT_EQ(result.x(), 0);
    EXPECT_EQ(result.y(), 0);
}

TEST(PointArithmetic, MultiplicationWithNegativeScalar) {
    Point<int> p(2, 3);
    Point<int> result = p * -2;
    EXPECT_EQ(result.x(), -4);
    EXPECT_EQ(result.y(), -6);
}

TEST(PointArithmetic, DivisionWithFloatingPoint) {
    Point<double> p(6.0, 9.0);
    Point<double> result = p / 2.0;
    EXPECT_DOUBLE_EQ(result.x(), 3.0);
    EXPECT_DOUBLE_EQ(result.y(), 4.5);
}

TEST(PointComparison, EqualityWithFloatingPoint) {
    Point<double> p1(3.14, 2.71);
    Point<double> p2(3.14, 2.71);
    EXPECT_TRUE(p1 == p2);
}

TEST(PointComparison, InequalityWithSameCoordinates) {
    Point<int> p1(5, 5);
    Point<int> p2(5, 5);
    EXPECT_FALSE(p1 != p2);
}