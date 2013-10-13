     
.extern     main
.text 
.global _start 
_start:
@ 0x00     
    b   Reset

@ 0x04
HandleUndef:
    b   HandleUndef 
 
@ 0x08
HandleSWI:
    b   HandleSWI

@ 0x0c
HandlePrefetchAbort:
    b   HandlePrefetchAbort

@ 0x10
HandleDataAbort:
    b   HandleDataAbort

@ 0x14
HandleNotUsed:
    b   HandleNotUsed

@ 0x18
    b   HandleIRQ

@ 0x1c
HandleFIQ:
    b   HandleFIQ

Reset:                      @in svc
    ldr sp, =4096           
    bl  disable_watch_dog   
    
    msr cpsr_c, #0xd2       @ enter int mode   M4~M0 10010
    ldr sp, =3072           @ int mod sp

    msr cpsr_c, #0xd3       @ enter svc mode   M4~M0 10011
    ldr sp, =4096           
                           

    msr cpsr_c, #0x53       @ M4~M0 10011  disable FIQ
    
    
    
    bl  clock_init          
    bl  memsetup           
    bl  copy_steppingstone_to_sdram     
    ldr pc, =on_sdram                   
on_sdram:
    ldr sp, =0x34000000     @ 设置栈指针
    ldr lr, =halt_loop      @ 设置返回地址
    ldr pc, =main           @ 调用main函数

halt_loop:
    b   halt_loop

HandleIRQ:
    sub lr, lr, #4                  @ 计算返回地址
    stmdb   sp!,    { r0-r12,lr }   @ 保存使用到的寄存器
                                    @ 注意，此时的sp是中断模式的sp
                                    @ 初始值是上面设置的3072
    
    ldr lr, =int_return             @ 设置调用ISR即EINT_Handle函数后的返回地址  
  
int_return:
    ldmia   sp!,    { r0-r12,pc }^  @ 中断返回, ^表示将spsr的值复制到cpsr
    
