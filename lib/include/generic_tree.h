/*
 * Copyright (c) 2018 Jie Zheng
 */
#ifndef _GENERIC_TREE_H
#define _GENERIC_TREE_H
#include <lib/include/types.h>

struct binary_tree_node {
    /*
     * the parent points to the parent node. if parent is NULL, the node is
     * root node.
     */
    struct binary_tree_node * parent;
    struct binary_tree_node * left;
    struct binary_tree_node * right;
};

// Do *NOT* use typedef, I Love struct
#define generic_tree binary_tree_node

/*
 * Enumerate all the siblings of the node, including itself.
 * Note the macro can accept NULL as the current
 */
#define FOREACH_SIBLING_NODE_START(current, _node) {\
    struct binary_tree_node * _sibling = (current); \
    if (_sibling) \
        for (; _sibling->parent && \
            (_sibling->parent->right == _sibling); \
            _sibling = _sibling->parent); \
    for(; _sibling; _sibling = _sibling->right) { \
        (_node) = _sibling;


#define FOREACH_SIBLING_NODE_END() }}

/*
 * Enumerate all the children of a node
 */
#define FOREACH_CHILD_NODE_START(current, _node) {\
    struct binary_tree_node * _first_child = (current)->left; \
    FOREACH_SIBLING_NODE_START(_first_child, _node) \


#define FOREACH_CHILD_NODE_END() \
    FOREACH_SIBLING_NODE_END(); \
}

int
add_sibling(struct generic_tree * current, struct generic_tree * node);

int
add_child(struct generic_tree * current, struct generic_tree * node);


#endif

