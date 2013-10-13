
#define WTCON           (*(volatile unsigned long *)0x53000000)

#define MEM_CTL_BASE    0x48000000


void disable_watch_dog(void)
{
    WTCON = 0; 
}

void memsetup(void)
{
     unsigned long  const    mem_cfg_val[]={ 0x22011110,     //BWSCON
                                            0x00000700,     //BANKCON0
                                            0x00000700,     //BANKCON1
                                            0x00000700,     //BANKCON2
                                            0x00000700,     //BANKCON3  
                                            0x00000700,     //BANKCON4
                                            0x00000700,     //BANKCON5
                                            0x00018005,     //BANKCON6
                                            0x00018005,     //BANKCON7
                                            0x008C07A3,     //REFRESH
                                            0x000000B1,     //BANKSIZE
                                            0x00000030,     //MRSRB6
                                            0x00000030,     //MRSRB7
                                    };
    int     i = 0;
    volatile unsigned long *p = (volatile unsigned long *)MEM_CTL_BASE;
    for(; i < 13; i++)
        p[i] = mem_cfg_val[i];
}

/*
 * 将第二部分代码复制到SDRAM
 */
void copy_2th_to_sdram(void)
{
    unsigned int *pdwSrc  = (unsigned int *)2048;
    unsigned int *pdwDest = (unsigned int *)0x30004000;
    
    while (pdwSrc < (unsigned int *)4096)
    {
        *pdwDest = *pdwSrc;
        pdwDest++;
        pdwSrc++;
    }
}

/*
 * 设置页表
 */
void create_page_table(void)
{

#define MMU_FULL_ACCESS     (3 << 10)   
#define MMU_DOMAIN          (0 << 5)    
#define MMU_SPECIAL         (1 << 4)   
#define MMU_CACHEABLE       (1 << 3)    /* cacheable */
#define MMU_BUFFERABLE      (1 << 2)    /* bufferable */
#define MMU_SECTION         (2)         
#define MMU_SECDESC         (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | \
                             MMU_SECTION)
#define MMU_SECDESC_WB      (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | \
                             MMU_CACHEABLE | MMU_BUFFERABLE | MMU_SECTION)
#define MMU_SECTION_SIZE    0x00100000

    unsigned long virtuladdr, physicaladdr;
    unsigned long *mmu_tlb_base = (unsigned long *)0x30000000;
    
    // 0~1M vir addr and phy addr is the same
    virtuladdr = 0;
    physicaladdr = 0;
    *(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | \
                                            MMU_SECDESC_WB;

    // map 0x56000000 to A0000000  1M
    virtuladdr = 0xA0000000;
    physicaladdr = 0x56000000;
    *(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | \
                                            MMU_SECDESC;

   
     // 0xB0000000～0xB3FFFFFF  to 0x30000000～0x33FFFFFF
    virtuladdr = 0xB0000000;
    physicaladdr = 0x30000000;
    while (virtuladdr < 0xB4000000)
    {
        *(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | \
                                                MMU_SECDESC_WB;
        virtuladdr += 0x100000;
        physicaladdr += 0x100000;
    }
}


void mmu_init(void)
{
    unsigned long ttb = 0x30000000;
__asm__(
    "mov    r0, #0\n"
    "mcr    p15, 0, r0, c7, c7, 0\n"    // icache dcache
    
    "mcr    p15, 0, r0, c7, c10, 4\n"   
    "mcr    p15, 0, r0, c8, c7, 0\n"   
    
    "mov    r4, %0\n"                   // r4 = page table base addr 
    "mcr    p15, 0, r4, c2, c0, 0\n"   
    
    "mvn    r0, #0\n"                   
    "mcr    p15, 0, r0, c3, c0, 0\n"     
  
    "mrc    p15, 0, r0, c1, c0, 0\n"   
    
   
                                      
    "bic    r0, r0, #0x3000\n"          
    "bic    r0, r0, #0x0300\n"          
    "bic    r0, r0, #0x0087\n"         

    "orr    r0, r0, #0x0002\n"         
    "orr    r0, r0, #0x0004\n"         // start DCaches 
    "orr    r0, r0, #0x1000\n"         // start ICaches */
    "orr    r0, r0, #0x0001\n"         //eable 
    
    "mcr    p15, 0, r0, c1, c0, 0\n"    
  	:
    : "r" (ttb) );
}
