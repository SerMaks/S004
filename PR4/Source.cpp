#include <iostream>

int main()
{
	std::cout << "Hello World!\n";
	char s1[256];
	char s2[256];
	int start;
	int len;
	char f[] = "%s";
	char fd[] = "%d";
	_asm {
		//считывание первой строки
		lea ebx, s1
		push ebx
		lea ecx, f
		push ecx
		call scanf
		add esp, 8
		//считывание начала и длины копирования
		lea ebx, start
		push ebx
		lea edx, fd
		push edx
		call scanf
		add esp, 8
		lea ebx, len
		push ebx
		lea edx, fd
		push edx
		call scanf
		add esp, 8
		//подготовка к подсчету длины строки
		lea ebx, s1
		dec ebx
		mov ecx, -1
		//подсчет длины строки
		b1:
		inc ecx
		inc ebx
		mov al, [ebx]
		cmp al, 0
		jnz b1
		//подготовка к началу копирования
		lea edx, s2
		dec edx
		//проверка стартового индекса копирования
		mov eax, start
		cmp eax, ecx
		jge end
		cmp eax, 0
		jg skip
		mov eax, 0 //если стартовый индекс меньше 0, помещаем 0

		skip:
		//подготовка к циклу
		lea ebx, s1
		sub ebx, 2
		mov ecx, len
		inc eax
		//первая половина копирования: перемещение к стартовому индексу
		copy1 :
		inc ebx
		dec eax
		cmp eax, 0
		jnz copy1
		//вторая половина копирования: копируем нужное
		copy2 :
		inc ebx
		inc edx
		dec ecx
		mov al, [ebx]
		mov[edx], al
		cmp al, 0
		jz end
		cmp ecx, 0
		jnz copy2
		jmp end

		end :
		inc edx
		mov[edx], 0
		lea ebx, s2
		push ebx
		lea ecx, f
		push ecx
		call printf
		add esp, 8
	}
}