GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL  _int_09_hand
GLOBAL	_int_80_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL	_read
GLOBAL	_write
GLOBAL	_in
GLOBAL	_out

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
        out	0A1h,al
        pop     ebp
        retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn


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

_int_09_hand:				; Handler de INT 9 ( Teclado )
        push    ds
        push    es                      ; Se salvan los registros
        pusha                           ; Carga de DS y ES con el valor del selector

	in al, 60h	;Leo el puerto del teclado
	push ax		;Le envio el SCAN CODE como parametro a la funcion int_09
	call int_09	;Llamo a la interrupcion que maneja el SCAN CODE en C
	pop ax		;Quito el parametro del stack

       mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al

	popa
        pop     es
        pop     ds
        iret

;_int_09_hand:
;	cli
 ;       push    ds
 ;       push    es      	; Se salvan los registros
 ;       pusha           	; Carga de DS y ES con el valor del selector
 ;       call int_09		; Se llama a la funcion en C
;		mov	al,20h			; Envio de EOI generico al PIC
;		out	20h,al       
;        popa
;        pop     es
;        pop     ds
;	sti
 ;       iret


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
    push edx            ; cantidad de caracteres a escribir
    push ecx            ; direccion de la cadena a escribir
    push ebx           	; file descriptor
    push eax			; system call
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
	int 80h
	ret
;_write:
;	push ebp
;	mov ebp, esp
;	pusha
;	mov eax, 0		; eax en 0 para write
;	mov ebx, [ebp+8]	; file descriptor
;	mov ecx, [ebp+12]	; buffer a escribir
;	mov edx, [ebp+16]	; cantidad
;	int 80h
;	popa
;	mov esp, ebp
;	pop ebp
;	ret

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

_in:	
        push ebp	
        mov ebp, esp		; Stack frame
        mov edx, [ebp+8]        ; Puerto
        mov eax, 0              ; Limpio eax
        in al, 0x60
        push ax
	pop ebp
	ret

_out:
        push ebp
	mov ebp, esp		; Stack frame
	mov edx, [ebp+8]   	; Puerto
	mov eax, [ebp+12]  	; lo que se envia
	out 0x20, al
	pop ebp
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
	pop     bp
        retn


	
