GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL  _int_09_hand
GLOBAL	_int_80_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL	_read
GLOBAL	_write
GLOBAL	_setCursor
GLOBAL	_restart
GLOBAL	_in
GLOBAL	_out
GLOBAL  __stack_chk_fail
GLOBAL	_rdtsc
GLOBAL _getSeconds
GLOBAL _getMinutes
GLOBAL _getHour
GLOBAL _set_CR

EXTERN  int_08
EXTERN  int_09
EXTERN	int_80

SECTION .text


_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret

_mascaraPIC1:			; Escribe mascara del PIC 1
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	21h,al
        pop     ebp
        retn

_mascaraPIC2:			; Escribe mascara del PIC 2
	push    ebp
    mov     ebp, esp
    mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out		0A1h,al
    pop     ebp
    retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn

_set_cr:
        push   ebp
		mov    ebp, esp
        mov    eax, 00300h 
        mov    cr3, eax		; setea CR3 con la direccion de el directorio de paginas
        
        mov    ebx, cr0      ;guardo el valor del CR0
        or     ebx, 80000000h ;seteo el ultimo bit en 1 que es el de PG
        mov    cr0,ebx        ;guardo CR0 modificado
        mov    esp,ebp
        pop    ebp
        ret


_lidt:				; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
	rol	ebx,16		    	
	lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn


_int_08_hand:				; Handler de INT 8 ( Timer tick)
        push    ds
        push    es                      ; Se salvan los registros
        pusha                           ; Carga de DS y ES con el valor del selector
        mov     ax, 10h			; a utilizar.
        mov     ds, ax
        mov     es, ax                  
        call    int_08                 
        mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	popa                            
        pop     es
        pop     ds
        iret

__stack_chk_fail:
				ret


_int_09_hand:
	cli
        push    ds
        push    es      	; Se salvan los registros
        pusha           	; Carga de DS y ES con el valor del selector
        call int_09		; Se llama a la funcion en C
        popa
        pop     es
        pop     ds
	sti
        iret

; recibe parametros a traves de los registros
; aex -> 0 para write, 1 para read
; ebx -> file descriptor
; ecx -> direccion de la cadena a escribir
; edx -> cantidad de caracteres a escribir

_int_80_hand:
    cli
    push ds
    push es
    pusha
    push edx             ; cantidad de caracteres a escribir
    push ecx             ; direccion de la cadena a escribir
    push ebx             ; file descriptor
    push eax		; system call
    call int_80
    pop eax             ; saco parametros
    pop eax
    pop eax
    pop eax
    popa
    pop es
    pop ds
    sti
    iret

_write:
	push ebp
	mov ebp, esp
	pusha
	mov eax, 0		; eax en 0 para write
	mov ebx, [ebp+8]	; file descriptor
	mov ecx, [ebp+12]	; buffer a escribiar
	mov edx, [ebp+16]	; cantidad
	int 80h
	popa
	mov esp,ebp
	pop ebp
	ret

_read:
	push ebp
	mov ebp, esp
	pusha
	mov eax, 1		; eax en 1 para read
	mov ebx, [ebp+8]	; file descriptor
	mov ecx, [ebp+12]	; buffer donde escribir
	mov edx, [ebp+16]	; cantidad
	int 80h
	popa
	mov esp, ebp
	pop ebp
	ret

_setCursor:
	        push ebp
	mov ebp, esp		; Stack frame
	mov bx, [ebp+8]  	; lo que se envia
	mov al,0x0e
	mov dx,0x03d4
	out dx, al
	mov al,bh
	mov dx,0x03d5
	out dx, al
	mov al,0x0f
	mov dx,0x03d4
	out dx, al
	mov al,bl
	mov dx,0x03d5
	out dx, al
	pop ebp
	ret

_restart:
	mov al,0xfe
	out 0x64,al
	ret

_in:	
    push ebp	
    mov ebp, esp		; Stack frame
    mov edx, [ebp+8]    ; Puerto
    mov eax, 0          ; Limpio eax
    in al, dx
	pop ebp
	ret

_out:
    push ebp
	mov ebp, esp		; Stack frame
	mov edx, [ebp+8]   	; Puerto
	mov eax, [ebp+12]  	; Lo que se va a mandar
	out dx, al
	pop ebp
	ret

_rdtsc:
        push ebp	
        mov ebp, esp		; Stack frame
		rdtsc
		mov esp,ebp
		pop ebp
		ret



_getHour:
	cli
	push ebp
	mov ebp,esp

	mov al, 04
	out 70h,al
	in al, 71h
	movzx eax,al
	
	mov esp,ebp
	pop ebp
	sti
	ret

_getMinutes:
	cli
	push ebp
	mov ebp,esp

	mov al,02
	out 70h,al
	in al, 71h
	
	movzx eax,al
	
	mov esp,ebp
	pop ebp
	sti
	ret

_getSeconds:
	cli
	push ebp
	mov ebp,esp

	mov al, 00
	out 70h,al
	in al, 71h
	movzx eax,al
	mov esp,ebp
	pop ebp
	sti
	ret
; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;


_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
		jne	vuelve
		pop	ax
		pop bp
		retn
