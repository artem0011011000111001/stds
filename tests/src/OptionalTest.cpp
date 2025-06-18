// optional_test.cpp

#include "gtest/gtest.h"

// Import your optional module and exceptions module
import stds.utility.optional;
import stds.exceptions;

using stds::utility::optional;
using stds::traits::throw_policy;
using stds::utility::null;
using stds::exceptions::null_reference;  // exception type for accessing empty optional

// Tests for optional<int>
TEST(OptionalIntTest, DefaultConstruct) {
    optional<int> o;
    EXPECT_FALSE(o.has_value());
    EXPECT_FALSE(static_cast<bool>(o));
    // value_or should return the default when empty
    EXPECT_EQ(o.value_or(42), 42);
    // value() should throw when empty
    EXPECT_THROW(o.value(), null_reference);
}

TEST(OptionalIntTest, ConstructFromValue) {
    optional<int> o1(5);
    EXPECT_TRUE(o1.has_value());
    EXPECT_TRUE(static_cast<bool>(o1));
    EXPECT_EQ(*o1, 5);
    EXPECT_EQ(o1.value(), 5);

    // value_or on non-empty should return the contained value
    EXPECT_EQ(o1.value_or(100), 5);
}

TEST(OptionalIntTest, CopyAndMoveConstruct) {
    optional<int> orig(10);
    optional<int> copy(orig);
    EXPECT_TRUE(copy.has_value());
    EXPECT_EQ(*copy, 10);

    optional<int> moved(std::move(orig));
    EXPECT_TRUE(moved.has_value());
    EXPECT_EQ(*moved, 10);
    // After move, orig may be in a valid but unspecified state; do not rely on its value
}

TEST(OptionalIntTest, CopyAndMoveAssign) {
    optional<int> a(1);
    optional<int> b;
    b = a;
    EXPECT_TRUE(b.has_value());
    EXPECT_EQ(*b, 1);

    optional<int> c;
    c = std::move(a);
    EXPECT_TRUE(c.has_value());
    EXPECT_EQ(*c, 1);

    // Assign nullopt
    c = null;
    EXPECT_FALSE(c.has_value());
    EXPECT_FALSE(static_cast<bool>(c));
}

TEST(OptionalIntTest, AssignFromValue) {
    optional<int> o;
    o = 7;
    EXPECT_TRUE(o.has_value());
    EXPECT_EQ(*o, 7);

    o = null;
    EXPECT_FALSE(o.has_value());

    o = 15;
    EXPECT_TRUE(o);
    EXPECT_EQ(o.value(), 15);
}

TEST(OptionalIntTest, EmplaceAndReset) {
    optional<int> o;
    auto& ref = o.emplace(123);
    EXPECT_TRUE(o.has_value());
    EXPECT_EQ(&ref, &*o);
    EXPECT_EQ(*o, 123);

    bool reset_res = o.reset();
    EXPECT_TRUE(reset_res);
    EXPECT_FALSE(o.has_value());
    // Emplace again after reset
    o.emplace(456);
    EXPECT_TRUE(o.has_value());
    EXPECT_EQ(o.value(), 456);
}

TEST(OptionalIntTest, ComparisonsBetweenOptionals) {
    optional<int> e1;           // empty
    optional<int> e2(null);
    optional<int> a(5);
    optional<int> b(10);

    // empty == empty
    EXPECT_TRUE(e1 == e2);
    EXPECT_FALSE(e1 != e2);
    EXPECT_FALSE(e1 < e2);
    EXPECT_FALSE(e1 > e2);
    EXPECT_TRUE(e1 <= e2);
    EXPECT_TRUE(e1 >= e2);

    // empty vs non-empty
    EXPECT_TRUE(e1 < a);
    EXPECT_FALSE(e1 > a);
    EXPECT_TRUE(e1 <= a);
    EXPECT_FALSE(e1 >= a);

    EXPECT_TRUE(b > e1);
    EXPECT_FALSE(b < e1);
    EXPECT_TRUE(b >= e1);
    EXPECT_FALSE(b <= e1);

    // non-empty comparisons
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(b > a);
    EXPECT_FALSE(a > b);

    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(b <= a);
    EXPECT_TRUE(b >= a);
    EXPECT_FALSE(a >= b);

    optional<int> a2(5);
    EXPECT_TRUE(a == a2);
    EXPECT_FALSE(a != a2);
    EXPECT_TRUE(a <= a2);
    EXPECT_TRUE(a >= a2);
}

