#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <map>
#include <list>
#include <set>
#include <queue>
#include <utility>
#include <bitset>
#include "DRAMSim2/DRAMSim.h"
#include "Vtop.h"
#include "Vtop__Dpi.h"

using std::list;
using std::set;
using std::pair;
using std::bitset;

#define KILO (1024UL)
#define MEGA (1024UL*1024)
#define GIGA (1024UL*1024*1024)

#define PAGE_SIZE       (4096UL)

// Sv48 page table entry bits (RISC-V privileged spec).  A PTE with V set and
// R/W/X all clear points at the next level; one with V and any of R/W/X is a
// leaf.  PPN starts at bit 10.
#define PTE_V           (1UL << 0)
#define PTE_R           (1UL << 1)
#define PTE_W           (1UL << 2)
#define PTE_X           (1UL << 3)
#define PTE_U           (1UL << 4)
#define PTE_A           (1UL << 6)
#define PTE_D           (1UL << 7)
#define VALID_PAGE_DIR  (PTE_V)
#define VALID_PAGE      (PTE_V|PTE_R|PTE_W|PTE_X|PTE_U|PTE_A|PTE_D)

#define SATP_MODE_SV48  (9UL << 60)
#define SATP_PPN_MASK   ((1UL << 44) - 1)

#define DRAM_OFFSET 0x80000000ULL

typedef unsigned long __uint64_t;
typedef __uint64_t uint64_t;
typedef unsigned int __uint32_t;
typedef __uint32_t uint32_t;
typedef int __int32_t;
typedef __int32_t int32_t;
typedef unsigned short __uint16_t;
typedef __uint16_t uint16_t;

class System {
    Vtop* top;

    enum { IRQ_TIMER=0, IRQ_KBD=1 };
    int interrupts;
    std::queue<char> keys;

    bool show_console;

    uint64_t load_binary(const char* filename);

    list<pair<uint64_t, pair<int, bool> > > r_queue;
    list<int> resp_queue;
    set<uint64_t> snoop_queue;
    std::map<uint64_t, std::pair<uint64_t, int> > addr_to_tag;

    void dram_read_complete(unsigned id, uint64_t address, uint64_t clock_cycle);
    void dram_write_complete(unsigned id, uint64_t address, uint64_t clock_cycle);

    bitset<GIGA/PAGE_SIZE> phys_page_used;
    uint64_t get_phys_page();
    uint64_t get_pte(uint64_t base_addr, int vpn, bool isleaf, bool& allocated);
    uint64_t load_elf_parts(int fileDescriptor, size_t size, const uint64_t virt_addr);
    void load_segment(const int fd, const size_t memsz, const size_t filesz, uint64_t virt_addr);

    DRAMSim::MultiChannelMemorySystem* dramsim;
    bool willAcceptTransaction(uint64_t addr) {
      // hack: false if /any/ memory channel can't accept transaction
      return dramsim->willAcceptTransaction();
    }
    
public:
    static System* sys;
    uint64_t max_elf_addr, dram_offset;
    uint64_t elf_phdr, elf_phnum, elf_phent;   // for the auxv, filled in by load_binary()
    uint64_t ecall_brk;

    uint64_t w_addr;
    int w_count;

    uint64_t ticks;
    int ps_per_clock;

    bool use_virtual_memory, full_system;

    void invalidate(const uint64_t phys_addr);
    uint64_t virt_to_phy(const uint64_t virt_addr);
    void read_response(uint64_t addr, int tag, bool last);

    char* ram;
    uint64_t ramsize;
    char* ram_virt;
    int ram_fd;

    System(Vtop* top, uint64_t ramsize, const char* ramelf, const int argc, char* argv[], int ps_per_clock);
    ~System();

    void console();
    void tick(int clk);
};

#endif
