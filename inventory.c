#include "inventory.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Warehouse *warehouse_create(void)
{
    Warehouse *w = malloc(sizeof(Warehouse) * 4);
    if (!w) 
    {
        return NULL;
    }
    w->products = NULL;
    w->count = 0;
    w->capacity = 4;
    w->next_id = 1;
    return w;

}

void warehouse_destroy(Warehouse *w)
{
    if (!w) 
    {
        return;
    }
    free(w->products);
    free(w);
}

int warehouse_add_product(Warehouse *w, const char *name, double price, int quantity)
{
    if (!w || !name) {
        return -1;
    }
    if (w->count >= w->capacity) {
        int new_capacity = w->capacity == 0 ? 4 : w->capacity * 2;
        Product *new_products = realloc(w->products, new_capacity * sizeof(Product));
        if (!new_products) 
        {
            return -1;
        }
        w->products = new_products;
        w->capacity = new_capacity;
    }
    w->products[w->count].id = w->next_id;
    w->products[w->count].price = price;
    w->products[w->count].quantity = quantity;
    strncpy(w->products[w->count].name, name, 63);
    w->products[w->count].name[63] = '\0';
    w->next_id++;
    w->count++;
    return 0;
}

int warehouse_remove_by_id(Warehouse *w, int id)
{
    if (!w) {
        return -1;
    }
    for (int i = 0; i < w->count; i++) {
        if (w->products[i].id == id) {
            for (int j = i; j < w->count - 1; j++) {
                w->products[j] = w->products[j + 1];
            }
            w->count--;
            return 0;
        }
    }
    return -1;

}

Product *warehouse_find_by_name(Warehouse *w, const char *query)
{
    if (!w || !query) {
        return NULL;
    }
    for (int i = 0; i < w->count; i++) {
        if (strcmp(w->products[i].name, query) == 0) {
            return &w->products[i];
        }
    }
    return NULL;
}

double warehouse_total_value(const Warehouse *w)
{
    if (!w) {
        return 0.0;
    }
    double total = 0;
    for (int i = 0; i < w->count; i++) {
        total += w->products[i].price * w->products[i].quantity;
    }
    return total;
}

void warehouse_sort_by_price(Warehouse *w)
{
    if (!w || w->count <= 1) {
        return;
    }
    for (int i = 0; i < w->count - 1; i++) {
        for (int j = 0; j < w->count - i - 1; j++) {
            if (w->products[j].price > w->products[j + 1].price ||
                (w->products[j].price == w->products[j + 1].price && w->products[j].id > w->products[j + 1].id)) {
                Product temp = w->products[j];
                w->products[j] = w->products[j + 1];
                w->products[j + 1] = temp;
            }
        }
    }
}

void warehouse_print(const Warehouse *w)
{
    if (!w) {
        return;
    }
    for (int i = 0; i < w->count; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n", w->products[i].id, w->products[i].name, w->products[i].price, w->products[i].quantity);
    }
}

