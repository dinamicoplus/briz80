/***************************************************************************************
  Z80.cpp 1.0
  (C) 30/01/2012 23:39:14 by MARCOS BRITO, marbri91@gmail.com
Description: Emulador del Z80
 **************************************************************************************/

#include "Z80.h"
#include <stdio.h>
//Reset
#define LDRR(Reg1,Reg2) R->Reg2=R->Reg1

int ResetZ80(RZ80 *R)
{
	R->PC=0x00;
	R->I=0x00;
	R->R=0x00;
	R->AF=0x0000;
	R->BC=0x0000;
	R->DE=0x0000;
	R->HL=0x0000;
	return 0;
}

//Read
const byte ReadZ80(word A)
{
	return RAM[A];
}
void WriteZ80(word A,byte D)
{
	RAM[A]=D;
}

int ExecZ80(RZ80 *R)
{
	word I=ReadZ80(R->PC);
	word AW;
	byte AB;
	switch (I)
	{
		case NOP: break;
		case LDBCNN: R->B=ReadZ80(++R->PC); R->C=ReadZ80(++R->PC); break;
		case LDBCA: WriteZ80(ReadZ80(R->BC), R->A); break;
		case INCBC: R->BC++; break;
		case INCB: R->B++; break;
		case DECB: R->B--; break;
		case LDBN: R->B=ReadZ80(++R->PC); break;
		case RLCA: R->A=(R->A<<1)|((R->A&0x80)>>7);  break;
		case EXAFAF_: AW=R->AF; R->AF=R->AF_; R->AF_=AW; break;
		case ADDHLBC: R->HL+=R->BC; break;
		case LDABC: R->A=ReadZ80(R->BC); break;
		case DECBC: R->BC--; break;
		case INCC: R->C++; break;
		case DECC: R->C--; break;
		case LDCN: R->C=ReadZ80(++R->PC); break;
		case RRCA: R->A=(R->A>>1)|((R->A&0x01)<<7); break;
		case DJNZ: R->B!=0? R->PC+=ReadZ80(++R->PC):R->B--; break;
		case LDDENN: R->D=ReadZ80(++R->PC); R->E=ReadZ80(++R->PC); break;
		case LDDEA: WriteZ80(R->DE, R->A); break;
		case INCDE: R->DE++; break;
		case INCD: R->D++; break;
		case DECD: R->D--; break;
		case LDDN: R->D=ReadZ80(++R->PC); break;
		case RLA: AB=(R->A&0x80)>>7; R->A=(R->A<<1)|(R->F&0x01); R->F|=AB; break;
		case JRE: R->PC+=ReadZ80(++R->PC); break;
		case ADDHLDE: R->HL+=R->DE; break;
		case LDADE: R->A=ReadZ80(R->DE); break;
		case DECDE: R->DE--; break;
		case INCE: R->E++; break;
		case DECE: R->E--; break;
		case LDEN: R->E=ReadZ80(++R->PC); break;
		case RRA: AB=(R->A&0x1); R->A=(R->A>>1)|(R->F&0x80)<<7; R->F|AB; break;
		case JRNZE: if ((R->F&0x40)>>5!=0) R->PC+=ReadZ80(++R->PC); break;
		case LDHLNN: R->H=ReadZ80(++R->PC); R->L=ReadZ80(++R->PC); break;
		case LDNN_HL: AW=ReadZ80(++R->PC)<<8; AW+=ReadZ80(++R->PC); //Toquetear si hay
					  WriteZ80(AW, R->L); WriteZ80(++AW, R->H); break;//problemas con endian
		case INCHL: R->HL++; break;
		case INCH: R->H++; break;
		case DECH: R->H--; break;
		case LDHN: R->H=ReadZ80(++R->PC); break;
		case DAA: AW=R->A; break; //Por hacer
		case JRZE: if ((R->F&0x40)>>5==0) R->PC+=ReadZ80(++R->PC); break;
		case ADDHLHL: R->HL<<=1; break;
		case LDHLNN_: AW=ReadZ80(++R->PC)<<8; AW+=ReadZ80(++R->PC);
					  R->L=ReadZ80(AW); R->H=ReadZ80(++AW); break;
		case DECHL: R->HL--; break;
		case INCL: R->L++; break;
		case DECL: R->L--; break;
		case LDLN: R->L=ReadZ80(++R->PC); break;
		case CPL: R->A^=0xF; break;
		case JRNCE: if ((R->F&0x01)!=0) R->PC+=ReadZ80(++R->PC); break;
		case LDSPNN: R->SP=ReadZ80(++R->PC); break;
		case LDNN_A: AW=ReadZ80(++R->PC)<<8; AW+=ReadZ80(++R->PC);
					 WriteZ80(AW, R->A); break;
		case INCSP: R->SP++; break;
		case INCHL_: WriteZ80(R->HL, ReadZ80(R->HL)+1); break;
		case DECHL_: WriteZ80(R->HL, ReadZ80(R->HL)-1); break;
		case LDHL_N: WriteZ80(R->HL, ReadZ80(++R->PC)); break;
		case SCF: R->F|=1; break;
		case JRCE: if ((R->F&0x01)==0) R->PC+=ReadZ80(++R->PC); break;
		case ADDHLSP: R->HL+=R->SP; break;
		case LDANN_: AW=ReadZ80(++R->PC)<<8; AW+=ReadZ80(++R->PC);
					 R->A=ReadZ80(AW); break;
		case DECSP: R->SP--; break;
		case INCA: R->A++; break;
		case DECA: R->A--; break;
		case LDAN: R->A=ReadZ80(++R->PC); break;
		case CCF: R->F^=0x11; break; //Esta mal (bit 5 no hace lo que debe)
		case LDBB: LDRR(B,B); break;
		case LDBC: LDRR(B,C); break;
		case LDBD: LDRR(B,D); break;
		case LDBE: LDRR(B,E); break;
		case LDBH: LDRR(B,H); break;
		case LDBL: LDRR(B,L); break;
		case LDBHL_: R->B=ReadZ80(R->HL); break;
		case LDBA: LDRR(B,A); break;
		
		case LDCB: LDRR(C,B); break;
		case LDCC: LDRR(C,C); break;
		case LDCD: LDRR(C,D); break;
		case LDCE: LDRR(C,E); break;
		case LDCH: LDRR(C,H); break;
		case LDCL: LDRR(C,L); break;
		case LDCHL_: R->C=ReadZ80(R->HL); break;
		case LDCA: LDRR(C,A); break;
		
		case LDDB: LDRR(D,B); break;
		case LDDC: LDRR(D,C); break;
		case LDDD: LDRR(D,D); break;
		case LDDE: LDRR(D,E); break;
		case LDDH: LDRR(D,H); break;
		case LDDL: LDRR(D,L); break;
		case LDDHL_: R->D=ReadZ80(R->HL); break;
		case LDDA: LDRR(D,A); break;
			
		case LDEB: LDRR(E,B); break;
		case LDEC: LDRR(E,C); break;
		case LDED: LDRR(E,D); break;
		case LDEE: LDRR(E,E); break;
		case LDEH: LDRR(E,H); break;
		case LDEL: LDRR(E,L); break;
		case LDEHL_: R->E=ReadZ80(R->HL); break;
		case LDEA: LDRR(E,A); break;
			
		case LDHB: LDRR(H,B); break;
		case LDHC: LDRR(H,C); break;
		case LDHD: LDRR(H,D); break;
		case LDHE: LDRR(H,E); break;
		case LDHH: LDRR(H,H); break;
		case LDHL: LDRR(H,L); break;
		case LDHHL_: R->H=ReadZ80(R->HL); break;
		case LDHA: LDRR(H,A); break;
			
		case LDLB: LDRR(L,B); break;
		case LDLC: LDRR(L,C); break;
		case LDLD: LDRR(L,D); break;
		case LDLE: LDRR(L,E); break;
		case LDLH: LDRR(L,H); break;
		case LDLL: LDRR(L,L); break;
		case LDLHL_: R->L=ReadZ80(R->HL); break;
		case LDLA: LDRR(L,A); break;
			
		case LDHL_B: WriteZ80(R->HL,R->B); break;
		case LDHL_C: WriteZ80(R->HL,R->C); break;
		case LDHL_D: WriteZ80(R->HL,R->D); break;
		case LDHL_E: WriteZ80(R->HL,R->E); break;
		case LDHL_H: WriteZ80(R->HL,R->H); break;
		case LDHL_L: WriteZ80(R->HL,R->L); break;
		case HALT: break;//<------------------------------------ SIN HACER
		case LDHL_A: WriteZ80(R->HL, R->A); break;
		case LDAB: LDRR(A,B); break;
		case LDAC: LDRR(A,C); break;
		case LDAD: LDRR(A,D); break;
		case LDAE: LDRR(A,E); break;
		case LDAH: LDRR(A,H); break;
		case LDAL: LDRR(A,L); break;
		case LDAHL_: R->A=ReadZ80(R->HL); break;
		case LDAA: LDRR(A,A); break;
		case ADDAB: R->A+=R->B; break; 
		case ADDAC: R->A+=R->C; break;
		case ADDAD: R->A+=R->D; break;
		case ADDAE: R->A+=R->E; break;	
		case ADDAH: R->A+=R->H; break;	
		case ADDAL: R->A+=R->L; break;
		case ADDAHL_: R->A+=ReadZ80(R->HL); break;
		case ADDAA: R->A+=R->A; break;
		case ADCAB: R->A=R->A+R->B+(R->F&0x01); break; 
		case ADCAC: R->A=R->A+R->C+(R->F&0x01); break;
		case ADCAD: R->A=R->A+R->D+(R->F&0x01); break;
		case ADCAE: R->A=R->A+R->E+(R->F&0x01); break;	
		case ADCAH: R->A=R->A+R->H+(R->F&0x01); break;	
		case ADCAL: R->A=R->A+R->L+(R->F&0x01); break;
		case ADCAHL_: R->A=R->A+ReadZ80(R->HL)+(R->F&0x01); break;
		case ADCAA: R->A=R->A+R->A+(R->F&0x01); break;	
		case SUBB: R->A-=R->B; break;
		case SUBC: R->A-=R->C; break;
		case SUBD: R->A-=R->D; break;
		case SUBE: R->A-=R->E; break;
		case SUBH: R->A-=R->H; break;
		case SUBL: R->A-=R->L; break;
		case SUBHL_: R->A-=ReadZ80(R->HL); break;
		case SUBA: R->A-=R->A; break;
		case SBCAB: R->A=R->A-R->B-(R->F&0x01); break;
		case SBCAC: R->A=R->A-R->C-(R->F&0x01); break;
		case SBCAD: R->A=R->A-R->D-(R->F&0x01); break;			
		case SBCAE: R->A=R->A-R->E-(R->F&0x01); break;			
		case SBCAH: R->A=R->A-R->H-(R->F&0x01); break;	
		case SBCAL: R->A=R->A-R->L-(R->F&0x01); break;
		case SBCAHL_: R->A=R->A-ReadZ80(R->HL)-(R->F&0x01); break;
		case SBCAA: R->A=-(R->F&0x01); break;
		case ANDB: R->A&=R->B; break;
		case ANDC: R->A&=R->C; break;
		case ANDD: R->A&=R->D; break;
		case ANDE: R->A&=R->E; break;
		case ANDH: R->A&=R->H; break;
		case ANDL: R->A&=R->L; break;
		case ANDHL_: R->A&=ReadZ80(R->HL); break;
		case ANDA: R->A&=R->A; break;
		case XORB: R->A^=R->B; break;
		case XORC: R->A^=R->C; break;
		case XORD: R->A^=R->D; break;
		case XORE: R->A^=R->E; break;
		case XORH: R->A^=R->H; break;
		case XORL: R->A^=R->L; break;
		case XORHL_: R->A^=ReadZ80(R->HL); break;
		case XORA: R->A^=R->A; break;
		case ORB: R->A|=R->B; break;
		case ORC: R->A|=R->C; break;
		case ORD: R->A|=R->D; break;
		case ORE: R->A|=R->E; break;
		case ORH: R->A|=R->H; break;
		case ORL: R->A|=R->L; break;
		case ORHL_: R->A|=ReadZ80(R->HL); break;
		case ORA: R->A|=R->A; break;	
		case CPB: if (R->A-R->B==0) R->F&=0x01; else R->F&=0x00; break;	//<------------------
		case CPC: if (R->A-R->C==0) R->F&=0x01; else R->F&=0x00; break;	//<------------------
		case CPD: if (R->A-R->D==0) R->F&=0x01; else R->F&=0x00; break;	//<------------------
		case CPE: if (R->A-R->E==0) R->F&=0x01; else R->F&=0x00; break;	//<------------------
		case CPH: if (R->A-R->H==0) R->F&=0x01; else R->F&=0x00; break;	//<------SIN HACER---
		case CP_L: if (R->A-R->L==0) R->F&=0x01; else R->F&=0x00; break;	//<--------------
		case CPHL_: if (R->A-ReadZ80(R->HL)==0) R->F&=0x01; else R->F&=0x00;  break;	//<--
		case CPA: if (R->A-R->A==0) R->F&=0x01; else R->F&=0x00; break;	//<------------------
		case RETNZ: if ((R->F&0x40)>>5!=0); break;

			
		default: printf("NO FUFA\n"); break;
	}
	++R->PC;
	return 0;
}
int inttobit(byte k)
{
	int i;
	for (i=0; i<sizeof(k)*8; i++, k<<=1) printf("%d",(k&0x80)>>7);
	printf("\n");
	return 0;
}









