/***************************************************************************************
  Z80.h 1.0
  (C) 30/01/2012 23:39:23 by MARCOS BRITO, marbri91@gmail.com
Description: Emulador del Z80
 **************************************************************************************/
#ifndef Z80_hpp
#define Z80_hpp
//#define ENDIAN
typedef unsigned char byte;
typedef unsigned short word;
typedef struct
{
#ifdef EDIAN
	union {	struct { byte A; byte F;}; word AF;};
	union {	struct { byte B; byte C;}; word BC;};
	union {	struct { byte D; byte E;}; word DE;};
	union {	struct { byte H; byte L;}; word HL;};
	union {	struct { byte A_; byte F_;}; word AF_;};
	union {	struct { byte B_; byte C_;}; word BC_;};
	union {	struct { byte D_; byte E_;}; word DE_;};
#else
	union {	struct { byte F; byte A;}; word AF;};
	union {	struct { byte C; byte B;}; word BC;};
	union {	struct { byte E; byte D;}; word DE;};
	union {	struct { byte L; byte H;}; word HL;};
	union {	struct { byte F_; byte A_;}; word AF_;};
	union {	struct { byte C_; byte B_;}; word BC_;};
	union {	struct { byte E_; byte D_;}; word DE_;};
#endif
	byte I,R;
	word IX,IY;
	word SP;
	word PC;
} RZ80;

enum
{
	NOP,LDBCNN,LDBCA,INCBC,INCB,DECB,LDBN,RLCA,
	EXAFAF_,ADDHLBC,LDABC,DECBC,INCC,DECC,LDCN,
	RRCA,DJNZ,LDDENN,LDDEA,INCDE,INCD,DECD,LDDN,
	RLA,JRE,ADDHLDE,LDADE,DECDE,INCE,DECE,LDEN,
	RRA,JRNZE,LDHLNN,LDNN_HL,INCHL,INCH,DECH,LDHN,
	DAA,JRZE,ADDHLHL,LDHLNN_,DECHL,INCL,DECL,LDLN,
	CPL,JRNCE,LDSPNN,LDNN_A,INCSP,INCHL_,DECHL_,
	LDHL_N,SCF,JRCE,ADDHLSP,LDANN_,DECSP,INCA,
	DECA,LDAN,CCF,LDBB,LDBC,LDBD,LDBE,LDBH,LDBL,
	LDBHL_,LDBA,LDCB,LDCC,LDCD,LDCE,LDCH,LDCL,
	LDCHL_,LDCA,LDDB,LDDC,LDDD,LDDE,LDDH,LDDL,
	LDDHL_,LDDA,LDEB,LDEC,LDED,LDEE,LDEH,LDEL,
	LDEHL_,LDEA,LDHB,LDHC,LDHD,LDHE,LDHH,LDHL,
	LDHHL_,LDHA,LDLB,LDLC,LDLD,LDLE,LDLH,LDLL,
	LDLHL_,LDLA,LDHL_B,LDHL_C,LDHL_D,LDHL_E,LDHL_H,
	LDHL_L,HALT,LDHL_A,LDAB,LDAC,LDAD,LDAE,LDAH,LDAL,
	LDAHL_,LDAA,ADDAB,ADDAC,ADDAD,ADDAE,ADDAH,ADDAL,
	ADDAHL_,ADDAA,ADCAB,ADCAC,ADCAD,ADCAE,ADCAH,ADCAL,
	ADCAHL_,ADCAA,SUBB,SUBC,SUBD,SUBE,SUBH,SUBL,
	SUBHL_,SUBA,SBCAB,SBCAC,SBCAD,SBCAE,SBCAH,SBCAL,
	SBCAHL_,SBCAA,ANDB,ANDC,ANDD,ANDE,ANDH,ANDL,
	ANDHL_,ANDA,XORB,XORC,XORD,XORE,XORH,XORL,
	XORHL_,XORA,ORB,ORC,ORD,ORE,ORH,ORL,ORHL_,
	ORA,CPB,CPC,CPD,CPE,CPH,CP_L,CPHL_,CPA,RETNZ
};

byte RAM[0xFFFF];

int ResetZ80(RZ80 *R);
const byte ReadZ80(word A);

int ExecZ80(RZ80 *R);

int inttobit(byte k);
#endif