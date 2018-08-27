/*
 * Copyright (c) 2018 Jie Zheng
 */

#include <lib/include/string.h>

void
memset(void * dst, uint8_t target, int32_t size)
{
    uint8_t * ptr = (uint8_t *)dst;
    int idx =0 ;
    for(idx = 0; idx < size; idx++) {
        ptr[idx] = target;
    }
}


void
strcpy(uint8_t * dst, const uint8_t * src)
{
    int idx = 0;
    for(; (dst[idx] = src[idx]); idx++);
}

/*
 * This is to judge whether the target string starts with sub string
 * non-Zero indicates check failure.
 */
int
start_with(const uint8_t * target, const uint8_t * sub)
{
    int idx = 0;
    for(; sub[idx]; idx++)
        if(target[idx] != sub[idx])
            break;
    return sub[idx];
}
