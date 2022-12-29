#ifndef __LIBVECTOR_H
#define __LIBVECTOR_H 1

#include <sys/types.h>
#include <stdlib.h>

typedef struct {
	u_int32_t size;
	u_int32_t capacity;
	void **array;
} vector_t;

vector_t* vec_new(void);
vector_t* vec_new_size(u_int32_t size);

void vec_push_back(vector_t* vec, void* value);
void* vec_pop_back(vector_t* vec);

void* vec_get(vector_t* vec, u_int32_t index);
void* vec_set(vector_t* vec, u_int32_t index, void *value);

void* vec_front(vector_t* vec);
void* vec_back(vector_t* vec);

u_int32_t vec_size(vector_t* vec);

void vec_shrink(vector_t* vec);
void vec_free(vector_t* vec);

// TODO: Insert elements/vectors at indices.

#endif