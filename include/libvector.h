#ifndef __LIBVECTOR_H
#define __LIBVECTOR_H 1

#include <sys/types.h>
#include <stdlib.h>

struct vector {
	u_int32_t size;
	u_int32_t capacity;
	void **array;
};

struct vector* vec_new(void);
struct vector* vec_new_size(u_int32_t size);

void vec_push_back(struct vector* vec, void* value);
void* vec_pop_back(struct vector* vec);

void* vec_get(struct vector* vec, u_int32_t index);
void* vec_set(struct vector* vec, u_int32_t index, void *value);

void* vec_front(struct vector* vec);
void* vec_back(struct vector* vec);

u_int32_t vec_size(struct vector* vec);

void vec_shrink(struct vector* vec);
void vec_free(struct vector* vec);

// TODO: Insert elements/vectors at indices.

#endif