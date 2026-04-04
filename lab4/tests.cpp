#include <gtest/gtest.h>
#include <cmath>

using namespace std;

#include "tree.h"

TEST(AVLTest, RightRotation) {
    node *t = nullptr;
    t = insert(t, "c", 3.0);
    t = insert(t, "b", 2.0);
    t = insert(t, "a", 1.0);
    t = insert(t, "b", 2.0);

    EXPECT_STREQ(t->key, "b");
    EXPECT_STREQ(t->l->key, "a");
    EXPECT_STREQ(t->r->key, "c");

    float *a = find(t, "a");
    EXPECT_EQ(*a, 1.0);
    clearTree(t);
}

TEST(AVLTest, LeftRotation) {
    node *t = nullptr;
    t = insert(t, "a", 1.0);
    t = insert(t, "b", 2.0);
    t = insert(t, "c", 3.0);

    EXPECT_STREQ(t->key, "b");
    EXPECT_STREQ(t->l->key, "a");
    EXPECT_STREQ(t->r->key, "c");

    EXPECT_EQ(height(t), 2);
    clearTree(t);
}

TEST(AVLTest, BigRightRotation) {
    node *t = nullptr;
    t = insert(t, "a", 1.0);
    t = insert(t, "c", 2.0);
    t = insert(t, "b", 2.0);

    EXPECT_STREQ(t->key, "b");
    EXPECT_STREQ(t->l->key, "a");
    EXPECT_STREQ(t->r->key, "c");

    EXPECT_EQ(diff(t), 0);
    clearTree(t);
}

TEST(AVLTest, BigLeftRotation) {
    node *t = nullptr;
    t = insert(t, "c", 3.0);
    t = insert(t, "a", 1.0);
    t = insert(t, "b", 2.0);

    EXPECT_STREQ(t->key, "b");
    EXPECT_STREQ(t->l->key, "a");
    EXPECT_STREQ(t->r->key, "c");

    EXPECT_STREQ(findMin(t)->key, "a");

    clearTree(t);
}

TEST(AVLTest, EraseFromTree) {
    node *t = nullptr;
    t = insert(t, "d", 4.0);
    t = insert(t, "b", 2.0);
    t = insert(t, "f", 6.0);
    t = insert(t, "a", 1.0);
    t = insert(t, "c", 3.0);
    t = insert(t, "e", 5.0);
    t = insert(t, "g", 6.0);

    t = erase(t, "d");
    EXPECT_STREQ(t->key, "e");
    EXPECT_EQ(t->value, 5.0);
    EXPECT_STREQ(t->l->key, "b");
    EXPECT_STREQ(t->r->key, "f");
    EXPECT_EQ(t->r->l, nullptr);

    clearTree(t);
}

TEST(AVLTest, EraseWithRotation) {
    node *t = nullptr;
    t = insert(t, "c", 3.0);
    t = insert(t, "a", 1.0);
    t = insert(t, "d", 4.0);
    t = insert(t, "b", 2.0);

    t = erase(t, "d");

    EXPECT_STREQ(t->key, "b");
    EXPECT_STREQ(t->l->key, "a");
    EXPECT_STREQ(t->r->key, "c");

    EXPECT_EQ(find(t, "d"), nullptr);

    clearTree(t);
}

bool check(node *t, int &h) {
    if (t == nullptr) {
        h = 0;
        return true;
    }
    int l, r;
    bool lok = check(t->l, l);
    bool rok = check(t->r, r);
    h = max(l, r) + 1;
    int b = l - r;
    return lok and rok and abs(b) <= 1 and t->h == h;
}

TEST(AVLTest, BigTreeTest) {
    node *t = nullptr;
    for (int i = 0; i < 26; i++) {
        t = insert(t, std::to_string('a' + i).c_str(), i);
    }
    int h = 0;
    EXPECT_EQ(check(t, h), true);
}
