#include "encode.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdio.h>

char *caesar_encode(const char *text, int shift)
{
    if (text == NULL) return NULL;

    size_t len = strlen(text);
    char *res = malloc(len + 1);
    if (res == NULL) return NULL;

    shift = shift % 26;
    if (shift < 0) shift += 26;

    for (size_t i = 0; i < len; i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') {
            res[i] = 'a' + (c - 'a' + shift) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            res[i] = 'A' + (c - 'A' + shift) % 26;
        } else {
            res[i] = c;
        }
    }
    res[len] = '\0';

    return res;
}

char *caesar_decode(const char *text, int shift)
{
    if (text == NULL) return NULL;
    
    int s = shift % 26;
    if (s < 0) s += 26;
    
    return caesar_encode(text, (26 - s) % 26);
}

char *xor_encode(const char *text, uint8_t key)
{
    if (text == NULL) return NULL;

    size_t len = strlen(text);
    char *res = malloc(len + 1);
    if (res == NULL) return NULL;

    for (size_t i = 0; i < len; i++) {
        res[i] = text[i] ^ key;
    }
    res[len] = '\0';

    return res;
}

int is_rotation(const char *a, const char *b)
{
    if (a == NULL || b == NULL) return 0;

    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    if (len_a != len_b) return 0;
    if (len_a == 0) return 1;

    char *concat = malloc(len_a * 2 + 1);
    if (concat == NULL) return 0;

    strcpy(concat, a);
    strcat(concat, a);

    int result = (strstr(concat, b) != NULL) ? 1 : 0;
    
    free(concat);
    return result;
}

char *rle_encode(const char *text)
{
    if (text == NULL) return NULL;

    size_t len = strlen(text);
    if (len == 0) {
        char *res = malloc(1);
        if (res) res[0] = '\0';
        return res;
    }

    char *res = malloc(len * 12 + 1);
    if (res == NULL) return NULL;

    int count = 1;
    char current = text[0];
    char buf[32];
    size_t pos = 0;

    for (size_t i = 1; i <= len; i++) {
        if (i < len && text[i] == current) {
            count++;
        } else {
            int w = sprintf(buf, "%d%c", count, current);
            strcpy(res + pos, buf);
            pos += w;
            if (i < len) {
                current = text[i];
                count = 1;
            }
        }
    }

    char *shrink = realloc(res, pos + 1);
    return shrink ? shrink : res;
}

char *rle_decode(const char *encoded)
{
    if (encoded == NULL) return NULL;
    
    if (encoded[0] == '\0') {
        char *res = malloc(1);
        if (res) res[0] = '\0';
        return res;
    }

    size_t total_len = 0;
    size_t i = 0;
    size_t enc_len = strlen(encoded);

    while (i < enc_len) {
        if (!isdigit((unsigned char)encoded[i])) return NULL;
        
        int count = 0;
        while (i < enc_len && isdigit((unsigned char)encoded[i])) {
            count = count * 10 + (encoded[i] - '0');
            i++;
        }
        
        if (count == 0 || i >= enc_len) return NULL;
        
        total_len += count;
        i++;
    }

    char *res = malloc(total_len + 1);
    if (res == NULL) return NULL;

    i = 0;
    size_t pos = 0;
    while (i < enc_len) {
        int count = 0;
        while (i < enc_len && isdigit((unsigned char)encoded[i])) {
            count = count * 10 + (encoded[i] - '0');
            i++;
        }
        
        char c = encoded[i];
        i++;
        
        for (int k = 0; k < count; k++) {
            res[pos++] = c;
        }
    }
    res[total_len] = '\0';

    return res;
}