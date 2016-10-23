#include "lisp_test.h"

TEST_F(LispTest, IntegersAreSelfEvaluating) {
    ExpectEq("4", "4");
    ExpectEq("-14", "-14");
    ExpectEq("+14", "14");
}

TEST_F(LispTest, IntegerPredicate) {
    ExpectEq("(number? -1)", "#t");
    ExpectEq("(number? 1)", "#t");
    ExpectEq("(number? #t)", "#f");
}

TEST_F(LispTest, IntegerComparison) {
    // =, <, >, <=, >=
    // These procedures return #t if their arguments are (respectively): equal,
    // monotonically increasing, monotonically decreasing, monotonically nondecreasing,
    // or monotonically nonincreasing.

    ExpectEq("(=)", "#t");
    ExpectEq("(>)", "#t");
    ExpectEq("(<)", "#t");
    ExpectEq("(>=)", "#t");
    ExpectEq("(<=)", "#t");

    ExpectEq("(= 1 2)", "#f");
    ExpectEq("(= 1 1)", "#t");
    ExpectEq("(= 1 1 1)", "#t");
    ExpectEq("(= 1 1 2)", "#f");

    ExpectEq("(> 2 1)", "#t");
    ExpectEq("(> 1 1)", "#f");
    ExpectEq("(> 3 2 1)", "#t");
    ExpectEq("(> 3 2 3)", "#f");

    ExpectEq("(< 1 2)", "#t");
    ExpectEq("(< 1 1)", "#f");
    ExpectEq("(< 1 2 3)", "#t");
    ExpectEq("(< 1 2 1)", "#f");

    ExpectEq("(>= 2 1)", "#t");
    ExpectEq("(>= 1 2)", "#f");
    ExpectEq("(>= 3 3 2)", "#t");
    ExpectEq("(>= 3 3 4)", "#f");

    ExpectEq("(<= 2 1)", "#f");
    ExpectEq("(<= 1 2)", "#t");
    ExpectEq("(<= 3 3 4)", "#t");
    ExpectEq("(<= 3 3 2)", "#f");
}

TEST_F(LispTest, IntegerComparisonEdgeCases) {
    ExpectRuntimeError("(= 1 #t)");
    ExpectRuntimeError("(< 1 #t)");
    ExpectRuntimeError("(> 1 #t)");
    ExpectRuntimeError("(<= 1 #t)");
    ExpectRuntimeError("(>= 1 #t)");
}

TEST_F(LispTest, IntegerArithmetics) {
    ExpectEq("(+ 1 2)", "3");
    ExpectEq("(+ 1)", "1");
    ExpectEq("(+ 1 (+ 3 4 5))", "13");
    ExpectEq("(- 1 2)", "-1");
    ExpectEq("(- 2 1)", "1");
    ExpectEq("(* 5 6)", "30");
    ExpectEq("(/ 4 2)", "2");
    ExpectEq("(/ 4 2 2)", "1");
}

TEST_F(LispTest, IntegerArithmeticsEdgeCases) {
    ExpectRuntimeError("(+ 1 #t)");
    ExpectRuntimeError("(- 1 #t)");
    ExpectRuntimeError("(* 1 #t)");
    ExpectRuntimeError("(/ 1 #t)");

    ExpectEq("(+)", "0");
    ExpectEq("(*)", "1");
    ExpectRuntimeError("(/)");
    ExpectRuntimeError("(-)");
}

TEST_F(LispTest, IntegerMaxMin) {
    ExpectEq("(max 0)", "0");
    ExpectEq("(min 0)", "0");

    ExpectEq("(max 1 2)", "2");
    ExpectEq("(min 1 2)", "1");

    ExpectEq("(max 1 2 3 4 5)", "5");
    ExpectEq("(min 1 2 3 4 5)", "1");
}

TEST_F(LispTest, IntegerMaxMinEdgeCases) {
    ExpectRuntimeError("(max)");
    ExpectRuntimeError("(min)");

    ExpectRuntimeError("(max #t)");
    ExpectRuntimeError("(min #t)");
}

TEST_F(LispTest, IntegerAbs) {
    ExpectEq("(abs 10)", "10");
    ExpectEq("(abs -10)", "10");
}

TEST_F(LispTest, IntegerAbsEdgeCases) {
    ExpectRuntimeError("(abs)");
    ExpectRuntimeError("(abs #t)");
    ExpectRuntimeError("(abs 1 2)");
}