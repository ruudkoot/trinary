/******************************************************************************/
/* Symetric Multi-Processing support for the IA-32 Architecture               */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* The trees used in the core have two distinct properties:                   */
/*                                                                            */
/*      - It is highly likely that nodes are added sequentialy.               */
/*      - Trees are modified rarely and search often.                         */
/*                                                                            */
/* The first argument instantly rules out ordinary / unbalanced, because this */
/* would make them even more inefficient than linked lists. The second fact   */
/* can be interpreted as an argument for and as an argument agains splay      */
/* trees. The argument agains is the fact that splay trees modify the tree    */
/* when searching it, causing extra memory bandwidth usage and secondly       */
/* take longer on average and much longer in a worst-case scenario. The       */
/* argument for splays are the fact that they function as a sort of cache,    */
/* that gives access to frequently used nodes faster. I don't believe the     */
/* argument for splay trees are great enough to overcome the arguments        */
/* against spays trees, because most searches through a trees are releativly  */
/* random, or sequential, both of which defeat the splay trees 'cache'.       */
/******************************************************************************/

/******************************************************************************/
/* tree     indexed binary search tree                                        */
/*          unbalanced binary search tree                                     */
/* map      balanced binary search tree                                       */
/* splay    splayed binary search tree                                        */
/******************************************************************************/

/******************************************************************************/
/* Indexed Binary Search Trees are search trees with leaf that leafes which   */
/* are keyed from 0 to n, without interruptions. This makes them function as  */
/* ordinary arrays / lists and gives them some special properties, that make  */
/* them quite fast to use.                                                    */
/******************************************************************************/

typedef struct
{
    unsigned key;
    void     *left;
    void     *right;
    void     *data;
} tree;

void tree_init(tree *t)
{
    t->key = 0;
    t->left = 0;
    t->right = 0;
    t->data = 0;
}

void* tree_find(tree *t, unsigned i)
{
    while (i != 0)
    {
        if (i % 2 == 0) t = t->left; else t = t->right;
        i >>= 1;
    }
}

void* tree_insert(tree *t, unsigned i)
{
    
}