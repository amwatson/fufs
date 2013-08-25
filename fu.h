#include <stdint.h>
#include <stdio.h>
#define BLOCK_SIZE 1  // TODO change to size of sector
#define CLUSTER_SIZE 4000
#define INODE_SIZE 128
#define NUM_DIRECT_BLOCKS 19

struct fu_inode {
  uint8_t is_free; // flag that denotes whether or not the inode is free
  uint16_t mode;
  uint16_t link_count;
  uint32_t uid;
  uint32_t gid;
  uint32_t size;
  uint32_t atime;
  uint32_t ctime;
  uint32_t utime;
  uint32_t dtime;
  uint32_t flags;
  uint32_t block_count;
  uint32_t directs[NUM_DIRECT_BLOCKS];
  uint32_t si_cluster;
  uint32_t di_cluster;
  uint8_t si_index;
  uint8_t di_index;
  uint16_t num_inodes; // -1 if inode, number of files if directory
};

struct fu_si_block {
  uint32_t directs[32];
};

struct fu_di_block {
  uint32_t clusters[25];
  uint8_t indices[25];
};

struct fu_super_block {
    // add freelist heads
    uint32_t s_cluster_head; // head of the free-cluster list
    uint32_t s_inode_head; //  head of the free-inode list
    uint8_t s_inode_head_ind; // index into th free-inode list
    uint8_t s_uuid [16]; // 128-bit filesystem identifier
    uint32_t s_inodes_count; // Total number of inodes in use
    uint64_t s_blocks_count; // Filesystem size in blocks
    uint32_t s_free_blocks_count; // Free blocks counter
    // uint32_t s_free_inodes_count; // Free inodes counter
    uint32_t s_first_data_block; // Number of first useful block (always 1)
    uint32_t s_blocks_per_cluster; // Number of blocks per cluster
    uint16_t s_inode_size; // Size of on-disk inode structure
    uint16_t s_block_cluster_nr; // Block cluster number of this superblock
    uint16_t s_padding1; // Alignment to word
    uint8_t s_reserved [47]; // Nulls to pad out 128 bytes
};

// a linked-list containing free inodes
struct fu_free_inode {
    uint32_t prev; // offset to previous cluster
    uint32_t next; // offset to next cluster
    uint8_t prev_ind; // index into previous cluster
    uint8_t next_ind; // index into next cluster
    uint8_t padding [118]; // pads out to 128 bytes
};

struct fu_dir_entry {
    char name [64]; // name of entry
    struct fu_inode *inode;     
};

// sizeof() doesn't work on struct
struct fu_dir {
    int length;
    struct fu_dir_entry *file_list; // list of files in directory
};
