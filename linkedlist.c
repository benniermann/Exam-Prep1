#include "linkedlist.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

SList *slist_create(void)
{
    SList* new_list = malloc(sizeof(SList));
    if(!new_list) return NULL;

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}

void slist_destroy(SList *list)
{
    if(list == NULL) return;
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    free(list);
}

int slist_push_front(SList *list, int value)
{
    return NULL;
}

int slist_push_back(SList *list, int value)
{
    return NULL;
}

int slist_pop_front(SList *list, int *err)
{
    return NULL;
}

int slist_remove_at(SList *list, int index)
{
    return NULL;
}

void slist_insertion_sort(SList *list)
{
    
}

void slist_reverse(SList *list)
{
    
}

void slist_print(const SList *list)
{
    
}

int *slist_to_array(const SList *list)
{
    return NULL;
}
