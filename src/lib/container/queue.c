/******************************************************************************/
/* Trinary Run-Time Library : Container : Queue                               */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* The queue is a FIFO stack. You can push items on it and pop items off, but */
/* the item that was pushed on first, will als be popped of first.            */
/******************************************************************************/

typedef struct
{
    void    *data;
    void    *previous;
} queue_node;

typedef struct
{
    queue_node  *start;
    queue_node  *end;
} queue;


/******************************************************************************/
/* queue_init - Initialize Queue                                              */
/*                                                                            */
/* queue            The Queue that needs to be initialized.                   */
/*                                                                            */
/* This function transparently initializes the queue structure. It should not */
/* be used to clear a queue that already has items popped on, because that    */
/* would result in memory leaks.                                              */
/******************************************************************************/
void queue_init(queue *queue)
{
    queue->start    = 0;
    queue->end      = 0;
}

/******************************************************************************/
/* queue_push - Push an item on the Queue                                     */
/*                                                                            */
/* queue            The on which you want to push the item.                   */
/* item             The item that needs to be puished on the Queue.           */
/*                                                                            */
/* The item will be pushed on the back of the queue. Note that you have to    */
/* make sure you which type of item you push onto the stack, because there is */
/* no type checking done.                                                     */
/******************************************************************************/
void queue_push(queue *queue, void* item)
{
    queue_node  *node;

    node = malloc(sizeof(queue_node));

    node->data      = item;
    node->previous  = 0;
        
    if (queue->start != 0)
        queue->end->previous = node;
    else
        queue->start = node;

    queue->end = node;
}

/******************************************************************************/
/* queue_pop - Pop an item fron the Queue                                     */
/*                                                                            */
/* queue            The from which you want to pop the item.                  */
/*                                                                            */
/* return           A pointer to the item popped off, or 0 if the queue is    */
/*                  empty.                                                    */
/******************************************************************************/
void* queue_pop(queue *queue)
{
    void        *data;
    queue_node  *node;

    if (queue->start != 0)
    {
        node            = queue->start;
        queue->start    = node->previous;
        data            = node->data;

        free(node);
    }
    else
    {
        data = 0;
    }

    return data;
}