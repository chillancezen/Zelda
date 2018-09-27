/*
 * Copyright (c) 2018 Jie Zheng
 */
#ifndef _VFS_H
#define _VFS_H
#include <lib/include/types.h>
#include <filesystem/include/file.h>
#include <filesystem/include/filesystem.h>

#define MOUNT_ENTRY_SIZE 256 // The maximum entries is 256

/*
 * http://man7.org/linux/man-pages/man2/stat.2.html
 */
struct mount_entry {
    uint8_t mount_point[MAX_PATH];
    struct file_system * fs;
    uint32_t valid:1;
};

void vfs_init(void);
void dump_mount_entries(void);
int canonicalize_path_name(uint8_t * dst, const uint8_t * src);
int register_file_system(uint8_t * mount_point, struct file_system * fs);

struct mount_entry *
search_mount_entry(const uint8_t * path);

struct file *
do_vfs_open(const uint8_t * path, uint32_t flags, uint32_t mode);

void
split_path(uint8_t * path,
    uint8_t **array,
    int32_t * iptr);

#endif
