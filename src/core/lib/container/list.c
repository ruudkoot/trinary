/******************************************************************************/
/*                                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

typedef struct
{
    void* next;
    void* previous;
    void* data;
} list;

/******************************************************************************/
/* list_init (Initialize List Item)                                           */
/* Initializes a new list item.                                               */
/*                                                                            */
/* l: Points to the list that needs to be inititialized                       */
/*                                                                            */
/* For a normal list it is enough to make all records NULL.                   */
/******************************************************************************/
void list_init(list* l)
{
    l->next     = 0;
    l->previous = 0;
    l->data     = 0;
}

/******************************************************************************/
/* list_get (Get List Item)                                                   */
/* Get a pointer to the data associated with the list item.                   */
/*                                                                            */
/* l: */
void* list_get(list* l, unsigned n)
{
    while (n--) if (!(l = l->next)) return 0;
    return l->data;
}

void list_set(list* l, unsigned n, void* d)
{
    while (n--) if (!(l = l->next)) return;
    l->data = d;
}

unsigned list_find(list* l, void* a)
{
    unsigned n;
    do
    {
        n++;
        if (l->data == a) return n;
    } while (l = l->next);
}

void list_insert(list* l, unsigned n)
{
    while (n--) if (!(l = l->next));
}

/*list* list_delete(list* l, unsigned n)
{
    while (n--) if (!(l = l->next)) return 0;
    l->next->previous = l->previous;
    l->previous->next = l->next;
    return l;
}*/

list* list_forward(list* l, unsigned n)
{
    while (n--) if (!(l = l->next)) return 0;
    return l;
}

list* list_backward(list* l, unsigned n)
{
    while (n--) if (!(l = l->previous)) return 0;
    return l;
}

list* list_start(list* l)
{
    while (l->previous) l = l->previous;
}

list* list_end(list* l)
{
    while (l->next) l = l->next;
}
