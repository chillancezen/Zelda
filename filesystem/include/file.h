/*
 * Copyright (c) 2018 Jie Zheng
 */
#include <lib/include/types.h>
#include <lib/include/generic_tree.h>
#define MAX_PATH 256

struct file_operation;

enum FILE_TYPE{
    FILE_TYPE_NONE = 0,
    FILE_TYPE_MARK,
    FILE_TYPE_REGULAR,
    FILE_TYPE_DIR
};
// The definition of file descriptor
struct file {
    uint8_t name[MAX_PATH];
    struct generic_tree fs_node;
    uint8_t type;
    uint32_t mode;
    /*
     * The reference_count is increased each time the file is opened.
     * It's decreased when the file is released.
     */
    uint32_t refer_count;
    struct file_operation * ops;
    void * priv;
};

// The per-task definition of file entry 
struct file_entry {
    struct file * file;
    uint32_t offset; 
    uint32_t valid:1; 
};

/*
 * https://github.com/freebsd/freebsd/blob/master/sys/sys/file.h#L128
 */

struct file_operation {
    int32_t (*open)(struct file * _file, uint32_t mode);
    int32_t (*read)(struct file * _file, uint32_t offset, void * buffer, int size);
    int32_t (*write)(struct file * _file, uint32_t offset, void * buffer, int size);
    int32_t (*truncate)(struct file * _file, int offset);
    int32_t (*close)(struct file * _file);
    int32_t (*ioctl)(struct file * _file, uint32_t request, ...);
};
