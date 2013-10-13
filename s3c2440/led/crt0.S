   

.text
.global _start
_start:
            ldr     r0, =0x53000000     @ WATCHDOG adr
            mov     r1, #0x0                     
            str   r1, [r0] 
            ldr     sp, =1024*4 				@ only 4k on chip memory   
            bl      main                
halt_loop:
            b       halt_loop
