TITLE Program 6 (Option A)

              
; Date: 03/13/16
; Description: Implements procedures to read and write unsigned integers.
;              Implements macros to get a string from keyboard and to display a String.
;              Gets 10 integers from the user and stores them in an array, displays the integers, 
;              their sum, and their average.

INCLUDE Irvine32.inc

;Display String (Macro)
;	prints a string converted from a number
;	uses stack parameters from WriteVal procedure 


displayString MACRO
	push	EDX
	mov		EDX, [EBP+12]			;the string of the converted number
	call	WriteString
	mov		EDX, [EBP+24]			;padding between numbers
	call	WriteString
	pop		EDX
ENDM

;Get String (Macro)
;	reads numbers from a string and puts them into an array

getString MACRO inputInt						
	push	EBX
	push	ECX
	push	EDX
	push	EAX
	mov		EDX, [EBP+12]
	mov		ECX, 11
	call	ReadString							;buffer has string of digits
	mov		EBX, inputInt						; move offset of inputCount to EBX
	mov		[EBX], eax							;count of numbers read from the string
	pop		EAX
	pop		EDX
	pop		ECX
	pop		EBX
ENDM

;Write String (Macro)
;	writes sting passed to it

WSMacro		MACRO	buffer
	push	EDX
	mov		EDX, OFFSET buffer
	call	WriteString
	pop		EDX
ENDM

;Read String(Macro)
;	reads string passed to it

RSMacro		MACRO	stringVar
	push	ECX
	push	EDX
	mov		EDX, OFFSET stringVar
	mov		ECX, (SIZEOF stringVar) - 1
	call	ReadString
	pop		EDX
	pop		ECX
ENDM

.data

inputBuffer		BYTE	11 DUP(?)				
inputCount		DWORD	0						;32 bit unsigned int max length = 10
convertedArray	DWORD	10 DUP (?)				;used by readVal, stores numbers after they are converted
intAccum		DWORD	0						;used by readVal, used in calculating int value of string
conLength		DWORD	10 DUP (0)				;lengths of the converted numbers
stringArray		BYTE	10 DUP (?) 				;array for the numbers converted back to strings
convertedNums	DWORD	0
fourInt			DWORD	4						;unused
promptString	BYTE	"Please enter an unsigned number: ",0
rangeString		BYTE	"ERROR: input not in range.",0
enteredString	BYTE	"You entered the following numbers: ",0
numPrinted		DWORD	0						;quantity of numbers printed
reversedString	BYTE	10 DUP (0)				;unused
paddingString	BYTE	"  ",0					;padding between numbers
aveString		BYTE	"Average is ",0
sumString		BYTE	"Sum is ", 0
introString		BYTE	"Low-level I/O procedures by John Steiner",0


.code
main PROC
WSMacro introString
call	Crlf
call	Crlf

push	OFFSET promptString				;+36
push	OFFSET fourInt					;+32
push	OFFSET inputCount				;+28
push	OFFSET convertedArray			;+24
push	OFFSET convertedNums			;+20
push	OFFSET conLength				;+16
push	OFFSET inputBuffer				;+12
push	OFFSET intAccum					;+8  needs to be written to
call	ReadVal


push	OFFSET paddingString			;+24
push	OFFSET enteredString			;+20
push	OFFSET numPrinted				;+16
push	OFFSET stringArray				;+12
push	OFFSET convertedArray			;+8
call	WriteVal

push	OFFSET aveString
push	OFFSET convertedArray
call	displayAve

push	OFFSET sumString
push	OFFSET convertedArray
call	displaySum

	exit	; exit to operating system
main ENDP

; ReadVal
;	Uses getString macto to get user's string of digits.
;	Converts digit string to numeric value

