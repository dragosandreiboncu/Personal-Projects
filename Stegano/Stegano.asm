%include "include/io.inc"

extern atoi
extern printf
extern exit

; Functions to read/free/print the image.
; The image is passed in argv[1].
extern read_image
extern free_image
; void print_image(int* image, int width, int height);
extern print_image

; Get image's width and height.
; Store them in img_[width, height] variables.
extern get_image_width
extern get_image_height

section .data
                task2words db "C'est un proverbe francais.", 0
	use_str db "Use with ./tema2 <task_num> [opt_arg1] [opt_arg2]", 10, 0

section .bss
    task:       resd 1
    img:        resd 1
    img_width:  resd 1
    img_height: resd 1

section .text


            
global main
main:
    ; Prologue
    ; Do not modify!
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    cmp eax, 1
    jne not_zero_param

    push use_str
    call printf
    add esp, 4

    push -1
    call exit

not_zero_param:
    ; We read the image. You can thank us later! :)
    ; You have it stored at img variable's address.
    mov eax, [ebp + 12]
    push DWORD[eax + 4]
    call read_image
    add esp, 4
    mov [img], eax

    ; We saved the image's dimensions in the variables below.
    call get_image_width
    mov [img_width], eax

    call get_image_height
    mov [img_height], eax

    ; Let's get the task number. It will be stored at task variable's address.
    mov eax, [ebp + 12]
    push DWORD[eax + 8]
    call atoi
    add esp, 4
    mov [task], eax

    ; There you go! Have fun! :D
    mov eax, [task]
    cmp eax, 1
    je solve_task1
    cmp eax, 2
    je solve_task2
    cmp eax, 3
    je solve_task3
    cmp eax, 4
    je solve_task4
    cmp eax, 5
    je solve_task5
    cmp eax, 6
    je solve_task6
    jmp done



solve_task1:
    ; EDX este folosit pentru a retine cheia
    mov edi, -1
    call bruteforce_singlebyte_xor
    print_task1:
            xor eax, eax
            mov ebx, -1
            print_word:
                inc ebx
                ; Daca am terminat randul => am terminat de printat cuvantul
                cmp ebx, [img_width]
                je print_key_and_line
                ; ECX este randul iar ebx coloana
                ; EDX este folosit pentru pozitia exact
                mov edx, [img_width]
                imul edx, ecx
                add edx, ebx
                
                mov eax, [img]
                mov eax, [eax + 4 * (edx)]
                xor eax, edi
                ; Daca pixelul este terminator de sir (/0) => am terminat de printat cuvantul
                cmp eax, 0
                je print_key_and_line
                PRINT_CHAR eax
                jmp print_word
            print_key_and_line:
            NEWLINE
            PRINT_DEC 4, edi
            NEWLINE
            PRINT_DEC 4, ecx
            NEWLINE
            jmp done
    
    
    
solve_task2:
    ; Aplicam functia de la primul task pentru a primi cheia si indexul randului
    call bruteforce_singlebyte_xor
    ; Le salvam pe stiva pentru a lucra cu EDX si ECX
    ; EDI - cheia
    push edi
    ; ECX - indexul randului
    push ecx
    ; Criptam matricea
    call task2_function
    pop ecx
    ; inc ECX pentru a scrie pe randul urmator
    inc ecx
    xor ebx, ebx
    overwrite_word:
        mov edx, [img_width]
        imul edx, ecx
        add edx, ebx

        mov edi, [img]
        mov eax, [task2words + ebx]
        ; Fiecare litera din propozitie o scriem peste valorile din matrice, de la linia ECX
        ; Am folosit AL in loc de EAX pentru a lua valoarea lui EAX doar pe un byte
        mov [edi + 4 * (edx)], al
        inc ebx
        ; Repeta cat timp EBX e mai mic decat lungimea propozitiei
        cmp ebx, 28
        jb overwrite_word
    ; Aplicam formula pentru noua cheie pe care o vom salva in EAX
    xor edx, edx
    pop eax
    imul eax, 2
    add eax, 3
    mov ecx, 5
    cdq
    idiv ecx
    sub eax, 4
    mov edi, eax
    ; Mutam noua cheie in EDI si apelam criptarea matricei din nou
    call task2_function
    ; Printam matricea cu ajutorul functiei print_image
    mov eax, [img_height]
    mov ebx, [img_width]
    mov ecx, [img]
    push eax
    push ebx
    push ecx
    call print_image
    jmp done


solve_task3:
    jmp done
solve_task4:
    jmp done
solve_task5:
    jmp done


    
    
solve_task6:
    call blur
    mov eax, [img_height]
    mov ebx, [img_width]
    mov ecx, [img]
    push eax
    push ebx
    push ecx
    call print_image
    jmp done

    ; Free the memory allocated for the image.
done:
    push DWORD[img]
    call free_image
    add esp, 4

    ; Epilogue
    ; Do not modify!
    xor eax, eax
    leave
return:
    ret
    
    



