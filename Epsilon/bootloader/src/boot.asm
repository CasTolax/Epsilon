; Bootloader (16-bit → 32-bit protected mode)
; Castolax style fixed version
;The parts I couldn't do were handled by AI
; fix problem: ChatGPT

[BITS 16]
[ORG 0x7C00]

CODE_SEG equ 0x08
DATA_SEG equ 0x10

KERNEL_LOAD_SEG equ 0x100   

;must be 0x00100000 or 0x00100. you can test so you find the correct adress.
; but also look at the this sites... OSdev Wiki: Memory Map(x86)
KERNEL_START_ADDR equ 0x00100000  ; must be 

start:
    cli

    ; Segment setup
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    sti

    ; -------------------------
    ; Disk read (INT 13h)
    ; -------------------------
    mov ax, KERNEL_LOAD_SEG
    mov es, ax
    xor bx, bx

    mov ah, 0x02        ; read sectors
    mov al, 8           ; sector count
    mov ch, 0           ; cylinder
    mov dh, 0           ; head
    mov cl, 2           ; sector (boot sector sonrası)
    mov dl, 0x80        ; first HDD

    int 0x13
    jc disk_read_error

    mov si, msg
    call print_msg

    ; -------------------------
    ; Enable A20 (fast gate)
    ; -------------------------
    in al, 0x92
    or al, 2
    out 0x92, al

    ; -------------------------
    ; Load GDT
    ; -------------------------
    cli
    lgdt [gdt_descriptor]

    ; -------------------------
    ; Enter protected mode
    ; -------------------------
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CODE_SEG:pmode_start

; -------------------------
; Error handler
; -------------------------
disk_read_error:
    hlt
    jmp disk_read_error

; -------------------------
; GDT
; -------------------------
gdt_start:
    dq 0x0000000000000000

    ; Code segment
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

    ; Data segment
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

print_msg:
    pusha
    mov ah, 0x0E
    mov bx, 0x0007
.print_loop:
    lodsb
    cmp al, 0
    je .print_done
    int 0x10
    jmp .print_loop
.print_done:
    popa
    ret

msg db 'BOOT OK!', 0

; -------------------------
; 32-bit protected mode
; -------------------------
[BITS 32]

pmode_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x9C000
    mov esp, ebp

    ; Jump to kernel
    jmp KERNEL_START_ADDR

; -------------------------
; Boot signature
; -------------------------
times 510-($-$$) db 0
dw 0xAA55