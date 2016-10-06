TITLE Programming Assignment #5 

; Date: 02-28-2016
; Description: Generates random numbers in the range [100 .. 999],
;              displays the original list, sorts the list, and calculates
;              the median value. Finally, it displays the list sorted 
;              in descending order.

INCLUDE Irvine32.inc

MIN = 10
MAX = 200
LO = 100
HI = 999

.data

request			DWORD	?				;quantity of numbers requested by user
array			DWORD	MAX	DUP (?)		;array of size MAX, a constant
numPrint		DWORD	?				;used to track quantity of numbers printed
newLineInt		DWORD	10				;start a new line after printing this many numbers
dataSize		DWORD	4				;used in incrementing ESI, set for DWORD data
swapIntA		DWORD	?				;temporary data holder for swapping
swapIntB		DWORD	?				;temporary data holder for swapping


nameString		BYTE	"Sorting Random Integers by John Steiner",0
introString		BYTE	"This program generates random numbers in the range [100 .. 999], ", 0dh, 0ah
				BYTE	"displays the original list, sorts the list, and calculates the ", 0dh,0ah
				BYTE	"median value. Finally, it displays the list sorted in descending order.",0
promptString	BYTE	"How Many numbers should be generated? (10 - 200) ",0
errorString		BYTE	"Invalid input",0
unsortString	BYTE	"The unsorted random numbers:",0
medianString	BYTE	"The median is ",0
sortedString	BYTE	"The sorted list:",0
paddingString	BYTE	"   ",0
myErrorString	BYTE	"***** The sorting algorithm breaks when request > 100  *****",0


.code
main PROC

call	Randomize

call	introduction

push	OFFSET request
call	getData

push	OFFSET array
push	request
call	fillArray

push	newLineInt						;+28
push	OFFSET paddingString			;+24
push	numPrint						;+20
push	OFFSET array					;+16?
push	request							;+12?
push	OFFSET unsortString				;+8
call	displayList


push	swapIntB						;20
push	swapIntA						;16
push	request
push	OFFSET array
call	sortList


push	OFFSET array
push	request
call	displayMedian

call	Crlf
mov		EDX, OFFSET myErrorString
call	WriteString
call    Crlf
call	Crlf

push	newLineInt						;+28
push	OFFSET paddingString			;+24
push	numPrint						;+20
push	OFFSET array					;+16?
push	request							;+12?
push	OFFSET sortedString				;+8
call	displayList

mov		EDX, OFFSET paddingString
call	WriteString

	exit	; exit to operating system

main ENDP

;Introduction
;	Displays program name and instructions.
;	Parameters are global string variables

introduction PROC
	mov		EDX, OFFSET nameString
	call	WriteString
	call	Crlf
	call	Crlf
	mov		EDX, OFFSET introString
	call	WriteString
	call	Crlf
	call	Crlf
	
	ret

introduction ENDP

;Get Data
;	Prompts user for quantity of numbers to generate
;	Validates data and stores input in request variable.
;	Parameter: Offset of request on stack

getData PROC

	push	EBP
	mov		EBP, ESP
	mov		EBX, [EBP+8]				;address of request is at EBP+8
	
	PromptU:

	mov		EDX, OFFSET promptString
	call	WriteString
	call	readInt						;stores in EAX
	cmp		EAX, MIN
	jl		ErrorM						;if input less than min, jump to error message				
	cmp		EAX, MAX
	jg		ErrorM						;if input greater than max, jump to error message
	JMP		ValidD						;if it hasn't jumped, it's valid data
	
	ErrorM:
	
	mov		EDX, OFFSET errorString
	call	WriteString
	call	Crlf
	jmp		PromptU						;after displaying message, prompt again
	
	ValidD:
	mov		[EBX], EAX					;data is valid so move it to address in EBX (which is request)

	pop		EBP
	ret		4

getData ENDP

;Fill Array
;	Fills an array with random numbers within range (HI - LO)
;	Quantity generated = request
;	Parameters: Offset of array and value of request, on stack 

fillArray PROC

	push	EBP
	mov		EBP,ESP
	mov		ESI,[EBP+12]				;array's address is EBP+12
	mov		ECX,[EBP+8]					;requests's address is EBP+8, used as loop counter

	fillRand:
	mov		EAX, HI
	sub		EAX, LO
	call	RandomRange
	add		EAX, 100
	mov		[ESI], EAX
	
	add		ESI, 4						;update ESI to point to next element in array
	loop	fillRand

	pop		EBP
	ret		8
	
fillArray ENDP

