
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
}
