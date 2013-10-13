     
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
                           

    bl  init_led            @ init gpio 
    bl  init_irq            
    msr cpsr_c, #0x53       @ M4~M0 10011  disable FIQ
    
    ldr lr, =halt_loop     
    ldr pc, =main          
halt_loop:
    b   halt_loop

HandleIRQ:
    sub lr, lr, #4                  @ 计算返回地址
    stmdb   sp!,    { r0-r12,lr }   @ 保存使用到的寄存器
                                    @ 注意，此时的sp是中断模式的sp
                                    @ 初始值是上面设置的3072
    
    ldr lr, =int_return             @ 设置调用ISR即EINT_Handle函数后的返回地址  
    ldr pc, =EINT_Handle            @ 调用中断服务函数，在interrupt.c中
int_return:
    ldmia   sp!,    { r0-r12,pc }^  @ 中断返回, ^表示将spsr的值复制到cpsr
    