bruteforce_singlebyte_xor:
    inc edi
    mov ecx, -1
    rows_1:
        ; Trecem pe linie noua, resetam indexul EBX pentru coloane la 0
        ; si crestem indexul ECX pentru linii
        inc ecx
        cmp ecx, [img_height]
        ; Daca am parcurs toata matricea, apelam functia din nou, pentru o noua valoare a cheii EDI
        je bruteforce_singlebyte_xor
        xor ebx, ebx
    columns_1:
        mov edx, [img_width]
        imul edx, ecx
        add edx, ebx
        inc ebx
        mov eax, [img]
        mov eax, [eax + 4 * (edx)]
        xor eax, edi
        cmp eax, 't'
        ; Daca gasim t, verificam pixelii anteriori
        je revient_check
    continue:    
        cmp ebx, [img_width]
        jb columns_1
        jmp rows_1
    revient_check:
            ; In caz ca unul dintre ei e diferite, ne intoarcem in matrice
            mov eax, [img]
            mov eax, [eax + 4 * (edx) - 4]
            xor eax, edi
            cmp eax, 'n'
            je check1
            jmp continue
        check1:
            mov eax, [img]
            mov eax, [eax + 4 * (edx) - 8]
            xor eax, edi
            cmp eax, 'e'
            je check2
            jmp continue
        check2:
            mov eax, [img]
            mov eax, [eax + 4 * (edx) - 12]
            xor eax, edi
            cmp eax, 'i'
            je check3
            jmp continue
        check3:
            mov eax, [img]
            mov eax, [eax + 4 * (edx) - 16]
            xor eax, edi
            cmp eax, 'v'
            je check4
            jmp continue
        check4:
            mov eax, [img]
            mov eax, [eax + 4 * (edx) - 20]
            xor eax, edi
            cmp eax, 'e'
            je check5
            jmp continue
        check5:
            mov eax, [img]
            mov eax, [eax + 4 * (edx) - 24]
            xor eax, edi
            cmp eax, 'r'
            ; Am gasit cuvantul => avem cheia in EDI si linia in ECX
            je return
            jmp continue
            
            

task2_function:
    mov ecx, -1
    rows_2:
        inc ecx
        cmp ecx, [img_height]
        je return
        xor ebx, ebx
    columns_2:
        mov edx, [img_width]
        imul edx, ecx
        add edx, ebx
        inc ebx
        mov eax, [img]
        mov eax, [eax + 4 * (edx)]
        ; Punem valoarea pixelului din matrice in EAX si o criptam cu cheia EDI
        xor eax, edi
        mov esi, [img]
        ; Suprapunem noua valoarea peste cea veche
        mov [esi + 4 * (edx)], eax
        cmp ebx, [img_width]
        jb columns_2
        jmp rows_2
                
                
                
blur:
    xor ecx, ecx
    ; Luam toti termenii matricii interioare + vecinii fiecaruia
    rows_6_1:
        inc ecx
        mov edi, [img_height]
        sub edi, 1
        ; Pentru matricea interioara, plecam de la linia 1( nu 0 )
        ; Iar daca am ajuns la penultima( img_height -1 ), ne oprim
        cmp ecx, edi
        je overwrite_values
        ; De asemenea, plecam de la coloana 1( nu 0 )
        mov ebx, 1
     columns_6_1:
        mov edx, [img_width]
        imul edx, ecx
        add edx, ebx
        inc ebx
        ; Valoarea pixelului
        mov eax, [img]
        mov eax, [eax + 4 * (edx)]
        mov esi, eax
        ; Valoarea pixelului din stanga
        mov eax, [img]
        mov eax, [eax + 4 * (edx) - 4]
        add esi, eax
        ; Valoarea pixelului din dreapta
        mov eax, [img]
        mov eax, [eax + 4 * (edx) + 4]
        add esi, eax
        ; Valoarea pixelului de sus
        mov eax, [img]
        sub edx, [img_width]
        mov eax, [ eax + 4 * (edx)]
        add esi, eax
        ; Valoarea pixelului de jos
        mov eax, [img]
        add edx, [img_width]
        add edx, [img_width]
        mov eax, [eax + 4 * (edx)]
        add esi, eax
        ; Calculam media aritmetica si o punem pe stiva
        mov eax, esi
        mov esi, 5
        xor edx, edx
        cdq
        idiv esi
        ; O punem pe stiva
        push eax
        ; De asemenea, pentru matricea interioara, daca ajungem la penultima coloana( img_width - 1 ), ne oprim
        mov edi, [img_width]
        sub edi, 1
        cmp ebx, edi
        jb columns_6_1
        jmp rows_6_1
        overwrite_values:
           ; Vom scrie valorile in matrice, de jos in sus
            mov ecx, [img_height]
            dec ecx
            rows_6_2:
                dec ecx
                cmp ecx, 0
                je return
                mov ebx, [img_width]
                sub ebx, 2
            columns_6_2:
                mov edx, [img_width]
                imul edx, ecx
                add edx, ebx
                dec ebx
                mov eax, [img]
                xor edi, edi
                pop edi
                mov  [eax + 4 * (edx)], edi
                cmp ebx, 0
                ja columns_6_2
                jmp rows_6_2
                
