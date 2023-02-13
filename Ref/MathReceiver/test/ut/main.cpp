#include "Tester.hpp"
#include "STest/Random/Random.hpp"

TEST(Nominal, Add) {
    Ref::Tester tester;
    tester.testAdd();
}

TEST(Nominal, Sub) {
    Ref::Tester tester;
    tester.testSub();
}

TEST(Nominal, Mul) {
    Ref::Tester tester;
    tester.testMul();
}

TEST(Nominal, Div) {
    Ref::Tester tester;
    tester.testDiv();
}

TEST(Nominal, DivZero) {
    Ref::Tester tester;
    tester.testDivZero();
}

TEST(Nominal, Throttle) {
    Ref::Tester tester;
    tester.testThrottle();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  STest::Random::seed();
  return RUN_ALL_TESTS();
}
