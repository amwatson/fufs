#include "fu.h"

/* device file, length, length is multiple of 4k, divide by that to get blocks,
       make struct 
       initial free inode list */

// first 32 bits cluster, next 8 bits are index
int main (int length, char *device) {
    // if length is not a multiple of 4k, return with error
    if (length%CLUSTER_SIZE) {
        return 0;
    }  

    struct fu_super_block *super_block;
    super_block->s_cluster_head = -1;
    super_block->s_inode_head = 0;
    super_block->s_inode_head_ind = 2;
    super_block->s_inodes_count = 1;
    super_block->s_blocks_count = length/BLOCK_SIZE;
    super_block->s_free_blocks_count = 1;
    super_block->s_first_data_block = 1;
    super_block->s_blocks_per_cluster = CLUSTER_SIZE/BLOCK_SIZE;
    super_block->s_inode_size = INODE_SIZE;
    super_block->s_block_cluster_nr = 0; // why is this even here? 

    struct fu_inode *root_inode = {0};

    int free_inodes_count = CLUSTER_SIZE/INODE_SIZE - 2;
    struct fu_free_inode free_inode_list[free_inodes_count];
    int i;
    for (i = 1; i < (free_inodes_count + 1); i++) {
        if (i) {
            free_inode_list[i].prev = 0;
            free_inode_list[i].prev_ind = i - 1;
        } else {
            free_inode_list[i].prev = -1;
            free_inode_list[i].prev_ind = -1;
                       
        }
        free_inode_list[i].next = 0;
        free_inode_list[i].next_ind = i + 1;
    }
    free_inode_list[free_inodes_count + 1].next = -1;
    free_inode_list[free_inodes_count + 1].next_ind = -1;
    
    FILE *dev_file = fopen(device, "wb");
    fwrite(super_block, sizeof(struct super_block *), 1, dev_file);
    fwrite(root_inode, INODE_SIZE, 1, dev_file);
    fwrite(free_inode_list, INODE_SIZE, free_inodes_count, dev_file);
}
