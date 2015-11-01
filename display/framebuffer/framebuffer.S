SEGMENT .text

global writechar
global clearscreen
global printc
global __lowlevel_write_char

__lowlevel_write_char:
	push eax
	push ebx
	push ecx

	mov eax, [esp+16]
	mov ebx, [esp+20]
	mov ecx, [esp+24]

	mov [eax], bl
	add eax, 1
	mov [eax], cl

	pop ecx
	pop ebx
	pop eax

	ret


;clearscreen:
;	push eax
;	push ebx
;	push ecx
;	push edx
;
;	mov edx, 1200 ; done condition
;	mov ecx, 0 ; start cout
;
;	cmp edx, ecx ; have we looped 1200 times?
;	je .done   ; if so go to done
;	mov eax, 2 ; put the index in eax
;	mul ecx ; eax = ecx*2
;	mov ebx, 0x000B8000
;	add ebx, eax
;	mov [ebx], byte 0x00
;	add ebx, 1
;	mov [ebx], byte 0x00
;.done
;	pop edx
;`	pop ecx
;	pop ebx
;	pop eax
;	ret


writechar:
	;push eax
	;push edx

	mov [0x000B8001], byte 0x07
	mov [0x000B8000], byte 0x41

	mov [0x000B8003], byte 0x0F
	mov [0x000B8002], byte 0x42

	mov [0x000B8005], byte 0x04
	mov [0x000B8004], byte 0x43


	;pop edx
	;pop eax

	ret
