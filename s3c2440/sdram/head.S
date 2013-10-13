 .equ        MEM_CTL_BASE,       0x48000000
.equ        SDRAM_BASE,         0x30000000

.text
.global _start
_start:
    bl  disable_watch_dog               @ 关闭WATCHDOG，否则CPU会不断重启
    bl  memsetup                        @ 设置存储控制器
   	bl  copy_steppingstone_to_sdram     @ 复制代码到SDRAM中
    ldr pc, =on_sdram                   @ 跳到SDRAM中继续执行
on_sdram:
    ldr sp, =0x34000000                 @ 设置堆栈
    bl  main
halt_loop:
    b   halt_loop

disable_watch_dog:   
    mov r1,     #0x53000000
    mov r2,     #0x0
    str r2,     [r1]
    mov pc,     lr      @ 返回

copy_steppingstone_to_sdram:
    	@copy the steppingstone 4k to 0x30000000
    
    mov r1, #0
    ldr r2, =SDRAM_BASE
    mov r3, #4*1024
1:  
    ldr r4, [r1],#4     @r4 = *r1, r1+=4
    str r4, [r2],#4    
    cmp r1, r3          
    bne 1b            
    mov pc,     lr      

memsetup: 
    mov r1,     #MEM_CTL_BASE      
    adrl    r2, mem_cfg_val         
    add r3,     r1, #52             @ 13*4 = 52
1:  
    ldr r4,     [r2], #4            
    str r4,     [r1], #4            
    cmp r1,     r3                 
    bne 1b                         
    mov pc,     lr               


.align 4
mem_cfg_val:   
    .long   0x22011110      @ BWSCON     BANK6 32 DATA WIDTH
    .long   0x00000700      @ BANKCON0
    .long   0x00000700      @ BANKCON1
    .long   0x00000700      @ BANKCON2
    .long   0x00000700      @ BANKCON3  
    .long   0x00000700      @ BANKCON4
    .long   0x00000700      @ BANKCON5
    .long   0x00018005      @ BANKCON6   0x3000000  K4S561632  Col Adr Num 9
    .long   0x00018005      @ BANKCON7
    .long   0x008C07A3      @ REFRESH
    .long   0x000000B1      @ BANKSIZE
    .long   0x00000030      @ MRSRB6  
    .long   0x00000030      @ MRSRB7
