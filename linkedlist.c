#include "linkedlist.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static void insertionSort(int arr[], int N)
{
    for (int i = 1; i < N; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

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
    
    SNode *current = list->head;
    while (current != NULL) 
    {
        SNode *next_node = current->next;
        free(current);
        current = next_node;
    }

    free(list);
}

int slist_push_front(SList *list, int value)
{
    if(list == NULL) return -1;

    SNode* new_node = malloc(sizeof(SNode));
    if(new_node == NULL) return -1;

    new_node->value = value;

    new_node->next = list->head;

    list->head = new_node;

    if(list->size == 0) list->tail = new_node;

    list->size++;
    
    return 0;
}

int slist_push_back(SList *list, int value)
{
    if(list == NULL) return -1;

    SNode* new_node = malloc(sizeof(SNode));
    if(new_node == NULL) return -1;

    new_node->value = value;

    new_node->next = NULL;

    if(list->size == 0)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;
    
    return 0;
}

int slist_pop_front(SList *list, int *err)
{
    if(list == 0 || list->size == 0)
    {
        if(err != NULL)
        {
            *err = -1;
        }
        return 0;
    }

    SNode* remove = list->head;
    int return_value = remove->value;

    list->head = remove->next;

    list->size--;

    if(list->size == 0) list->tail = NULL;

    free(remove);
    
    if (err != NULL) 
    {
        *err = 0;
    }  

    return return_value;
}

int slist_remove_at(SList *list, int index)
{
    if (list == NULL || index < 0 || index >= list->size) 
    {
        return -1;
    }

    if (index == 0) 
    {
        SNode *node_to_remove = list->head;
        list->head = node_to_remove->next;
        
        list->size--;
        
        if (list->size == 0) 
        {
            list->tail = NULL;
        }
        
        free(node_to_remove);
        return 0;
    }

    SNode* prev = list->head;
    for (int i = 0; i < index - 1; i++) 
    {
        prev = prev->next;
    }

    SNode* node_to_remove = prev->next;

    prev->next = node_to_remove->next;

    if (node_to_remove == list->tail) 
    { 
        list->tail = prev;
    }

    list->size--;
    free(node_to_remove);

    return 0;
}

// int compare_snodes(const void *a, const void *b)
// {
//     SNode *node_a = *(SNode **)a;
//     SNode *node_b = *(SNode **)b;
    
//     if (node_a->value < node_b->value) return -1;
//     if (node_a->value > node_b->value) return 1;
//     return 0;
// }

// void slist_quick_sort(SList *list)
// {
//     if(list == NULL || list->size <= 1) return;

//     SNode **node_array = malloc(list->size * sizeof(SNode *));
//     if (node_array == NULL) return;

//     SNode *current = list->head;
//     for (int i = 0; i < list->size; i++) 
//     {
//         node_array[i] = current;
//         current = current->next;
//     }

//     qsort(node_array, list->size, sizeof(SNode *), compare_snodes);

//     list->head = node_array[0];

//     for (int i = 0; i < list->size - 1; i++) 
//     {
//         node_array[i]->next = node_array[i + 1];
//     }

//     node_array[list->size - 1]->next = NULL;
//     list->tail = node_array[list->size - 1];

//     free(node_array);
// }

void slist_insertion_sort(SList *list)
{
    if (list == NULL || list->size <= 1) return;

    SNode *sorted_head = NULL;
    SNode *sorted_tail = NULL;
    SNode *current = list->head;

    while (current != NULL) {
        SNode *next_node = current->next;

        if (sorted_head == NULL || current->value <= sorted_head->value) {
            current->next = sorted_head;
            sorted_head = current;
            if (sorted_tail == NULL) sorted_tail = current;
        } else {
            SNode *search = sorted_head;
            while (search->next != NULL && search->next->value < current->value) {
                search = search->next;
            }
            
            current->next = search->next;
            search->next = current;

            if (current->next == NULL) sorted_tail = current;
        }
        current = next_node;
    }

    list->head = sorted_head;
    list->tail = sorted_tail;
}

void slist_reverse(SList *list)
{
    if (list == NULL || list->size <= 1) return;

    SNode *prev = NULL;
    SNode *current = list->head;
    SNode *next = NULL;

    list->tail = list->head;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
}

void slist_print(const SList *list)
{
    if (list == NULL) {
        printf("NULL\n");
        return;
    }

    SNode *current = list->head;
    while (current != NULL) {
        printf("[%d] -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int *slist_to_array(const SList *list)
{
    if (list == NULL || list->size == 0) return NULL;

    int *array = malloc(list->size * sizeof(int));
    if (array == NULL) return NULL;

    SNode *current = list->head;
    for (int i = 0; i < list->size; i++) {
        array[i] = current->value;
        current = current->next;
    }

    return array;
}
