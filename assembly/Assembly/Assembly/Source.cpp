#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
	float a[5], b;
	float n, d, CONSTANT_1, CONSTANT_2, CONSTANT_3, CONSTANT_4, CONSTANT_5;

	__asm {

		mov eax, 1085276160
		mov dword ptr[a + 0], eax  // a[0] = 5.5

		mov eax, 1084227584
		mov dword ptr[a + 4], eax  // a[1] = 5

		mov eax, 3240099840
		mov dword ptr[a + 8], eax  // a[2] = -10

		mov d, 1090519040 //d = 8
		mov CONSTANT_1, 1065353216 //CONSTANT_1 = 0
		mov CONSTANT_2, 1065353216 //CONSTANT_2 = 1
		mov CONSTANT_3, 1073741824 //CONSTANT_3 = 2

		movups xmm0, b
		mov esi, 0
		movups xmm1, [4 * esi] + a
		mov esi, 1
		movups xmm2, [4 * esi] + a
		mov esi, 2
		movups xmm3, [4 * esi] + a
		addss xmm1, xmm2
		addss xmm1, xmm3
		movups b, xmm1
		
	}
	cout << "b : ";
	cout << b;
}

