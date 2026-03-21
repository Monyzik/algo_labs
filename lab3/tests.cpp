#include <gtest/gtest.h>
#include <string>

#include "structures.h"
#include "stack.h"
#include "tree.h"
#include "parse.h"

using namespace std;


string stackToString(stack s) {
    string ans;
    for (int i = 0; i < s.size; i++) {
        if (s.data[i].type == number) {
            ans += to_string(s.data[i].num);
        } else if (s.data[i].type == variable) {
            ans += s.data[i].var;
        } else {
            ans += s.data[i].sign;
        }
        ans += " ";
    }
    return ans;
}


TEST(TestStack, Stack) {
    stack s;
    initStack(&s);
    EXPECT_EQ(pop(&s), nullptr);
    EXPECT_EQ(back(&s), nullptr);

    push(&s, createNumber(1));
    push(&s, createNumber(2));
    push(&s, createNumber(3));
    push(&s, createNumber(4));
    push(&s, createNumber(5));

    EXPECT_EQ(back(&s)->num, 5);
    EXPECT_EQ(stackToString(s), "1 2 3 4 5 ");
    EXPECT_EQ(pop(&s)->num, 5);
    EXPECT_EQ(back(&s)->num, 4);
    freeStack(&s);
}

TEST(TestParsing, Parse) {
    array<string, 2> data[] = {
        {"(1+   2)", "( 1 + 2 ) "},
        {"(1* 2) * (   (1 +        2) - (-1)) ^ 3", "( 1 * 2 ) * ( ( 1 + 2 ) - ( - 1 ) ) ^ 3 "},
        {"a * b - abacaba / fedia", "a * b - abacaba / fedia "},
    };

    for (auto [in, ans]: data) {
        stack s = parse(in.data());
        EXPECT_EQ(stackToString(s), ans);
        freeStack(&s);
    };
}

TEST(TestConvertToRpn, Convert) {
    array<string, 2> data[] = {
        {"1+   2", "1 2 + "},
        {"(1 * 2) * ((1 + 2) - (-1)) ^ 3", "1 2 * 1 2 + 1 - - 3 ^ * "},
        {"1 + 100 * a ^ 10 - x ^ kak * 1431", "1 100 a 10 ^ * + x kak ^ 1431 * - "},
        {"a ^ (10 ^ b)", "a 10 b ^ ^ "},
    };

    for (auto [in, ans]: data) {
        stack s = parse(in.data());
        stack out = toRpn(&s);
        EXPECT_EQ(stackToString(out), ans);
        freeStack(&s);
        freeStack(&out);
    }
}

TEST(TestTransform, Transform) {
    array<string, 2> data[] = {
        {"a * a - a * b - a * c", "(a * ((a - b) - c))"},
        {"1-        1", "(1 - 1)"},
        {"33 * 33 - 33 * 100", "(33 * (33 - 100))"},
        {"-5 ^ 10 / (- 5 + 3)", "(((-5) ^ 10) / ((-5) + 3))"},
        {"a - a", "(a * (1 - 1))"},
        {"2*x - 2*y", "(2 * (x - y))"},
        {"a * b * c - a * d", "(a * ((b * c) - d))"},
        {"4 * x * y * z - 4 * x * y * w", "(((4 * x) * y) * (z - w))"},
        {"6*a - 6*b - 6*c", "(6 * ((a - b) - c))"},
        {"var1 * var2 - var1 * var3", "(var1 * (var2 - var3))"},
        {"a*b*c - a*b*d - a*b*e", "((a * b) * ((c - d) - e))"},
        {"a + b - a * c", "((a + b) - (a * c))"},
        {"a - a - c * d", "((a * (1 - 1)) - (c * d))"},
        {"a * (b - c) - a * (d - e)", "(a * ((b - c) - (d - e)))"},
        {"a * (-b) - a * (-c)", "(a * ((-b) - (-c)))"},
        {"(a + b) * c - (a + b) * d", "((a + b) * (c - d))"},
        {"a ^ 2 * b - a ^ 2 * c", "((a ^ 2) * (b - c))"},
        {"(-a) * (-b) - (-a) * (-c)", "((-a) * ((-b) - (-c)))"},
        {"-x * y - -x * z", "((-x) * (y - z))"}
    };


    for (auto [in, ans]: data) {
        testing::internal::CaptureStdout();
        stack s = parse(in.data());
        stack rpn = toRpn(&s);
        node *tree = NULL;
        int n = rpn.size - 1;
        tree = buildFromRpn(tree, &rpn, &n);
        tree = transformLoop(tree);
        printInfix(tree);
        EXPECT_EQ(testing::internal::GetCapturedStdout(), ans);
        freeStack(&s);
        freeStack(&rpn);
    }
}

TEST(TestIncorrectInput, IncorectInput) {
    string data[] = {"a + * b", "a + ()", "a * b /", "-", "a ^"};

    for (auto in: data) {
        stack s = parse(in.data());
        stack rpn = toRpn(&s);
        node *tree = NULL;
        int n = rpn.size - 1;
        EXPECT_EXIT(buildFromRpn(tree, &rpn, &n), testing::ExitedWithCode(2), "");
        freeStack(&s);
        freeStack(&rpn);
    }
}
