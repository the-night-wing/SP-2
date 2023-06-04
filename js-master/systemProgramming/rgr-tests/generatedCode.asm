
mov eax, 1092616192
mov dword ptr[a+0], eax  // a[0] = 10
  
mov eax, 1097859072
mov dword ptr[a+4], eax  // a[1] = 15
  
mov eax, 3225419776
mov dword ptr[a+8], eax  // a[2] = -3
  
mov eax, 1085276160
mov dword ptr[a+0], eax  // a[0] = 5.5
  
mov n, 1065353216 //n = 0
mov d, 1090519040 //d = 8
mov CONSTANT_1, 3221225472 //CONSTANT_1 = -2
mov CONSTANT_2, 1065353216 //CONSTANT_2 = 0


movups xmm2, b
movups xmm1, b
movups xmm3, CONSTANT_1
mov esi, 0
movups xmm4, [4 * esi] + a
mulss xmm3, xmm4
movups b, xmm0
movups b, xmm3