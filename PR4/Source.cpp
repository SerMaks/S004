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
		//���������� ������ ������
		lea ebx, s1
		push ebx
		lea ecx, f
		push ecx
		call scanf
		add esp, 8
		//���������� ������ � ����� �����������
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
		//���������� � �������� ����� ������
		lea ebx, s1
		dec ebx
		mov ecx, -1
		//������� ����� ������
		b1:
		inc ecx
		inc ebx
		mov al, [ebx]
		cmp al, 0
		jnz b1
		//���������� � ������ �����������
		lea edx, s2
		dec edx
		//�������� ���������� ������� �����������
		mov eax, start
		cmp eax, ecx
		jge end
		cmp eax, 0
		jg skip
		mov eax, 0 //���� ��������� ������ ������ 0, �������� 0

		skip:
		//���������� � �����
		lea ebx, s1
		sub ebx, 2
		mov ecx, len
		inc eax
		//������ �������� �����������: ����������� � ���������� �������
		copy1 :
		inc ebx
		dec eax
		cmp eax, 0
		jnz copy1
		//������ �������� �����������: �������� ������
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