
#define NUM_DIRECT_BLOCKS 19

struct fu_inode {
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
};

struct fu_si_block {
  uint32_t directs[32];
};

struct fu_di_block {
  uint32_t clusters[25];
  uint8_t indices[25];
}

struct fu_super_block {
    // add freelist heads
    uint_32_t s_cluster_head; // head of the free-cluster list
    uint_32_t inode_head; //  head of the free-inode list
    uint_8_t inode_head_ind; // index into th free-inode list
    uint_8_t s_uuid [16]; // 128-bit filesystem identifier
    char s_volume_name [16]; // Volume name
    uint_8_t s_prealloc_blocks; // Number of blocks to preallocate
    uint_8_t s_prealloc_dir_blocks; // Number of blocks to preallocate for directories
    uint_32_t s_inodes_count; // Total number of inodes
    uint_32_t s_blocks_count; // Filesystem size in blocks
    uint_32_t s_free_blocks_count; // Free blocks counter
    uint_32_t s_free_inodes_count; // Free inodes counter
    uint_32_t s_first_data_block; // Number of first useful block (always 1)
    uint_32_t s_log_block_size; // Block size
    uint_32_t s_blocks_per_cluster; // Number of blocks per cluster
    uint_32_t s_inodes_per_cluster; // Number of inodes per cluster
    uint_16_t s_inode_size; // Size of on-disk inode structure
    uint_16_t s_block_cluster_nr; // Block cluster number of this superblock
    uint_16_t s_padding1; // Alignment to word
    uint_8_t s_reserved [47]; // Nulls to pad out 128 bytes
}

// a linked-list containing free inodes
struct fu_free_inode {
    uint_32_t prev; // pointer to previous cluster
    uint_32_t next; // pointer to next cluster
    uint_8_t prev_ind; // index into previous cluster
    uint_8_t next_ind; // index into next cluster
    uint_8_t padding [118]; // pads out to 128 bytes
}

struct fu_dir_entry {
    char name [64]; // name of entry
    struct fu_inode *inode;     
}

// sizeof() doesn't work on struct
struct fu_dir {
    int length;
    struct fu_dir_entry *file_list; // list of files in directory
}
