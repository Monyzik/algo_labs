#include <assert.h>

#include "tree.c"

void test1() {
    printf("test_1:\n");
    node *tree = NULL;
    tree = insert(tree, 10);
    assert(tree->data == 10);
    tree = insert(tree, 20);
    assert(tree->r->data == 20);
    tree = insert(tree, 20);
    assert(tree->r->data == 20);
    tree = insert(tree, 9);
    assert(tree->l->data == 9);
    clearTree(tree);
}

void test2() {
    printf("test_2:\n");
    node *tree = NULL;
    assert(depth(tree) == 0);
    tree = insert(tree, 20);
    assert(depth(tree) == 1);
    tree = insert(tree, 9);
    tree = insert(tree, 8);
    assert(depth(tree) == 3);
    assert(isLeaf(tree->l->l));
    assert(!isLeaf(tree));
    print(tree, 0);
    clearTree(tree);
}

void test3() {
    printf("test_3:\n");
    node *tree = NULL;
    tree = erase(tree, 100000);
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    tree = insert(tree, 20);
    tree = insert(tree, 9);
    tree = insert(tree, 22);
    tree = insert(tree, 23);
    tree = insert(tree, 8);
    tree = insert(tree, 7);
    assert(tree->data == 10);
    tree = erase(tree, 7);
    tree = erase(tree, 10);
    assert(tree->data == 20);
    clearTree(tree);
}

void test4() {
    printf("test_4:\n");
    node *tree = NULL;
    assert(query(tree, 1, depth(tree)) == 1);
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    tree = insert(tree, 20);
    tree = insert(tree, 9);
    assert(query(tree, 1, depth(tree)) == 1);
    tree = insert(tree, 1);
    assert(query(tree, 1, depth(tree)) == 0);
    tree = insert(tree, 21);
    assert(query(tree, 1, depth(tree)) == 1);
    print(tree, 0);
    clearTree(tree);
}

void test5() {
    printf("test_5:\n");
    node *tree = NULL;
    assert(findMin(tree) == NULL);
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    tree = insert(tree, 20);
    assert(findMin(tree)->data == 10);
    tree = insert(tree, 8);
    assert(findMin(tree)->data == 8);
    tree = insert(tree, 9);
    tree = insert(tree, 1);
    assert(findMin(tree)->data == 1);
    clearTree(tree);
}

signed main() {
    test1();
    test2();
    test3();
    test4();
    test5();
}