ReadVal PROC
	
	push		EBP
	mov			EBP, ESP
	mov			EDI, OFFSET convertedArray				; needed for stosb
	cld

	newNumber:
	mov			ESI, [EBP+12]							; needed for lodsb
	mov			EBX, [EBP+8]							; move accumulator into EBX
	mov			EAX, 0
	mov			[EBX], EAX								;reset intAccum to 0 
	push	EDX
	mov		EDX, [EBP+36]								;promp string
	call	WriteString
	pop		EDX

	getString	[EBP+28]								; "calls" getString macro with inputBuffer
	mov			ECX, [EBP+28]							;inputCount into ECX for counter
	mov			ECX,[ECX] 
	mov			EDX, 0

	getNums:										
	lodsb												; loads the first byte from the ESI string; increments automatically
	cmp			AL, 0									; check if it's 0 not the ascii value of 0
	je			addToArray

	cmp			EAX, 48
	jge			inLower									;if in range above lower limit jump over error message

	WSMacro rangeString
	call	Crlf
	jmp			getNums

	inLower:
	cmp			EAX, 57
	jle			accumulate								; if in range below upper limit, jump over error message

	WSMacro rangeString
	call	Crlf
	jmp			getNums


	;numbers read are added to running total

	accumulate:
	mov			ECX, EAX							; move the valid input into ECX 
	mov			EAX, 10								; move 10 into EAX for multiplication
	mov			EBX, [EBP+8]							; move our accumulator into EBX
	mov			EBX, [EBX]
	mul			EBX									; data is valid, multiply accumulator by 10 ; product is in EAX
	sub			ECX, 48								; convert valid input's ascii into a number
	add			ECX, EAX							; add temporary accumulator and converted number
	mov			EDX, [EBP+8]
	mov			[EDX], ECX
	jmp			getNums

	addToArray:										;this shouldn't happen until lodsb hits a zero
	
	mov			EAX, [EBP+8]						; accumulated number is about to go in array
	mov			EAX, [EAX]
	stosd											; move converted number to convertedArray
	;add			EDI, 3
	push		EDX
	push		EBX
	mov			EDX, [EBP+20]
 	mov			EBX, [EDX]
	add			EBX, 1
	mov			[EDX], EBX
	cmp			EBX, 10
	pop			EBX
	pop			EDX
	jl			newNumber
	pop			EBP
	ret 28 

ReadVal ENDP

; WriteVal
;	Converts a numberic value to a string of digits
;	Uses displayString macro to produce output

WriteVal PROC

	push		EBP
	mov			EBP, ESP
	mov			ESI, [EBP+8]				;array of ints is here 
	mov			EDI, [EBP+12]				;array to store string in is here
	cld

	mov		EDX, [EBP+20]					; "You entered..."
	call	WriteString
	call	Crlf

	; start on a new number

	nextNumber:
	mov		EDI, [EBP+12]					; write to the same place for every new string
	mov		EAX, [ESI]						; first int to convert should be here on first loop
	mov		EBX, 10							; EBX used for two things, shouldn't be changed from 10

	;move to the next digit within same number

	nextPlace:
	cmp		EAX, EBX						; if int is less than 10, no more division
	jl		finalDigit

	mov		EDX, 0							;because division
	div		EBX								;divides EAX by EBX; quotient goes to EAX, remainder to EDX
	jmp		processInt


	processInt:
	add		EDX, 48					; convert remainder to ascii
	
	push	EAX
	mov		AL, DL
	stosb
	pop		EAX
	loop	nextPlace
	

	finalDigit:
	add		EAX, 48					; convert remainder to ascii
	stosb
	mov		AL,0
	stosb

	displayString

	add		ESI, 4
	mov		EDX, [EBP+16]			;address of numPrinted in EDX
	mov		EBX, [EDX]				;EDX now should have value of numPrinted
	add		EBX, 1
	mov		[EDX], EBX			; move incremented value of numPrinted into memory location for numPrinted
	cmp		EBX, 9
	jle		nextNumber
	call	Crlf
	pop		EBP
	ret 20
			
WriteVal ENDP


;Display Average
;	Calculates and displays the average of the numbers entered.

displayAve PROC

	push	EBP
	mov		EBP, ESP

	mov		ESI,[EBP+8]					;should be our array
	mov		EDX, [EBP+12]
	call	WriteString

	mov		ECX, 10
	mov		EBX, 0						;EBX will be accumulator
	topSum:
	add		EBX, [ESI]
	add		ESI,4

	loop	topSum						; ECX set to 10, the number of entries required
	
	mov		EDX, 0
	mov		EAX, EBX
	mov		EBX, 10
	div		EBX							;divide total by 10, the number of required entries

	call	WriteDec
	call	Crlf
	
	pop		EBP
	ret		8

displayAve ENDP

; Display Sum
;	Calculates and displays the sum of the numbers entered.

displaySum PROC

	push	EBP
	mov		EBP, ESP

	mov		ESI,[EBP+8]					;array of numbers to process
	mov		EDX, [EBP+12]
	call	WriteString

	mov		ECX, 10
	mov		EBX, 0						;EBX will be accumulator
	topSum:
	add		EBX, [ESI]
	add		ESI,4

	loop	topSum						
	
	mov		EAX, EBX

	call	WriteDec
	call	Crlf
	
	pop		EBP
	ret		8

displaySum ENDP


END main
