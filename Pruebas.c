/***************************************************************************************
  Pruebas.cpp 1.0
  (C) 30/01/2012 23:57:13 by MARCOS BRITO, marbri91@gmail.com
Description: Para ir probando lo que voy haciendo
 **************************************************************************************/

#include "Z80.h"
#include <stdio.h>

int main()
{
	RZ80 Reg;
	word n=0x1234;
	RAM[0] = SBCAB;
	RAM[1] = 0x12;
	RAM[2] = 0x34;
	RAM[3] = 0x56;
	RAM[n] = 0x80;
	ResetZ80(&Reg);
	Reg.AF_ =0x00F0;
	Reg.A = 0x0E;
	Reg.B = 0x01;
	Reg.C = 0xCC;
	Reg.D = 0xDD;
	Reg.E = 0xEE;
	Reg.F = 0x01;
	Reg.H = 0x12;
	Reg.L = 0x34;
	printf("A:%X B:%X C:%X D:%X E:%X H:%X L:%X\n",Reg.A,Reg.B,Reg.C,Reg.D,Reg.E,Reg.H,Reg.L);
	printf("BC:0x%X  DE:0x%X  HL:0x%X PC:0x%X\n",Reg.BC,Reg.DE,Reg.HL,Reg.PC);
	printf("0x%04x: 0x%02x%02x\n\n",n,RAM[n],RAM[n+1]);
	ExecZ80(&Reg);
	printf("A:%X B:%X C:%X D:%X E:%X H:%X L:%X\n",Reg.A,Reg.B,Reg.C,Reg.D,Reg.E,Reg.H,Reg.L);
	printf("BC:0x%X  DE:0x%X  HL:0x%X PC:0x%X\n",Reg.BC,Reg.DE,Reg.HL,Reg.PC);
	printf("0x%04x: 0x%02x%02x\n",n,RAM[n],RAM[n+1]);
	return 0;
}
