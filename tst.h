/*
 * Copyright (C) Looyao
 */

#ifndef _TST_H_
#define _TST_H_

#include <sys/types.h>
#include <ngx_core.h>

typedef enum _tst_node_type tst_node_type;

enum _tst_node_type {
    tst_node_type_normal = 0,
    tst_node_type_end
};

typedef struct _tst_search_alias_node tst_search_alias_node;

struct _tst_search_alias_node {
    tst_search_alias_node  *next;
    char                   *word;
    size_t                  word_len;
};

typedef struct _tst_node tst_node;

struct _tst_node {
    tst_node               *left;
    tst_node               *center;
    tst_node               *right;
    tst_node_type           type;
    tst_node_type           alias_type;
    tst_search_alias_node  *alias;
    char                   *word;
    char                    c;
};


typedef struct _tst_search_result_node tst_search_result_node;

struct _tst_search_result_node {
    tst_search_result_node *next;
    tst_search_result_node *prev;
    char                   *word;
    size_t                  word_len;
};

typedef struct _tst_search_result tst_search_result;

struct _tst_search_result {
    size_t                  count;
    tst_search_result_node *list;
    tst_search_result_node *tail;
};


tst_node *tst_insert(tst_node *root, char *word, ngx_shm_zone_t *shm_zone);

tst_node *tst_insert_alias(tst_node *root, char *word, char *alias, ngx_shm_zone_t *shm_zone);

void tst_traverse(tst_node *p, tst_search_result *result, ngx_pool_t *pool);

tst_search_result *tst_search(tst_node *root, char *word, ngx_pool_t *pool);

void tst_destroy(tst_node *p, ngx_shm_zone_t *shm_zone);

tst_search_result *tst_search_result_init(ngx_pool_t *pool);

/*void tst_search_result_free(tst_search_result *result);*/

#endif