;Sort List
;	Uses gnome sort to sort arrray into descending order
;	Parameters: two integers to hold values while swapping
;			    request passed by value, and offset of array
;				All variable passed onto stack

sortList PROC

	push	EBP
	mov		EBP,ESP

	mov		ESI, [EBP + 8]                 
	add		ESI, 4							; first element to compare 
	mov		ECX, [EBP + 12]                 ; setting ECX to the number of items
	mov		EAX, 1;                         ; index starts at 1 and compares with index-1


MiniLoop:

	cmp		EAX, 0
	jle		EndOfLoop                     
                                                                
	mov		EBX, [ESI]						; EBX = current element        
	mov		EDX, [ESI - 4]					; EDX = previous element
	cmp		EDX, EBX						; compare current and previous, if they are correctly ordered jump to end
	jge		EndOfLoop			


	mov		[EBP + 16], EBX                 ; current element goes into swapIntA
	mov		[EBP + 20], EDX					; previous element goes into swapIntB

	mov		EDX, [EBP + 16]					;swapIntA goes into previous element
	mov		EBX, [EBP + 20]					;swapIntB goes into current element

	mov		[ESI], EBX						;current element goes into its place in array
	mov		[ESI-4], EDX					;previous element goes into its place in array

											;swapIntB 20
											;swapIntA 16

	
	cmp		EAX, 0
	jle		NoDecrement
	sub		ESI, 4							; May need to move value back again so dec ESI and EAX
	dec		EAX								

	NoDecrement:

	jmp MiniLoop


	EndOfLoop:								; Go to next element, in ESI and EAX
	inc		EAX								
	add		ESI, 4

	cmp		EAX, [EBP + 12]
	jl		MiniLoop

	Loop MiniLoop

	pop		EBP
	ret		16

sortList ENDP


; Display Median
;	Calculates and displays the median of the sorted array
;	Offest of array and value of request passed onto stack

displayMedian PROC

	push	EBP
	mov		EBP, ESP

	mov		ESI,[EBP+12]
	mov		EDX, OFFSET medianString
	call	WriteString


	;request is [EBP+8]
	;array is [EBP+12]

	mov		EDX, 0
	mov		EAX, [EBP+8]
	mov		ECX, 2
	div		ECX

	cmp		EDX, 0
	jne oddLength

											;if it didn't jump request is even
	mov		EDX, 0
	mov		EAX, [EBP+8]
	mov		ECX, 2
	div		ECX								;request /2, result stored in EAX
	mov		ECX, 4
	mul		ECX								;multiply index * 4 gives offset

	mov		EAX, [ESI+EAX]					;first value from array used to calculate mean
	add		EAX, [ESI+EAX+4]				;add value after it to first value

	mov		EDX,0
	mov		ECX, 2
	div		ECX								;divide the sum of the two elements by 2. Median is now in EAX

	jmp		PrintMedian

	oddLength:

	mov		EDX, 0
	mov		EAX, [EBP+8]
	mov		ECX, 2
	div		ECX								; div EAX by ECX, Result in EAX
	add		EAX, 1							; median of odd numbers is (integer division by 2) + 1
	mov		ECX, 4
	mul		ECX								;index of median * 4 is stored in EAX
	
	mov		EAX, [ESI + EAX]
	jmp		PrintMedian


	PrintMedian: 
	call	WriteDec
	call	Crlf
	
	pop		EBP
	ret		8

displayMedian ENDP


;Display List
;	Displays the values of an array and the description string
;	Parameters: values of newLineInt, numPrint, and request
;				Offset of a blank spacing string, the array, a description string


displayList PROC

	push	EBP
	mov		EBP, ESP
	mov		ESI, [EBP+16]				;address of array
	mov		ECX, [EBP+12]				;value of request, used as loop counter
	mov		EDX, [EBP+8]				;address of String
	call	WriteString
	call	Crlf

	DisplayL:

	mov		EAX, [ESI]					;current element
	call	WriteDec
	mov		EDX, [EBP+24]
	call	WriteString
	add		ESI,4

	mov		EAX, [EBP+20]
	add		EAX,1
	mov		[EBP+20], EAX				;number printed is in EAX

	mov		EDX, 0
	mov		EBX, [EBP+28]
	div		EBX							;divide number printed by 10
	cmp		EDX, 0
	jne		NONEWLINE					;jump over printing newline if number printed % 10 is not equal to zero
	call	Crlf
	
	NONEWLINE:

	loop	DisplayL

	Call	Crlf
	pop		EBP
	ret 24

displayList ENDP


END main