TEST(OptionalIntTest, ComparisonsWithValue) {
    optional<int> e;
    optional<int> o(20);

    // optional vs T
    EXPECT_TRUE(e < 5);     // empty < any value
    EXPECT_TRUE(e <= 5);
    EXPECT_FALSE(e == 5);
    EXPECT_TRUE(e != 5);
    EXPECT_FALSE(e > 5);
    EXPECT_FALSE(e >= 5);

    EXPECT_TRUE(o == 20);
    EXPECT_FALSE(o != 20);
    EXPECT_FALSE(o < 20);
    EXPECT_TRUE(o <= 20);
    EXPECT_FALSE(o > 20);
    EXPECT_TRUE(o >= 20);

    EXPECT_TRUE(o < 30);
    EXPECT_TRUE(o <= 30);
    EXPECT_FALSE(o > 30);
    EXPECT_FALSE(o >= 30);

    // T vs optional
    EXPECT_FALSE(5 < e);   // value < empty is false
    EXPECT_FALSE(5 <= e);  // value <= empty is false
    EXPECT_TRUE(5 > e);
    EXPECT_TRUE(5 >= e);
    EXPECT_FALSE(5 == e);
    EXPECT_TRUE(5 != e);

    EXPECT_TRUE(20 == o);
    EXPECT_FALSE(20 != o);
    EXPECT_FALSE(20 < o);
    EXPECT_TRUE(20 <= o);
    EXPECT_FALSE(20 > o);
    EXPECT_TRUE(20 >= o);

    EXPECT_FALSE(30 == o);
    EXPECT_TRUE(30 != o);
    EXPECT_FALSE(30 < o);
    EXPECT_FALSE(30 <= o);
    EXPECT_TRUE(30 > o);
    EXPECT_TRUE(30 >= o);
}

// Tests for optional<std::string>
TEST(OptionalStringTest, BasicOperations) {
    optional<std::string> es;
    EXPECT_FALSE(es.has_value());
    EXPECT_THROW(es.value(), null_reference);

    optional<std::string> s1(std::string("hello"));
    EXPECT_TRUE(s1);
    EXPECT_EQ(*s1, "hello");
    EXPECT_EQ(s1.value(), "hello");

    // value_or
    EXPECT_EQ(es.value_or(std::string("def")), "def");
    EXPECT_EQ(s1.value_or(std::string("xxx")), "hello");

    // assignment
    es = std::string("world");
    EXPECT_TRUE(es);
    EXPECT_EQ(*es, "world");

    optional<std::string> s2 = s1;
    EXPECT_TRUE(s2);
    EXPECT_EQ(*s2, "hello");

    optional<std::string> s3 = std::move(es);
    EXPECT_TRUE(s3);
    EXPECT_EQ(*s3, "world");

    // emplace
    s3.emplace("new");
    EXPECT_EQ(*s3, "new");

    // reset
    EXPECT_TRUE(s3.reset());
    EXPECT_FALSE(s3);
}

TEST(OptionalStringTest, Comparisons) {
    optional<std::string> e1, e2;
    optional<std::string> a("apple"), b("banana"), a2("apple");

    // empty == empty
    EXPECT_TRUE(e1 == e2);
    // empty < any
    EXPECT_TRUE(e1 < a);
    EXPECT_TRUE(e1 <= a);
    EXPECT_FALSE(e1 > a);
    EXPECT_FALSE(e1 >= a);

    // non-empty comparisons
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a <= a2);
    EXPECT_TRUE(a >= a2);
    EXPECT_TRUE(a == a2);
    EXPECT_FALSE(a != a2);
}

// Test operator-> and exception on empty
TEST(OptionalTest, ArrowOperatorThrows) {
    struct S { int x; };
    optional<S> es;
    EXPECT_THROW(es->x, null_reference);

    optional<S> s{ S{42} };
    EXPECT_EQ(s->x, 42);
}

// Test constexpr behavior (if supported by compiler)
// This is checked at compile-time via static_assert, not part of GoogleTest runtime.
constexpr bool constexpr_optional_test() {
    optional<int> o;
    if (o.has_value()) return false;
    o = 5;
    if (!o.has_value()) return false;
    if (*o != 5) return false;
    o.reset();
    if (o.has_value()) return false;
    o.emplace(7);
    if (*o != 7) return false;
    return true;
}
//static_assert(constexpr_optional_test(), "constexpr optional<int> test failed");

// Test three-way comparison if supported
#ifdef __cpp_impl_three_way_comparison
TEST(OptionalTest, ThreeWayComparison) {
    optional<int> e1, e2;
    optional<int> a(3), b(5);
    // empty == empty
    EXPECT_EQ((e1 <=> e2), std::strong_ordering::equal);
    // empty < non-empty
    EXPECT_EQ((e1 <=> a), std::strong_ordering::less);
    EXPECT_EQ((a <=> e1), std::strong_ordering::greater);
    // non-empty compare
    EXPECT_EQ((a <=> b), std::strong_ordering::less);
    EXPECT_EQ((b <=> a), std::strong_ordering::greater);
    optional<int> a2(3);
    EXPECT_EQ((a <=> a2), std::strong_ordering::equal);
}
#endif
