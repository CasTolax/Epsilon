[BITS 32]

global _start
extern kernel_main

_start:
    ; Test: Write 'K' to screen to verify we're in kernel
   ; mov byte [0xB8000], 'K'
   ; mov byte [0xB8001], 0x0F
    
    call kernel_main
    jmp $

times 512 - ($ - $$) db 0