/**********************************************************************************************************************/
/* Processor Identification                                                                                           */
/**********************************************************************************************************************/

//Name		Title																				Revision

/*
AMD			AMD-K6 Processor Model 6 Revision Guide												G		1998 August
AMD			AMD-K6 Processor Model 7 Revision Guide												H		1999 June
AMD			AMD-K6-2 Processor Model 8 Revision Guide											F		1999 June
AMD			AMD-K6-III Processor Model 9 Revision Guide											C		1999 July
AMD			AMD Athlon Processor Model 1 & Model 2 Revision Guide								D		2000 August
AMD			AMD Athlon Processor Model 3 Revision Guide											H		2002 July
AMD			AMD Athlon Processor Model 4 Revision Guide											H		2002 July
AMD			AMD Athlon Processor Model 6 Revision Guide											D		2002 July
AMD			AMD Athlon Processor Model 7 Revision Guide											B		2002 July
AMD			AMD Athlon Processor Model 8 Revision Guide											B		2002 June

AMD			AMD Processor Recognition															V		2002 August

Intel		Intel386 CX/SXSA Microprocessor Specification Update								002		1997 January
Intel		Intel386 DX Processor Specification Update											002		1997 January
Intel		Intel386 EX Embedded Processor Specification Update									010		1998 October
Intel		60- and 66-MHz Pentium Processor Specification Update								001		1997 February
Intel		Pentium Processor Specification Update												041		1999 January
Intel		Pentium Pro Processor Specification Update											039		1999 January
Intel		Mobile Intel Celeron Processor at 466 MHz, ... Specification Update					038		2002 November
Intel		Mobile Intel Pentium II Processor Specification Update								046		2002 November
Intel		Intel Pentium II Xeon Processor Specification Update								032		2002 January
Intel		Intel Pentium II Processor Specification Update										049		2002 July
Intel		Intel Celeron Processor Specification Update										047		2002 October
Intel		Intel Pentium III Processor Specification Update									045		2002 November
Intel		Mobile Intel Celeron Processor (0.18µ and 0.13µ) Specification Update				030		2002 August
Intel		Mobile Intel Pentium III Processor and ... Specification Update						036		2002 November
Intel		Intel Pentium III Xeon Processor Specification Update								037		2002 July
Intel		Intel Pentium 4 Processor Specification Update										029		2002 November
Intel		Mobile Intel Pentium 4 Processor-M Specification Update								008		2002 November
Intel		Intel Celeron Processor in the 478-Pin Package Specification Update					005		2002 November
Intel		Mobile Intel Celeron Processor on .13 Micron ... Specification Update				002		2002 August
Intel		Intel Xeon Processor Specification Update											020		2002 November
Intel		Intel Xeon Processor MP Specification Updata										009		2002 November

Intel		Intel Itanium Processor Specification Update										008		2003 January
Intel		Intel Itanium 2 Processor Specification Update										007		2003 January

Intel		Intel Processor Identification and the CPUID Instruction							022		2002 November
Intel		Intel Processor Serial Number														001		1999 March

IDT			IDT WinChip C6 Data Sheet															1.10	1998 March
*/

#include <mem.h>
#include <string.h>
#include <bootlog.h>
#include <cpu.h>

struct IdentificationStructure
{
	struct
	{
		int Family;
		int Model;
		int Stepping;
		int Type;
		char* VendorID;
		int BrandNumber;
		char* BrandString;

		int ExtendedFamily;
		int ExtendedModel;
		int ExtendedStepping;
		int ExtendedType;
		char* ExtendedVendorID;

		char* Name;
	} Processor;

	struct
	{
		bool FloatingPoint;
		bool MMX;
		bool aMMX;
		bool cMMX;
		bool SSE;
		bool SSE2;
		bool FXSR;
		bool CompareAndExchange8;
		bool FastSystemCall;
		bool SYSCALL;
		bool ConditionalMove;
		bool CacheLineFlush;
		bool IA64;
		bool ThreeDNow;
		bool ThreeDNowExtensions;
	} Instructions;

	struct
	{
		bool VirtualModeExtensions;
		bool DebuggingExtensions;
		bool PageSizeExtensions;
		bool TimeStampCounter;
		bool ModelSpecificRegisters;
		bool PhysicalAddressExtension;
		bool MachineCheckException;
		bool LocalAPIC;
		bool MemoryTypeRangeRegisters;
		bool PageGlobalEnable;
		bool MachineCheckArchitecture;
		bool PageAttributeTable;
		bool PageSizeExtension36;
		bool DebugStore;
		bool ACPI;
		bool SelfSnoop;
		bool HyperThreadingTechnology;
		bool ThermalMonitor;
		bool SignalBreakOnFERR;

		bool ProcessorSerialNumber;
		
		bool MultiProcessing;
		bool TemperatureSensor;
		bool FrequencyIDControl;
		bool VoltageIDControl;
	} Features;

	struct
	{
		bool HasSerialNumber;
		unsigned SerialNumber1;
		unsigned SerialNumber2;
		unsigned SerialNumber3;
		unsigned SerialNumber4;
	} Signature;

	struct
	{
		int CacheLineSize;
		int LogicalProcessors;
		int LocalAPICPhysicalID;

		bool LongMode;

		int MaximumPhysicalAddress;
		int MaximumLogicalAddress;

		bool ContextID;

	} Unknown;

	struct
	{
		struct {bool Present; int Size; int Associativity; int LineSize; int LinesPerTag;} L1CodeCache;
		struct {bool Present; int Size; int Associativity; int LineSize; int LinesPerTag;} L1DataCache;
		struct {bool Present; int Size; int Associativity; int LineSize; int LinesPerTag;} L1UnifiedCache;
		struct {bool Present; int Size; int Associativity; int LineSize; int LinesPerTag;} L2UnifiedCache;
		struct {bool Present; int Size; int Associativity; int LineSize; int LinesPerTag;} L3UnifiedCache;
		
		struct {bool Present; int Entries; int Associativity;} L1CodeTLB4K;
		struct {bool Present; int Entries; int Associativity;} L1CodeTLB2M;
		struct {bool Present; int Entries; int Associativity;} L1CodeTLB4M;
		struct {bool Present; int Entries; int Associativity;} L1DataTLB4K;
		struct {bool Present; int Entries; int Associativity;} L1DataTLB2M;
		struct {bool Present; int Entries; int Associativity;} L1DataTLB4M;

		struct {bool Present; int Entries; int Associativity;} L2CodeTLB4K;
		struct {bool Present; int Entries; int Associativity;} L2CodeTLB2M;
		struct {bool Present; int Entries; int Associativity;} L2CodeTLB4M;
		struct {bool Present; int Entries; int Associativity;} L2DataTLB4K;
		struct {bool Present; int Entries; int Associativity;} L2DataTLB2M;
		struct {bool Present; int Entries; int Associativity;} L2DataTLB4M;
		struct {bool Present; int Entries; int Associativity;} L2UnifiedTLB4K;
		struct {bool Present; int Entries; int Associativity;} L2UnifiedTLB2M;
		struct {bool Present; int Entries; int Associativity;} L2UnifiedTLB4M;

		struct {bool Present; int MicroOps; int Associativity;} TraceCache;

	} Cache;

	struct {
		bool Feature10;
		bool Feature20;
		bool Feature32;
		bool Feature33;
		bool Feature34;
		bool Feature35;
		bool Feature36;
		bool Feature37;
		bool Feature38;
		bool Feature39;
		bool Feature40;
		bool Feature41;
		bool Feature43;
		bool Feature44;
		bool Feature45;
		bool Feature46;
		bool Feature47;
		bool Feature48;
		bool Feature49;
		bool Feature50;
		bool Feature51;
		bool Feature52;
		bool Feature53;
		bool Feature54;
		bool Feature55;
		bool Feature56;
		bool Feature57;
		bool Feature58;
		bool Feature59;
		bool Feature60;
		bool Feature61;
		bool Feature62;
		bool Feature63;

		bool ExtendedFeature10;
		bool ExtendedFeature18;
		bool ExtendedFeature20;
		bool ExtendedFeature21;
		bool ExtendedFeature25;
		bool ExtendedFeature26;
		bool ExtendedFeature27;
		bool ExtendedFeature28;
	} Reserved;
};

bool SupportsCPUID(void);
void Identify(IdentificationStructure &IdentificationData);
void IdentifyIntelCache(IdentificationStructure &IdentificationData, int CacheDescriptor);
int AMDAssociativity(int Value);
void IdentifyProcessor(IdentificationStructure &IdentificationData, int Extra);

void cpuInit(void)
{
	IdentificationStructure x;
	Identify(x);
	logSubItem("Vendor", x.Processor.VendorID);
	logSubItem("CPU0", x.Processor.Name);
	logSubItem("Floating Point", x.Instructions.FloatingPoint ? "True" : "False");
	logSubItem("iMMX", x.Instructions.MMX ? "True" : "False");
	logSubItem("aMMX", x.Instructions.aMMX ? "True" : "False");
	logSubItem("cMMX", x.Instructions.cMMX ? "True" : "False");
	logSubItem("iSSE", x.Instructions.SSE ? "True" : "False");
	logSubItem("iSSE2", x.Instructions.SSE2 ? "True" : "False");
	logSubItem("3DNow!", x.Instructions.ThreeDNow ? "True" : "False");
	logSubItem("Extended 3DNow!", x.Instructions.ThreeDNowExtensions ? "True" : "False");
}

struct PROCLIST {
	char*	VendorID;
	int		Family;
	int		Model;
	int		Stepping;
	int		Extra;
	char*	Name;
	int		Class;
	int		MfgStepping;
	int		Errata1;
	int		Errata2;
	int		Errata3;
	int		Errata4;
};

/*
	Mobile Athlon Detection
  
	Problems with CPU identication:

  1) How much information?
  2) Getting the information

  CPU identification has two purposes: OS information and user information. Since this module wil be
  used in TriOS we'll only need OS information (ident upto stepping for erratas) No process size,
  packaging or voltage info. I can be found withofficial name and codename. To prevent user confusion
  we need to show the diff between Celeron / Pentium / Xeon. Cache info is important for some memory
  defragmentation and alignment algorithms, perhaps.

  OLD CPUS:

  i4004 / i4040
  i8008 / i8080 / i8080A / Zilog Z80 / i8085A / i8085AH

  2.13 Contemporary CPUs 
	Contemporary 16 bit CPUs to 8086/8088 were Zilog Z8000 CPU, Fairchild 9445 CPU, Texas Instruments TI9900 CPU and Mil-Std 1750A CPU. Last is reason DOD (Department Of Defence) contractors were not interested in 8086/8088. Mil-Std 1750A CPU was specified in all contracts of 1979 - 1984 period.
	Texas Instruments TI9900 CPU was probably the best of the lot, but Texas Instruments considered it a closed architecture, so no-one used it. 



  8086 - 80368	Intel Only
  80486			Lots of manufacturers, almost no stpping info
  80586			Lots of incorrect information and processors that were never sold, no stepping info
  80686			Celeron / Pentium / Xeon // !Mobile! (Inel realy srewed up the names here)
  80786			VERY WELL DONE BY INTEL (at least names are a bit more consistant)
  80886			Not officialy realeasd at the moment

	Intel detection:	AAA xxh doesn't #UD
	Cyrix Detection:	Read the chipset data, but I heard there was a better one
	AMD Detection		If there not TI, IBM, UMC, Cyrix or Intel, must be AMD, need sometin' better
	UMC Detection		support CPUID I believe
	Texas Detection		Models do not real conflic (aren't those things the same as IBM have to check)
	IBM Detection		Ax or 8x as family (but there are exceptions) and models do not conflict


	CYRIX/TI/IBM Identificaton through Chipset Data (I/O 22h and 23h)


	Not about the use of stepping and revision:
		Stepping is used always. I try to change this into: Stepping = A0 / Revision = 3h
		Intel also calls the revion Stepping ID


	386 Reset Data
	 0- 3	Minor Stepping		Revision
	 4- 7	Major Stepping		Model
	 8-11	Family				Family
	12-15	Type				DX/SX/SL and TI/IBM/Intel


	486+ Reset Data
	 0- 3 	Revision
	 4- 7 	Model
	 8-11	Family
	12-13	Type				0 = Normal, 1 = OverDrive, 2 = Second Processor, 3 = Reserved
	14-15	Reserved
	16-19	Extended Model
	20-27	Extended Family
	28-30	Reserved
	31		Reserved			Has Serial Number


	All over drives could also have type 0 if they are an errata (whatever that means)

	Legal Mumbo Jumbo: In the CPUID Documentation, Intel says the PSN could be reported wrongly, for
		example if the voltage or frequency is wrong. It doesn't say it's corec when the processor is
		working on the correct voltage and frequency...

  IF HighetExtened CPUID Fucntion > 0x80000000 Brand String is supported, even if 0x800000001 or 2 ???

  Should OverDrives just be ignored? According to Intel internal caches or execution times may vary
  According to Intel CPUID is unreliable in V86 Mode
  According to Intel MSRs vary between different Models of the Pentium (P5 that is)
  PSN is not guaranteed to be unique
  Intel PSN Style: XXXX-XXXX-XXXX-XXXX-XXXX-XXXX		(96 bit)
  Transmeta PSN S: XXXXXXXX:XXXXXXXX:XXXXXXXX:XXXXXXXX	(128 bit)
  Intel says apps need to use the BRAND STRING to identify the processor (ARE THEY CRAZY???)
  Intel says apps need to use the BRAND ID to identify the processor (not crazy, but useless)

  DAZ DAZ DAZ DAZ DAZ DAZ DAZ

	11 DENORMALS ARE ZERO
		With the introduction of the SSE2 extensions, some Intel Architecture processors have the ability to convert SSE
		and SSE2 source operand denormal numbers to zero. This feature is referred to as Denormals -Are-Zero (DAZ). The
		DAZ mode is not compatible with IEEE Standard 754. The DAZ mode is provided to improve processor
		performance for applications such as streaming media processing, where rounding a denormal operand to zero does
		not appreciably affect the quality of the processed data.
		Some processor steppings support SSE2 but do not support the DAZ mode. To determine if a processor supports the
		DAZ mode, software must perform the following steps.
		1. Execute the CPUID instruction with an input value of EAX=0 and ensure the vendor-ID string returned is “GenuineIntel”.
		2. Execute the CPUID instruction with EAX=1. This will load the EDX register with the feature flags.
		3. Ensure that the FXSR feature flag (EDX bit 24) is set. This indicates the processor supports the FXSAVE and FXRSTOR
		instructions.
		4. Ensure that the XMM feature flag (EDX bit 25) or the EMM feature flag (EDX bit 26) is set. This indicates that the
		processor supports at least one of the SSE/SSE2 instruction sets and its MXCSR control register.
		5. Zero a 16-byte aligned, 512-byte area of memory. This is necessary since some implementations of FXSAVE do not modify
		reserved areas within the image.
		6. Execute an FXSAVE into the cleared area.
		7. Bytes 28-31 of the FXSAVE image are defined to contain the MXCSR_MASK. If this value is 0, then the processor's
		MXCSR_MASK is 0xFFBF, otherwise MXCSR_MASK is the value of this dword.
		8. If bit 6 of the MXCSR_MASK is set, then DAZ is supported.
		After completing this algorithm, if DAZ is supported, software can enable DAZ mode by setting bit 6 in the
		MXCSR register save area and executing the FXRSTOR instruction. Alternately software can enable DAZ mode by
		setting bit 6 in the MXCSR by executing the LDMXCSR instruction. Refer to the chapter titled “Programming with
		the Streaming SIMD Extensions (SSE)” in the Intel Architecture Software Developer’s Manual volume 1: Basic
		Architecture.

	DAZ DAZ DAZ DAZ DAZ DAZ DAZ

  Legacy detecyion

	8086	EFLAGS 12-15 are always set
	80286	EFLAGS 12-15 are clear in RM
	80366	EFLAGS 18	Cant be set, if it can it a 486+
	80848	EFLAGS 21	Can't be set, if it can use CPUID

	FPU		If control/status word can be saved it's present
	27/387	Infinity control Rounding Stuff

	487		486 with coproc


  What about the Xeon DP????

  CMXCHG8B	Disabled because of Stuoid MSWinNT bug (studpid. Microsft not diabling. stupid)




  sAVE bRAND sTRING BEFRORE s3 POWER DOWN


  NSC Geode!!!!
  Tillamook = Mobile Pentium MMX



  "The iAPX 286 will push a different value on the stack for PUSH SP than the iAPX 86/88."
  "When a word write is performed at offset FFFFh in a segment, the 8086 will write one byte at offset
		FFFFh, and the other at offset 0, while an 80186 family processor will write one byte at offset
		FFFFh, and the other at offset 10000h (one byte beyond the end of the segment)."




 */

PROCLIST ProcessorList[] =
{
	/** Intel 8086 / 8088 (Includes model manufactured by AMD, Harris, Siemens, Hitachi) ************/

	//I belive there an alroithm to identify the diff between HMOS and CMOS models
	{"GenuineIntel", 1, 0, 0, 0, "Intel 8088"},
	{"GenuineIntel", 1, 0, 0, 1, "Intel 8086"},
	{"GenuineIntel", 1, 0, 0, 2, "Intel 80C88"},
	{"GenuineIntel", 1, 0, 0, 3, "Intel 80C86"},
	{"GenuineIntel", 1, 0, 0, 4, "Intel 80188"},	//XL/EA/EB/EC		AMD/Siemens
	{"GenuineIntel", 1, 0, 0, 5, "Intel 80186"},	//XL/EA/EB/EC		AMD/Siemens
	{"GenuineIntel", 1, 0, 0, 6, "NEC V20"},	//V20H/V25/V25 Plus/V25 Softwae Guard/V40/V40H//V45
	{"GenuineIntel", 1, 0, 0, 7, "NEC V30"},	//V30H/V35/V35 Plus/V35 Softwae Guard/V50/V50H//V55
	//Intel 80886???

	{"GenuineIntel", 2, 0, 0, 0, "Intel 80286"},//amd/harris/siemens/fujitsu/kruger
	
	
	/** Intel 386 ***********************************************************************************/

	
	//The 386 use a very different format: Family (8-bits!) + Revision (8-bits! Model+Stepping)
	//Not to myself: The high four bits of the family should coume in the extra field
	//These chips were also munufactured by AMD!!! They are affected by the POPAD bug????
	//Old (sigma-pi) i386 have 32-bit multipy bug
	//C&T 38600DX do not have POPAD bug. IBM 386SLC unknwon
	//AMD 386DX & DXL hav Intel microcode
	//AMD 386DXLV & SXLV hav UMOV???
	//Nx586 has no AC has 386 instr set

	//Erly modles (A stepping) as Famuly: 0, Revision: ??? (In Intel Docs! Support the 'Bit Instrucs')
	//0300
	// * Intel i386DX			: F0
	{"GenuineIntel", 3, 0, 3, 0, "Intel i386DX (B0/B1/B2/B3/B4/B5/B6/B7/B8/B9/B10)"},
	{"GenuineIntel", 3, 0, 4, 0, "Intel i386DX (C???)"},	// Stepping not confiremed
	{"GenuineIntel", 3, 0, 5, 0, "Intel i386DX (D0)"},
	{"GenuineIntel", 3, 0, 8, 0, "Intel i386DX (D1/D2/E0/E1/F0)"}, //E0/E1/F0 coulld also be 9!!!
	
	//The family 23 could also simply be 3 (I don't know were the 2 stands for???) Officialy not part
	//Difference between DX and SX perhaps (I hope so)
	// * Intel i386CX/SXSA		: A2 / B
	// * Intel i386EX			: A0 / B1 / B2
	{"GenuineIntel",23, 0, 4, 0, "Intel i386SX (A0)"},
	{"GenuineIntel",23, 0, 5, 0, "Intel i386SX (B)"},
	{"GenuineIntel",23, 0, 8, 0, "Intel i386SX (C/D/E)"},
	{"GenuineIntel",23, 0, 8, 0, "Intel i386CXSA/B (A) / i386EX (A) / i386SXSA (?)"},	//A || B
	{"GenuineIntel",23, 0, 9, 0, "Intel i386SX (?)"},	//EMBEDDED (CX/FX
	{"GenuineIntel",23, 0, 9, 0, "Intel i386EX (A0/B1/C1)"},
	
	//Dito for 33 (376 perhaps)
	{"GenuineIntel",33, 0, 5, 0, "Intel i376 (A0)"}, //Never used in PC because they only work in PM
	{"GenuineIntel",33, 0, 8, 0, "Intel i376 (B)"},  //...

	//And againt for 43 (386SL)
	//have a signatur register @ 30e
	//step level A0: 0x4300, 
	//step level A1: 0x4300, 
	//step level A2: 0x4301, 
	//step level A3: 0x4302, 
	//step level B0: 0x4310, 
	//step level B1: 0x4311. 
//	{"GenuineIntel",43, 0, 5, ?, "Intel i386SL (B)"},
//	{"GenuineIntel",43, 0, 5, ?, "Intel i386SL (A0/A1/A2/A3)"},	//Not sure about this
//	{"GenuineIntel",43, 1, 0, 0, "Intel i386SL (A0/A1/A2/A3)"},
//	{"GenuineIntel",43, 1, 1, 0, "Intel i386SL (B0/B1)"},

	//RapidCADs are not so familiar to me, where they ever used in PCs???
	{"GenuineIntel", 3, 4, 0, 0, "Intel RapidCAD (A)"},
	{"GenuineIntel", 3, 4, 1, 0, "Intel RapidCAD (B)"},


	/** Intel 486 ***********************************************************************************/
	
	//According to Intel only SL Enhanced and WB Enhanced processors support CPUID
	
	{"GenuineIntel", 4, 0, 0, 0, "Intel i486DX (A0/A1)"},
	{"GenuineIntel", 4, 0, 1, 0, "Intel i486DX (B2/B3/B4/B5/B6)"},
	{"GenuineIntel", 4, 0, 2, 0, "Intel i486DX (C0)"},
	{"GenuineIntel", 4, 0, 3, 0, "Intel i486DX (C1)"},
	{"GenuineIntel", 4, 0, 4, 0, "Intel i486DX (D0)"},
//	{"GenuineIntel", 4, 0, ?, 0, "Intel i486DX"},

	{"GenuineIntel", 4, 1, 0, 0, "Intel i486DX (cA2/cA3)"},
	{"GenuineIntel", 4, 1, 1, 0, "Intel i486DX (cB0/cB1)"},
	{"GenuineIntel", 4, 1, 3, 0, "Intel i486DX (cC0)"},
	{"GenuineIntel", 4, 1, 4, 0, "Intel i486DX (aA0/aA1)"},	//SL Enhanced
	{"GenuineIntel", 4, 1, 5, 0, "Intel i486DX (aB0)"},	//SL Enhanced
//	{"GenuineIntel", 4, 1, ?, 0, "Intel i486DX"},

	{"GenuineIntel", 4, 2, 0, 0, "Intel i486SX / i487SX (A0)"},	//Should 487 be model 3
	{"GenuineIntel", 4, 2, 1, 0, "Intel i487SX (B0)"},	//Should 487 be model 3
	{"GenuineIntel", 4, 2, 2, 0, "Intel i486SX (B0)"},
	{"GenuineIntel", 4, 2, 3, 0, "Intel i486SX (bBx)"},	//SL Enhanced and... CPUID
	{"GenuineIntel", 4, 2, 4, 0, "Intel i486SX (gAx)"},
	{"GenuineIntel", 4, 2, 7, 0, "Intel i486SX (cA0)"},
	{"GenuineIntel", 4, 2, 8, 0, "Intel i486SX (cB0)"},
	{"GenuineIntel", 4, 2, 0xA, 0, "Intel i486SX (aA0/aA1)"},	//SL Enhanced
	{"GenuineIntel", 4, 2, 0xB, 0, "Intel i486SX (aB0/aC0)"},	//SL Enhanced
	{"GenuineIntel", 4, 2, 0xE, 0, "Intel i486SX (E)"},	//SL Enhanced??? Grzegorz
//	{"GenuineIntel", 4, 2, ?, 0, "Intel i486SX"},

//	{"GenuineIntel", 4, 3, ?, 0, "Intel i486DX2 / i486DX2 OverDrive / i487"},
	{"GenuineIntel", 4, 3, 2, 0, "Intel i486DX2 (A0/A1/A2)"},
	{"GenuineIntel", 4, 3, 3, 0, "Intel i486DX2 (B1)"},
	{"GenuineIntel", 4, 3, 4, 0, "Intel i486DX2 (aA0/aA1)"}, //SL Enhanced
	{"GenuineIntel", 4, 3, 5, 0, "Intel i486DX2 (aB0/aC0)"}, //SL Enhanced
	{"GenuineIntel", 4, 3, 6, 0, "Intel i486DX2"},	//Possibly as WB in WT Mode

	{"GenuineIntel", 4, 4, 0, 0, "Intel i486SL (A)"},
	{"GenuineIntel", 4, 4, 1, 0, "Intel i486SL (?)"},
	{"GenuineIntel", 4, 4, 3, 0, "Intel i486SL (?)"},	//In Intel Docs, saupoosed to support CPUID
//	{"GenuineIntel", 4, 4, ?, 0, "Intel i486SL"},

//	{"GenuineIntel", 4, 5, ?, 0, "Intel i486SX2"},
	{"GenuineIntel", 4, 5, 0xB, 0, "Intel i486SX2 (aC0)"},	//SL Enhanced

	{"GenuineIntel", 4, 7, 0, 0, "Intel i486DX2-WB (A)"},
	{"GenuineIntel", 4, 7, 3, 0, "Intel i486DX2-WB (?)"},	//In Intel Docs, saupoosed to support CPUID
//	{"GenuineIntel", 4, 7, ?, 0, "Intel i486DX2-WB"},

	{"GenuineIntel", 4, 8, 0, 0, "Intel i486DX4 (A)"},
	{"GenuineIntel", 4, 8, 0, 1, "Intel i486DX4 OverDrive (A)"},
	{"GenuineIntel", 4, 8, 3, 0, "Intel i486DX4 (A)"},	//Possibly as WB in WT Mode, Support CPUID
//	{"GenuineIntel", 4, 8, ?, 0, "Intel i486DX4 / i486DX4 OverDrive"},

	{"GenuineIntel", 4, 9, 0, 0, "Intel i486DX4-WB (A)"}, //(Do not exist according to Intel CPUID Inf)
//	{"GenuineIntel", 4, 9, ?, 0, "Intel i486DX4-WB"},

	/** Intel Pentium *******************************************************************************/
	
//	{"GenuineIntel", 0x05, 0x00, 0x0?,    0, /*false,*/ "Intel Pentium Classic (A)"},
	
//	{"GenuineIntel", 0x05, 0x01, 0x02,    0, /*false,*/ "Intel Pentium Classic (Engineering Sample)"},
	{"GenuineIntel", 0x05, 0x01, 0x03,    0, /*false,*/ "Intel Pentium Classic (B1)"},
//	{"GenuineIntel", 0x05, 0x01, 0x04,    0, /*false,*/ "Intel Pentium Classic (B2)"},
	{"GenuineIntel", 0x05, 0x01, 0x05,    0, /*false,*/ "Intel Pentium Classic (C1)"},
	{"GenuineIntel", 0x05, 0x01, 0x07,    0, /*false,*/ "Intel Pentium Classic (D1)"},

	{"GenuineIntel", 0x05, 0x01, 0x0A,    0, /*false,*/ "Intel Pentium OverDrive (tA0 1.0)"},
	
	{"GenuineIntel", 0x05, 0x02, 0x01,    0, /*false,*/ "Intel Pentium+ (B1)"},
	{"GenuineIntel", 0x05, 0x02, 0x02,    0, /*false,*/ "Intel Pentium+ (B3)"},
	{"GenuineIntel", 0x05, 0x02, 0x04,    0, /*false,*/ "Intel Pentium+ (B5)"},
	{"GenuineIntel", 0x05, 0x02, 0x05,    0, /*false,*/ "Intel Pentium+ (C2) / Mobile Intel Pentium+ (mA1)"},
	{"GenuineIntel", 0x05, 0x02, 0x06,    0, /*false,*/ "Intel Pentium+ (E0)"},
	{"GenuineIntel", 0x05, 0x02, 0x0B,    0, /*false,*/ "Intel Pentium+ (cB1)"},
	{"GenuineIntel", 0x05, 0x02, 0x0C,    0, /*false,*/ "Intel Pentium+ (cC0) / Mobile Intel Pentium+ (mcC0) / Intel Pentium OverDrive (aC0)"},

	{"GenuineIntel", 0x05, 0x03, 0x01,    1, /*false,*/ "Intel Pentium OverDrive (B1 / B2 / C0)"},
	{"GenuineIntel", 0x05, 0x03, 0x02,    1, /*false,*/ "Intel Pentium OverDrive (C0)"},

//	{"GenuineIntel", 0x05, 0x04, 0x01,    0, /*false,*/ "Intel Pentium MMX (A1)"},
//	{"GenuineIntel", 0x05, 0x04, 0x02,    0, /*false,*/ "Intel Pentium MMX (A2)"},
	{"GenuineIntel", 0x05, 0x04, 0x03,    0, /*false,*/ "Intel Pentium MMX (xB1) / Mobile Intel Pentium MMX 'Tillamook' (mxB1)"},
	{"GenuineIntel", 0x05, 0x04, 0x03,    1, /*false,*/ "Intel Pentium MMX OverDrive (oxB1)"},
	{"GenuineIntel", 0x05, 0x04, 0x04,    0, /*false,*/ "Intel Pentium MMX (xA3) / Mobile Intel Pentium MMX 'Tillamook' (mxA3)"},
	{"GenuineIntel", 0x05, 0x04, 0x04,    1, /*false,*/ "Intel Pentium MMX OverDrive (oxA3)"},

//	{"GenuineIntel", 0x05, 0x05, 0x0?,    0, /*false,*/ "Intel Pentium ???"},	//Grzegroz DX4 OD
//	{"GenuineIntel", 0x05, 0x06, 0x0?,    0, /*false,*/ "Intel Pentium ???"},	//Grzegroz P5 OD
	
	{"GenuineIntel", 0x05, 0x07, 0x00,    0, /*false,*/ "Mobile Intel Pentium (mA4)"},

	{"GenuineIntel", 0x05, 0x08, 0x01,    0, /*false,*/ "Mobile Intel Pentium MMX 'Tillamook' (myA0)"},
	{"GenuineIntel", 0x05, 0x08, 0x02,    0, /*false,*/ "Mobile Intel Pentium MMX 'Tillamook' (myB1)"},

	/** Intel P6 ************************************************************************************/

	//	{"GenuineIntel", 0x06, 0x00, 0x0?,    0, /*false,*/ "Intel Pentium Pro (A0 Engeneering Sample)"},

	{"GenuineIntel", 0x06, 0x01, 0x01,    0, /*false,*/ "Intel Pentium Pro (B0)"},
	{"GenuineIntel", 0x06, 0x01, 0x02,    0, /*false,*/ "Intel Pentium Pro (C0)"},
	{"GenuineIntel", 0x06, 0x01, 0x06,    0, /*false,*/ "Intel Pentium Pro (sA0)"},
	{"GenuineIntel", 0x06, 0x01, 0x07,    0, /*false,*/ "Intel Pentium Pro (sA1)"},
	{"GenuineIntel", 0x06, 0x01, 0x09,    0, /*false,*/ "Intel Pentium Pro (sB1)"},

	{"GenuineIntel", 0x06, 0x03, 0x02,    1, /*false,*/ "Intel Pentium II OverDrive (TdB0)"},
	{"GenuineIntel", 0x06, 0x03, 0x03,  512, /*false,*/ "Intel Pentium II 'Klamath' (C0)"},
	{"GenuineIntel", 0x06, 0x03, 0x04,  512, /*false,*/ "Intel Pentium II 'Klamath' (C1)"},

//	{"GenuineIntel", 0x06, 0x04, 0x0?,    0, /*false,*/ "Intel Pentium II OverDrive (?)"},

	{"GenuineIntel", 0x06, 0x05, 0x00,    0, /*false,*/ "Intel Celeron II 'Covington' (A0)"},
	{"GenuineIntel", 0x06, 0x05, 0x00,  512, /*false,*/ "Intel Pentium II 'Deschutes' (dA0) / Intel Pentium II Mobile 'Tonga' (mdA0)"},
	{"GenuineIntel", 0x06, 0x05, 0x01,    0, /*false,*/ "Intel Celeron II 'Covington' (A1)"},
	{"GenuineIntel", 0x06, 0x05, 0x01,  512, /*false,*/ "Intel Pentium II 'Deschutes' (dA1)"},
	{"GenuineIntel", 0x06, 0x05, 0x02,    0, /*false,*/ "Intel Celeron II 'Covington' (B0)"},
	{"GenuineIntel", 0x06, 0x05, 0x02,  512, /*false,*/ "Intel Pentium II 'Deschutes' (dB0) / Intel Xeon II 'Drake' (B0) / Intel Pentium II Mobile 'Tonga' (mdB0)"},
	{"GenuineIntel", 0x06, 0x05, 0x02, 1024, /*false,*/ "Intel Xeon II 'Drake' (B0)"},
	{"GenuineIntel", 0x06, 0x05, 0x03,  512, /*false,*/ "Intel Pentium II 'Deschutes' (B1) / Intel Xeon II 'Drake' (B1)"},
	{"GenuineIntel", 0x06, 0x05, 0x03, 1024, /*false,*/ "Intel Xeon II 'Drake' (B1)"},
	{"GenuineIntel", 0x06, 0x05, 0x03, 2048, /*false,*/ "Intel Xeon II 'Drake' (B1)"},

	{"GenuineIntel", 0x06, 0x06, 0x00,  128, /*false,*/ "Intel Celeron II 'Mendocino' (A0)"},
	{"GenuineIntel", 0x06, 0x06, 0x05,  128,  /*true,*/ "Intel Celeron II 'Mendocino' (B0)"},
	{"GenuineIntel", 0x06, 0x06, 0x0A,  128, /*false,*/ "Intel Celeron II Mobile (A0)"},
	{"GenuineIntel", 0x06, 0x06, 0x0A,  256, /*false,*/ "Intel Pentium II Mobile 'Dixon' (mdbA0 / mqbA1 / dmmA0)"},

	{"GenuineIntel", 0x06, 0x07, 0x02,  512, /*false,*/ "Intel Pentium III 'Katmai' (B0) / Intel Xeon III 'Tanner' (B0)"},
	{"GenuineIntel", 0x06, 0x07, 0x02, 1024, /*false,*/ "Intel Xeon III 'Tanner' (B0)"},
	{"GenuineIntel", 0x06, 0x07, 0x02, 2096, /*false,*/ "Intel Xeon III 'Tanner' (B0)"},
	{"GenuineIntel", 0x06, 0x07, 0x03,  512, /*false,*/ "Intel Pentium III 'Katmai' (C0) / Intel Xeon III 'Tanner' (C0)"},
	{"GenuineIntel", 0x06, 0x07, 0x03, 1024, /*false,*/ "Intel Xeon III 'Tanner' (C0)"},
	{"GenuineIntel", 0x06, 0x07, 0x03, 2096, /*false,*/ "Intel Xeon III 'Tanner' (C0)"},
	
	{"GenuineIntel", 0x06, 0x08, 0x01, 0x01, /*false,*/ "Intel Celeron III 'Coppermine' (A0)"},
	{"GenuineIntel", 0x06, 0x08, 0x01, 0x02, /*false,*/ "Intel Pentium III (Mobile) 'Coppermine' (cA2)"},
	{"GenuineIntel", 0x06, 0x08, 0x01, 0x03, /*false,*/ "Intel Xeon III 'Cascades' (A0)"},
	{"GenuineIntel", 0x06, 0x08, 0x03, 0x01, /*false,*/ "Intel Celeron III 'Coppermine' (B0)"},
	{"GenuineIntel", 0x06, 0x08, 0x03, 0x02,  /*true,*/ "Intel Pentium III (Mobile) 'Coppermine' (cB0)"},
	{"GenuineIntel", 0x06, 0x08, 0x03, 0x03, /*false,*/ "Intel Xeon III 'Cascades' (B0)"},
	{"GenuineIntel", 0x06, 0x08, 0x06, 0x01, /*false,*/ "Intel Celeron III 'Coppermine' (C0)"},
	{"GenuineIntel", 0x06, 0x08, 0x06, 0x02, /*false,*/ "Intel Pentium III (Mobile) 'Coppermine' (cC0)"},
	{"GenuineIntel", 0x06, 0x08, 0x06, 0x03, /*false,*/ "Intel Xeon III 'Cascades' (C0)"},
	{"GenuineIntel", 0x06, 0x08, 0x0A, 0x01, /*false,*/ "Intel Celeron III 'Coppermine' (D0)"},
	{"GenuineIntel", 0x06, 0x08, 0x0A, 0x02, /*false,*/ "Intel Pentium III (Mobile) 'Coppermine' (cD0)"},

	{"GenuineIntel", 0x06, 0x0A, 0x00, 0x03, /*false,*/ "Intel Xeon III 'Cascades' (A0)"},
	{"GenuineIntel", 0x06, 0x0A, 0x01, 0x03, /*false,*/ "Intel Xeon III 'Cascades' (A1)"},
	{"GenuineIntel", 0x06, 0x0A, 0x04, 0x03, /*false,*/ "Intel Xeon III 'Cascades' (B0)"},

	{"GenuineIntel", 0x06, 0x0B, 0x01, 0x03, /*false,*/ "Intel Celeron III 'Tualatin' (A1)"},
	{"GenuineIntel", 0x06, 0x0B, 0x01, 0x04, /*false,*/ "Intel Pentium III 'Tualatin' (cA1)"},
	{"GenuineIntel", 0x06, 0x0B, 0x01, 0x06, /*false,*/ "Intel Pentium III Mobile 'Geyserville' (A1)"},
	{"GenuineIntel", 0x06, 0x0B, 0x01, 0x07, /*false,*/ "Intel Celeron III Mobile 'Tualatin' (A1)"},
	{"GenuineIntel", 0x06, 0x0B, 0x04, 0x03, /*false,*/ "Intel Celeron III 'Tualatin' (B1)"},
	{"GenuineIntel", 0x06, 0x0B, 0x04, 0x04, /*false,*/ "Intel Pentium III 'Tualatin' (cB1)"},
	{"GenuineIntel", 0x06, 0x0B, 0x04, 0x06, /*false,*/ "Intel Pentium III Mobile 'Geyserville' (B1)"},

//	A finalty note: I'm looking for some information on the Intel Timna (Intel's MediaGX). The project
//	was abandonned so Intel never published any useful material on this. It was based on the P-III.

//	Also some info in the Microsoft X-Box' special P-III would help

	/** Unknown Processors ************************************************************************/
	
	{"UnknownVendr", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown Processor"},
	{"GenuineIntel", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown Intel Processor"},
	{"AuthenticAMD", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown AMD Processor"},
	{"CentaurHauls", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown Centaur Processor"},
	{"CyrixInstead", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown Cyrix Processor"},
	{"GenuineTMx86", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown Transmeta Processor"},
	{"NexGenDriven", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown NexGen Processor"},
	{"RiseRiseRise", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown Rise Processor"},
	{"UMC UMC UMC ", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown UMC Processor"},
	{"AMD ISBETTER", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown AMD Pre-Procuction Processor"},
	{"ThinkTrinary", 0xFF, 0xFF, 0xFF, 0xFF, "Unknown Trinary Processor"},

	{"GenuineIntel", 0x03, 0xFF, 0xFF, 0xFF, "Unknown Intel i386 Processor"},
	{"GenuineIntel", 0x04, 0xFF, 0xFF, 0xFF, "Unknown Intel i486 Processor"},
	{"GenuineIntel", 0x05, 0xFF, 0xFF, 0xFF, "Unknown Intel Pentium Processor"},
	{"GenuineIntel", 0x06, 0xFF, 0xFF, 0xFF, "Unknown Intel P6 Processor"},
	{"GenuineIntel", 0x0F, 0xFF, 0xFF, 0xFF, "Unknown Intel NetBurst Processor"},

	{"AuthenticAMD", 0x03, 0xFF, 0xFF, 0xFF, "Unknown AMD 386 Processor"},
	{"AuthenticAMD", 0x04, 0xFF, 0xFF, 0xFF, "Unknown AMD 486 Processor"},
	{"AuthenticAMD", 0x05, 0xFF, 0xFF, 0xFF, "Unknown AMD K-6 Processor"},
	{"AuthenticAMD", 0x06, 0xFF, 0xFF, 0xFF, "Unknown AMD Athlon Processor"},


	/** Intel NetBurst ****************************************************************************/

	{"GenuineIntel", 0x0F, 0x00, 0x07, 0x08, /*false,*/ "Intel Pentium 4 'Willamette' (B2)"},
//	{"GenuineIntel", 0x0F, 0x00, 0x09, 0x0B?,/*false,*/ "Intel Xeon 4 'Foster?' (??)"},	// In Intel docs as Xeon < F09
	{"GenuineIntel", 0x0F, 0x00, 0x0A, 0x08, /*false,*/ "Intel Pentium 4 'Willamette' (C1)"},
	{"GenuineIntel", 0x0F, 0x00, 0x0A, 0x0E, /*false,*/ "Intel Xeon 4 'Foster' (C1)"},

	{"GenuineIntel", 0x0F, 0x01, 0x01, 0x0B, /*false,*/ "Intel Xeon 4 MP 'Foster' (C0)"},
	{"GenuineIntel", 0x0F, 0x01, 0x02, 0x08, /*false,*/ "Intel Pentium 4 'Willamette' (D0)"},
	{"GenuineIntel", 0x0F, 0x01, 0x02, 0x0E, /*false,*/ "Intel Xeon 4 'Foster' (D0)"},
	{"GenuineIntel", 0x0F, 0x01, 0x03, 0x09, /*false,*/ "Intel Pentium 4 'Willamette' (E0)"},
	{"GenuineIntel", 0x0F, 0x01, 0x03, 0x0A, /*false,*/ "Intel Celeron 4 'Willamette' (E0)"},

	{"GenuineIntel", 0x0F, 0x02, 0x02, 0x0C, /*false,*/ "Intel Xeon 4 MP 'Gallatin' (A0)"},
	{"GenuineIntel", 0x0F, 0x02, 0x04, 0x08, /*false,*/ "Intel Celeron 4 Mobile (B0)"},
	{"GenuineIntel", 0x0F, 0x02, 0x04, 0x09, /*false,*/ "Intel Pentium 4 'Northwood' (B0)"},
	{"GenuineIntel", 0x0F, 0x02, 0x04, 0x0B, /*false,*/ "Intel Xeon 4 'Prestonia' (B0)"},
	{"GenuineIntel", 0x0F, 0x02, 0x04, 0x0E, /*false,*/ "Intel Pentium 4 Mobile (B0)"},
	{"GenuineIntel", 0x0F, 0x02, 0x04, 0x0F, /*false,*/ "Intel Pentium 4 Mobile (B0 Sample)"},
	{"GenuineIntel", 0x0F, 0x02, 0x07, 0x09, /*false,*/ "Intel Pentium 4 'Northwood' (C1)"},
	{"GenuineIntel", 0x0F, 0x02, 0x07, 0x0A, /*false,*/ "Intel Celeron 4 'Northwood' (C1)"},
	{"GenuineIntel", 0x0F, 0x02, 0x07, 0x0B, /*false,*/ "Intel Xeon 4 'Prestonia' (C1)"},
//	{"GenuineIntel", 0x0F, 0x02, 0x07, 0x0E, /*false,*/ "Intel Pentium 4 Mobile (C1)"},
	{"GenuineIntel", 0x0F, 0x02, 0x07, 0x0F, /*false,*/ "Intel Celeron 4 Mobile (C1)"},

//	{"GenuineIntel",F?,3?, ?, ?, "Intel Pentium 4 'Prescott' (??)"},	//.09
//	{"GenuineIntel",F?,3?, ?, ?, "Intel Xeon 4 'Nocona' (??)"},			//.09

//	{"GenuineIntel",F?,4?, ?, ?, "Intel Pentium 4 'Tyler' (??)"},



//	{"GenuineIntel", ?,?, ?, ?, "Intel Mobillium 'Banias' (??)"},
//	{"GenuineIntel", ?,?, ?, ?, "Intel Mobillium 'Dothan' (??)"},
//	Intel's truly mobile processor. Intel says this is a completly new processor. Sources say it's just
//	a rework of the PIII or P4. I don't believe this, beacause it has SSE2 (not in PIII) and is faster
//	than the P4. I guess they just shortened the enormous 20 stage P4 pipeline a bit, which is too long
//	to be used effecivly. More backup is provided for the fact that the Pentium 5 will be based upon
//	this chip. And another thing many sources will tell you this chip will be called 'Intel Banias',
//	didn't Intel call the Pentium III, Intel Katmai for a very long time. With this in mind it wouldn't
//	even surprise me if this processor is goin to be called Pentium 5. Sorry but I have to go one now
//	I'm brainstorming. The mobile part of it might not even be used for mobile computers, but for
//	desktops and servers as well, because cooling has become almost impossible today. If speeds are
//	going to get even higher the next couple of years, the processor cores will just melt. Because
//	AMD's processors get even hotter and isn't working on a similar project Intel might even regain
//	it's market monopoly (wheter this is good or bad, I don't know?)

//	{"GenuineIntel",F?,?, ?, ?, "Intel Pentium 5 'Nehalem' (??)"},
//	This is just a rumor. It's supposed to come out in 2006, run at 6Ghz and have a bus speed of
//	1.5Ghz. It COULD be using the Intel Banias core. Suggesting the Banias is a Pentium 5 and that it
//	IS completely new. IF you read the note above this could also be the Pentium 6 or something.

	/** Intel Itanium *******************************************************************************/

//	{"GenuineIntel", 7, 6, 4, 0, "Intel Itanium 'Merced' (C0)"},				//0007000604
//	{"GenuineIntel", 7, 7, 4, 0, "Intel Itanium 'Merced' (C1)"},				//0007000704
//	{"GenuineIntel", 7, 7, 4, 0, "Intel Itanium 'Merced' (C2)"},				//0007000804

//	{"GenuineIntel", 0x10, 0, ?, 0, "Intel Itanium 2 'McKinley' (B3)"},			//001F000704

//	{"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2 'Madison' (??)"},
//	{"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2 'Deerfield' (??)"},
//	{"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2? 'Montecito' (??)"}
//	{"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2? 'Shavano' (??)"},

	/** AMD *****************************************************************************************/
	
	{"AuthenticAMD", 4, 1, 2, 0, "AMD 486DX"},
	{"AuthenticAMD", 4, 3, 2, 0, "AMD 486DX/2"},	//DX4 (WT2x) toooo && DXL2 / DX4NV8T
	{"AuthenticAMD", 4, 3, 4, 0, "AMD 486DX/2"},	//DX4 (WT2x) toooo && DXL2 / DX4SV8B
//	{"AuthenticAMD", 4, 7, ?, 0, "AMD 486DX/2-WB"},	//DX4 (WB2x)
	{"AuthenticAMD", 4, 7, 4, 0, "AMD SV8B (WT)"},
//	{"AuthenticAMD", 4, 8, ?, 0, "AMD 486DX/4"},		//5x86 toooo
	{"AuthenticAMD", 4, 8, 4, 0, "AMD 486DX/4"},	//3xWT
	{"AuthenticAMD", 4, 9, 4, 0, "AMD 486DX/4-WB"},	//3xWB
	{"AuthenticAMD", 4, 0xE, 4, 0, "AMD Am5x86-WT"},		//AMD Enhanced 486
	{"AuthenticAMD", 4, 0xF, 4, 0, "AMD Am5x86-WB (4)"},	//AMD Enhanced 486
	
	//cores: 5.0 / 5.0 (MMX) / 5.1 / 5.2
	{"AuthenticAMD", 5, 0, 0, 0, "AMD K5 SSA/5 (E)"},		//??? Stepping Name
	{"AuthenticAMD", 5, 0, 1, 0, "AMD K5 SSA/5 (F)"},		//??? Stepping Name
//	{"AuthenticAMD", 5, 0, ?, 0, "AMD K5 SSA/5 (?)"},		//??? Stepping Name
//	{"AuthenticAMD", 5, 1, ?, 0, "AMD K5 5k86 Model 1 (?)"},		//??? Stepping Name
	{"AuthenticAMD", 5, 1, 1, 0, "AMD K5 5k86 Model 1 (?)"},		//??? Stepping Name
	{"AuthenticAMD", 5, 1, 2, 0, "AMD K5 5k86 Model 1 (?)"},		//??? Stepping Name
	{"AuthenticAMD", 5, 1, 4, 0, "AMD K5 5k86 Model 1 (?)"},		//CLKMUL=1.5
//	{"AuthenticAMD", 5, 2, ?, 0, "AMD K5 5k86 Model 1 (?)"},		//??? Stepping Name
	{"AuthenticAMD", 5, 2, 4, 0, "AMD K5 5k86 Model 2 (?)"},		//CLKMUL=1.75
//	{"AuthenticAMD", 5, 3, ?, 0, "AMD K5 5k86 Model 3 (?)"},		//??? Stepping Name (NOT RELEASED)
	{"AuthenticAMD", 5, 3, 4, 0, "AMD K5 5k86 Model 1 (?)"},		//CLKMUL=2.0
	
	
	//Missing: MobileS / K6-2+ n/ K6-III+
	{"AuthenticAMD", 5, 6, 1, 0, "AMD-K6 Model 6 (B)"},
	{"AuthenticAMD", 5, 6, 2, 0, "AMD-K6 Model 6 (C)"},
	{"AuthenticAMD", 5, 7, 0, 0, "AMD-K6 Model 7 'Little Foot' (A)"},
	{"AuthenticAMD", 5, 8, 0, 0, "AMD-K6-2 Model 8 'Chomper' (A0)"},	//doesnt CXT stnd fr Chomber XT
//	{"AuthenticAMD", 5, 8, 8, 0, "AMD-K6-2 Model 8 'Chomper' (AC)"},	//In Recognition < CXT
	{"AuthenticAMD", 5, 8, 0xC, 0, "AMD-K6-2 Model 8 'Chomper' (AC)"},	//CXT Core (Write COmbining) I believe
	{"AuthenticAMD", 5, 9, 1, 0, "AMD-K6-III 'Sharptooth' Model 9 (B)"},
//	{"AuthenticAMD", 5, 0xD, ?, 0, "AMD-K6-2+ / K6-III+ 'Sharptooth' (?)"}, //Not doced by AMD (3DNow!+)

//*	{"AuthenticAMD", 6, 0, ?, 0, "AMD K7 [ES]"},		//UNDOCUMENTED!?!
	
	{"AuthenticAMD", 0x06, 1, 1, 0, "AMD Athlon 'Argon' Model 1 (C1)"},
	{"AuthenticAMD", 0x06, 1, 2, 0, "AMD Athlon 'Argon' Model 1 (C2)"},
	{"AuthenticAMD", 0x06, 2, 1, 0, "AMD Athlon 'Pluto' Model 2 (A1)"},
	{"AuthenticAMD", 0x06, 2, 2, 0, "AMD Athlon 'Pluto' Model 2 (A2)"},
	{"AuthenticAMD", 0x06, 3, 0, 0, "AMD Duron 'Spitfire' Model 3 (A0)"},
	{"AuthenticAMD", 0x06, 3, 1, 0, "AMD Duron 'Spitfire' Model 3 (A2)"},	/* CPUIDERR fixed*/
	{"AuthenticAMD", 0x06, 4, 2, 0, "AMD Athlon 'Thunderbird' Model 4 (A4/A5/A6/A7)"},
	{"AuthenticAMD", 0x06, 4, 4, 0, "AMD Athlon 'Thunderbird' Model 4 (A9)"},
//	{"AuthenticAMD", 0x06, 4, 4, 0, "AMD Athlon 'Thunderbird' Model 4 (B0)"},	//??Grzegorz
//	{"AuthenticAMD", 0x06,5?, ?, 0, "AMD Athlon Ultra 'Mustang' Model 5? (??)"},			/* CANCELED */
	{"AuthenticAMD", 0x06, 6, 0, 0, "AMD Athlon XP/MP 'Palomino' Model 6 (A0)"},
	{"AuthenticAMD", 0x06, 6, 0, 2, "AMD Athlon 4 Mobile 'Palomino' Model 6 (A0)"},
	{"AuthenticAMD", 0x06, 6, 1, 0, "AMD Athlon XP/MP 'Palomino' Model 6 (A2)"},
	{"AuthenticAMD", 0x06, 6, 1, 2, "AMD Athlon 4 Mobile 'Palomino' Model 6 (A2)"},
	{"AuthenticAMD", 0x06, 6, 2, 0, "AMD Athlon XP 'Palomino' Model 6 (A5)"},
	{"AuthenticAMD", 0x06, 6, 2, 1, "AMD Athlon MP 'Palomino' Model 6 (A5)"},
	{"AuthenticAMD", 0x06, 6, 2, 2, "AMD Athlon 4 Mobile 'Palomino' Model 6 (A5)"},
	//DURON and Mobile DUREN????? (IN AMD AP-NOTE)
	{"AuthenticAMD", 0x06, 7, 0, 0, "AMD Duron 'Morgan' Model 7 (A0)"},
	{"AuthenticAMD", 0x06, 7, 0, 2, "AMD Duron Mobile 'Morgan' Model 7 (A0)"},
	{"AuthenticAMD", 0x06, 7, 1, 0, "AMD Duron 'Morgan' Model 7 (A1)"},
	{"AuthenticAMD", 0x06, 7, 1, 2, "AMD Duron Mobile 'Morgan' Model 7 (A1)"},
	{"AuthenticAMD", 0x06, 8, 0, 0, "AMD Athlon XP 'Thoroughbred' Model 8 (A0)"},
	{"AuthenticAMD", 0x06, 8, 0, 1, "AMD Athlon MP 'Thoroughbred' Model 8 (A0)"},
	{"AuthenticAMD", 0x06, 8, 0, 2, "AMD Athlon XP Mobile 'Thoroughbred' Model 8 (A0)"},
//	{"AuthenticAMD", 0x06, 8,1?, 0, "AMD Athlon XP 'Thoroughbred' Model 8 (B0?)"},	/* B Model = better
//	{"AuthenticAMD", 0x06,9?, ?, 0, "AMD Duron 'Appaloosa' Model 9? (??)"},	/*Could get(IS)canceled*/
//	{"AuthenticAMD", 0x06,A?, ?, 0, "AMD Athlon XP 'Barton' Model 10? (??)"},
//	{"AuthenticAMD", 0x06,A?, ?, 1, "AMD Athlon MP 'Barton' Model 10? (??)"},

//	{"AuthenticAMD", ?, ?, ?, ?, "AMD Athlon XP64 / Hammer 'Clawhammer' (??)"},
//	{"AuthenticAMD", ?, ?, ?, ?, "AMD Athlon XP64 / Hammer 'San Diego' (??)"},
//	{"AuthenticAMD", ?, ?, ?, ?, "AMD Athlon XP64 / Hammer Mobile 'Odessa' (??)"},
//	{"AuthenticAMD", ?, ?, ?, ?, "AMD Opteron 'Sledgehammer' (??)"},
//	{"AuthenticAMD", ?, ?, ?, ?, "AMD Opteron 'Athens' (??)"},

	/************************************************************************************************/

	{"CentaurHauls", 0x05, 0x04, 0x00, 0x00, "IDT WinChip C6 (A)"},
	{"CentaurHauls", 0x05, 0x04, 0x01, 0x00, "IDT WinChip C6 (B)"},	//WinChip 98 ???

//	{"CentaurHauls", 0x05, 0x08, 0x01, 0x00, "IDT WinChip 2"},
	{"CentaurHauls", 0x05, 0x08, 0x05, 0x00, "IDT WinChip 2"},
	{"CentaurHauls", 0x05, 0x08, 0x07, 0x00, "IDT WinChip 2A (7)"},
	{"CentaurHauls", 0x05, 0x08, 0x08, 0x00, "IDT WinChip 2A (8)"},
	{"CentaurHauls", 0x05, 0x08, 0x09, 0x00, "IDT WinChip 2A (9)"},
	{"CentaurHauls", 0x05, 0x08, 0x0A, 0x00, "IDT WinChip 2B (A)"},
	{"CentaurHauls", 0x05, 0x08, 0x0B, 0x00, "IDT WinChip 2B (B)"},
	{"CentaurHauls", 0x05, 0x08, 0x0C, 0x00, "IDT WinChip 2B (C)"},
	{"CentaurHauls", 0x05, 0x08, 0x0D, 0x00, "IDT WinChip 2B (D)"},
	{"CentaurHauls", 0x05, 0x08, 0x0E, 0x00, "IDT WinChip 2B (E)"},
	{"CentaurHauls", 0x05, 0x08, 0x0F, 0x00, "IDT WinChip 2B (F)"},

	{"CentaurHauls", 0x05, 0x09, 0x00, 0x00, "IDT WinChip 3 (0)"},
	{"CentaurHauls", 0x05, 0x09, 0x01, 0x00, "IDT WinChip 3 (1)"},
	{"CentaurHauls", 0x05, 0x09, 0x02, 0x00, "IDT WinChip 3 (2)"},
	{"CentaurHauls", 0x05, 0x09, 0x03, 0x00, "IDT WinChip 3 (3)"},
	{"CentaurHauls", 0x05, 0x09, 0x04, 0x00, "IDT WinChip 3 (4)"},
	{"CentaurHauls", 0x05, 0x09, 0x05, 0x00, "IDT WinChip 3 (5)"},
	{"CentaurHauls", 0x05, 0x09, 0x06, 0x00, "IDT WinChip 3 (6)"},
	{"CentaurHauls", 0x05, 0x09, 0x07, 0x00, "IDT WinChip 3 (7)"},
	{"CentaurHauls", 0x05, 0x09, 0x08, 0x00, "IDT WinChip 3 (8)"},
	{"CentaurHauls", 0x05, 0x09, 0x09, 0x00, "IDT WinChip 3 (9)"},
	{"CentaurHauls", 0x05, 0x09, 0x0A, 0x00, "IDT WinChip 3 (A)"},
	{"CentaurHauls", 0x05, 0x09, 0x0B, 0x00, "IDT WinChip 3 (B)"},
	{"CentaurHauls", 0x05, 0x09, 0x0C, 0x00, "IDT WinChip 3 (C)"},
	{"CentaurHauls", 0x05, 0x09, 0x0D, 0x00, "IDT WinChip 3 (D)"},
	{"CentaurHauls", 0x05, 0x09, 0x0E, 0x00, "IDT WinChip 3 (E)"},
	{"CentaurHauls", 0x05, 0x09, 0x0F, 0x00, "IDT WinChip 3 (F)"},

	//VIA Cyrix III is @ CyrixInstead dummies
//	{"CentaurHauls", 6, 6, ?, 0, "VIA C3 'Samuel 1'"},	//???
//	{"CentaurHauls", 6, 7, ?, 0, "VIA C3 'Samuel 2'"}, //0-7
//	{"CentaurHauls", 6, 7, ?, 0, "VIA C3 'Ezra'"},		//8-F
//	{"CentaurHauls", 6, 8, ?, 0, "VIA C3 'Ezra-T'"},	//0-?
	//The VIA Eden has a North and SOuth bridge bundled (ID???)


//	{"CentaurHauls", 6, 0xA, ?, 0, "IDT WinChip 4"},		//PROBABLY DOESN'T EXIST!

	/***********************************************************************************************/

	//My sources are unreliable at best for these suckers, so I list them all
	//Also I belive the names aren't entire ly correct, confused codename/ actualt name and extensions

	{"CyrixInstead", 0, 0, 5, 0, "Cyrix M5 Cx486S/D"},	//No CPUID I believe (is family correct?)
	{"CyrixInstead", 0, 0, 6, 0, "Cyrix M6 Cx486DX"},	//...
	{"CyrixInstead", 0, 0, 7, 0, "Cyrix M7 Cx486DX2"},	//...
	{"CyrixInstead", 0, 0, 8, 0, "Cyrix M8 Cx486DX4"},	
	//...

	{"CyrixInstead", 4, 1, 0, 0, "Cyrix 4x86SLC"},
//	{"CyrixInstead", 4, 2, ?, 0, "Cyrix 5x86"},
	{"CyrixInstead", 4, 2, 9, 0, "Cyrix 5x86 (Rev 1-)"},	//Bus *2
	{"CyrixInstead", 4, 2, 0xB, 0, "Cyrix 5x86 (Rev 1-)"},	//Bus *2
	{"CyrixInstead", 4, 2, 0xD, 0, "Cyrix 5x86 (Rev 1-)"},	//Bus *3
	{"CyrixInstead", 4, 2, 0xF, 0, "Cyrix 5x86 (Rev 1-)"},	//Bus *3
//	{"CyrixInstead", 4, 4, ?, 0, "Cyrix MediaGX"},
	{"CyrixInstead", 4, 9, 0, 0, "Cyrix 5x86 (Rev 2+)"},
//	{"CyrixInstead", 4, 9, ?, 0, "Cyrix 5x86"},

	
//	IBM ID=15h Top (65 KB JPG) and Bottom (104 KB JPG)
//	IBM ID=17h Top (71 KB JPG) and Bottom (110 KB JPG)
//	Cyrix ID=17h Top (63 KB JPG) and Bottom (102 KB JPG)
//	IBM ID=22h Top (82 KB JPG) and Bottom (99 KB JPG) 
//	{"CyrixInstead", 5, 0, ?, 0, "Cyrix M1 (6x86)"},	//Grzegorz
	{"CyrixInstead", 5, 2, 0, 0, "Cyrix M1 (6x86)"},	//Early Models (L / non-L versions???? (LV too))
//	{"CyrixInstead", 5, 2, ?, 0, "Cyrix M1 (6x86)"},	//Early Models (L / non-L versions???? (LV too))
	{"CyrixInstead", 5, 3, 0, 0, "Cyrix M1 (6x86)"},	//1.0x Bus Ratio
	{"CyrixInstead", 5, 3, 1, 0, "Cyrix M1 (6x86)"},	//2.0x Bus Ratio
	{"CyrixInstead", 5, 3, 2, 0, "Cyrix M1 (6x86)"},	//1.0x Bus Ratio
	{"CyrixInstead", 5, 3, 3, 0, "Cyrix M1 (6x86)"},	//2.0x Bus Ratio
	{"CyrixInstead", 5, 3, 4, 0, "Cyrix M1 (6x86)"},	//3.0x Bus Ratio
	{"CyrixInstead", 5, 3, 5, 0, "Cyrix M1 (6x86)"},	//4.0x Bus Ratio
	{"CyrixInstead", 5, 3, 6, 0, "Cyrix M1 (6x86)"},	//3.0x Bus Ratio
	{"CyrixInstead", 5, 3, 7, 0, "Cyrix M1 (6x86)"},	//4.0x Bus Ratio
//	{"CyrixInstead", 5, 4, ?, 0, "Cyrix MediaGX MMX"},


//	ID=02h Top (73 KB JPG) and Bottom (100 KB JPG)
//	ID=04h Top (79 KB JPG) and Bottom (106 KB JPG)
//	ID=08h Top (66 KB JPG) and Bottom (101 KB JPG) 
//	ID=53 07
	{"CyrixInstead", 6, 0, 0, 0, "Cyrix MII (6x86MX)"},
//	{"CyrixInstead", 6, 0, ?, 0, "Cyrix MII (6x86MX)"},

	//These guys are actualy a Cyrix M2 with minor enhancemets (3DNow! / better FPU), but who cares,
	//they were never taken into procuvtion. Although VIA C3 probalby stands for Cyrix M3 and not,
	//Centaur WinChip 3
	{"CyrixInstead", 6, 5, 1, 0, "VIA Cyrix III 'Joshua'"},	//2.0x Bus Ratio
	{"CyrixInstead", 6, 5, 2, 0, "VIA Cyrix III 'Joshua'"},	//2.5x Bus Ratio
	{"CyrixInstead", 6, 5, 3, 0, "VIA Cyrix III 'Joshua'"},	//3.0x Bus Ratio
	{"CyrixInstead", 6, 5, 4, 0, "VIA Cyrix III 'Joshua'"},	//3.5x Bus Ratio
	{"CyrixInstead", 6, 5, 5, 0, "VIA Cyrix III 'Joshua'"},	//4.0x Bus Ratio
	{"CyrixInstead", 6, 5, 9, 0, "VIA Cyrix III 'Joshua'"},	//2.0x Bus Ratio
	{"CyrixInstead", 6, 5, 0xA, 0, "VIA Cyrix III 'Joshua'"},	//2.5x Bus Ratio
	{"CyrixInstead", 6, 5, 0xB, 0, "VIA Cyrix III 'Joshua'"},	//3.0x Bus Ratio
	{"CyrixInstead", 6, 5, 0xC, 0, "VIA Cyrix III 'Joshua'"},	//4.5x Bus Ratio
	{"CyrixInstead", 6, 5, 0xD, 0, "VIA Cyrix III 'Joshua'"},	//4.0x Bus Ratio

	//Other names heard: Cyrix M-III 'Mojave'
	// Cayenne / Gobi / Jalapeno
	// Cayenne, then Gobi, then Joshua

	//THE VIA Series!!!!!

	/************************************************************************************************/
	
//	{"UMC UMC UMC ", 0x04, 0x01, 0x??, 0x00, "UMC U5SD (?)"},
//	{"UMC UMC UMC ", 0x04, 0x02, 0x??, 0x00, "UMC U5S (?)"},
	{"UMC UMC UMC ", 0x04, 0x02, 0x03, 0x00, "UMC U5S (3?)"},
//	{"UMC UMC UMC ", 0x04, 0x03, 0x??, 0x00, "UMC U486DX2 (?)"},
//	{"UMC UMC UMC ", 0x04, 0x05, 0x??, 0x00, "UMC U486SX2 (?)"},

//	TM3200 (formerly known as TM3120)
//	TM5400 and TM5600
//	TM5500 and TM5800 
//	{"GenuineTMx86", 5, 4, ?, ?, "Transmeta Crusoe"},

//	I'm not sure about the CNs
//	{"RiseRiseRise", 5, 0, ?, 0, "Rise mP6 iDragon '6401?' (Model 0)"},	//0.25
//	{"RiseRiseRise", 5, 0, 4, 0, "Rise mP6 iDragon '6401?' (Model 0)"},	//0.25
//	{"RiseRiseRise", 5, 1, ?, 0, "Rise mP6 iDragon 'Kirin?' (Model 1)"},
//	{"RiseRiseRise", 5, 2, ?, 0, "Rise mP6 iDragon 'Lynx?' (Model 2)"},	//0.18
//	{"RiseRiseRise", 5, 8, ?, 0, "Rise mP6 iDragon II"},
//	{"RiseRiseRise", 5, 9, ?, 0, "Rise mP6 iDragon II"},

	//Nx586 / Nx586FP
//	{"NexGenDriven", 0x05, 0x00, 0x??, 0x00, ?,  ???, "NexGen Nx586"},
//	{"NexGenDriven", 0x05, 0x00, 0x4, 0x00, ?,  ???, "NexGen Nx586"},	//120MHz / 100
//	{"NexGenDriven", 0x05, 0x00, 0x6, 0x00, ?,  ???, "NexGen Nx586"},	//133MHz / 120 (E2/C0)
//	{"NexGenDriven", 0x05, 0x??, 0x??, 0x00, ?,  ???, "NexGen Nx686"}.		//--> AuthenticAMD = K6

//	NONEXISTINGCPUS (VMWARE and such...)
//	{"ThinkTrinary", F, F, F, 0, "Trinary Emulator"}
};

struct {
	char* VendorID;
	char* VendorName;
} VendorList[] =
{
	{"GenuineIntel", "Intel Corporation"},
	{"AuthenticAMD", "AMD (Advanced Micro Devices)"},
	{"AMD ISBETTER", "AMD (Advanced Micro Devices)"},	//1994 Engineering Samples
	{"CyrixInstead", "Cyrix Corporation / VIA (Value Internet Architecture) Incorporated"},
	{"CentaurHauls", "Centaur Technologies / VIA (Value Internet Architecture) Incorporated"},
	{"GenuineTMx86", "Transmeta Corporation"},
	{"RiseRiseRise", "Rise"},	//"RISERISERISE"
	{"Geode by NSC", "National Semiconductor Corporation"}, //Need info
	{"UMC UMC UMC ", "United Microelectronics Corporation"},	//" UMC UMC UMC"
	{"NexGenDriven", "NexGen Incorporated / AMD (Advanced Micro Devices)"},
	{"ThinkTrinary", "Trinary Technologies"}
};





struct BRANDLIST {
	char* VerdorID;
	int BrandID;
	char* Description;
};

BRANDLIST BrandIDList[] = 
{
	{"GenuineIntel", 0x00, "Not Supported"}, //Better remove this one, it's stupid
	{"GenuineIntel", 0x01, "Intel Celeron"},
	{"GenuineIntel", 0x02, "Intel Pentium III"},
	{"GenuineIntel", 0x03, "Intel Pentium III Xeon"}, //Intel Celeron for 6B1 (and 6B4 I'd guess???)
	{"GenuineIntel", 0x04, "Intel Pentium III"},
	{"GenuineIntel", 0x05, "?????????????????????"},
	{"GenuineIntel", 0x06, "Intel Pentium III-M Mobile"},	//Namechange???
	{"GenuineIntel", 0x07, "Intel Celeron Mobile"},
	{"GenuineIntel", 0x08, "Intel Pentium 4"},	//Intel Genuine (Celeron 4 Mobile???) if >= F13 (Why??? I don't get it)
	{"GenuineIntel", 0x09, "Intel Pentium 4"},
	{"GenuineIntel", 0x0A, "Intel Celeron"},
	{"GenuineIntel", 0x0B, "Intel Xeon"},	// Intel Xeon MP if < F13 
	{"GenuineIntel", 0x0C, "Intel Xeon MP"},
	{"GenuineIntel", 0x0D, "????????????????????????"},
	{"GenuineIntel", 0x0E, "Intel Pentium 4-M Mobile"}, //Intel Xeon if < F13
	{"GenuineIntel", 0x0F, "Intel Celeron Mobile"}, //(pentium 4 mobile SAMPLES accoridng to Sandpile)
};

struct {
	int Frequency;
	int	Model;
} AMDFrequencyList[] =
{
	{1300, 1500},
	{1333, 1500},
	{1400, 1600},
	{1467, 1700},
	{1500, 1800},
	{1533, 1800},
	{1600, 1900},
	{1666, 2000},
	{1733, 2100},
	{1800, 2200},
	{2000, 2400},
	{2133, 2600}
};


//When this identification code is executed, we are already in 32-bit Protected Mode. So the basic
//80x86 test are not necessary (and imposible), beacuse the OS did that for us before switching into
//Protected Mode. Doing these test in Protected Mode will hurt system integrity. It includes changing
//some PM Flags and even reseting the processor. Not a good idea!

bool SupportsCPUID(void)
{
	unsigned int OldFlags, NewFlags;
	
	__asm
	{	pushfd				//Read the flags
		pop eax
		mov OldFlags, eax
		xor eax, 0x200000	//Invert the CPUID bit
		push eax			//Save the flags
		popfd
		pushfd				//Read the flags
		pop eax
		mov NewFlags, eax
		push eax			//Restore the flags
		popfd
	}

	if (OldFlags != NewFlags) return true;
	return false;

	//Need to enable CPUID on Cyrix
	//Need to used #UD to detect NexGen 5x86
	//Alternative RESET/BIOS detection 386s and some 486s
}

union CPUIDData {unsigned int d; unsigned short w[2]; unsigned char b[4];};

void CPUID(unsigned int processor, unsigned int function, CPUIDData& A, CPUIDData& B, CPUIDData& C, CPUIDData& D)
{
	unsigned int a, b, c, d;
	
	__asm
	{	mov eax, function
		mov ecx, 0x00000000
		mov edx, 0x00000000
		mov ebx, 0x00000000
		cpuid
		mov a, eax
		mov c, ecx
		mov d, edx
		mov b, ebx
	}

	A.d = a;
	B.d = b;
	C.d = c;
	D.d = d;
}

void Identify(IdentificationStructure &IdentificationData)
{
	CPUIDData A, B, C, D;

	unsigned int HighestStandardFunction = 0;
	unsigned int HighestExtendedFunction = 0;

	CPUID(0, 0, A, B, C, D);

	HighestStandardFunction = A.d;
	memcpy(IdentificationData.Processor.VendorID+0, B.b, 4);
	memcpy(IdentificationData.Processor.VendorID+4, D.b, 4);
	memcpy(IdentificationData.Processor.VendorID+8, C.b, 4);
	memset(IdentificationData.Processor.VendorID+12, 0, 4);

	//According to an old CPU identification application, the pre-production models of the Pentium
	//Classic returned the wrong number of supported CPUID levels ( > 500h ) and no vendor string.
	if (HighestStandardFunction >= 0x500)
	{
		HighestStandardFunction = 1;
		strcpy(IdentificationData.Processor.VendorID, "GenuineIntel");
	}

	//CPUID level 1 returns the stepping and feature information. Because different vendors assign
	//different meanings to the same flags. Therefore we need to do a lot of correcting afterwards.
	if (HighestStandardFunction >= 1)
	{
		CPUID(0, 1, A, B, C, D);

		IdentificationData.Processor.Stepping			= (A.d & 0x0000000F) >> 0;
		IdentificationData.Processor.Model				= (A.d & 0x000000F0) >> 4;
		IdentificationData.Processor.Family				= (A.d & 0x00000F00) >> 8;
		IdentificationData.Processor.Type				= (A.d & 0x00003000) >> 12;
		IdentificationData.Signature.HasSerialNumber	= (A.d & 0x80000000) >> 31;

		if (IdentificationData.Processor.Model >= 0xF)
			IdentificationData.Processor.Model += (A.d & 0x000F0000) >> 16;
		if (IdentificationData.Processor.Family	>= 0xF)
			IdentificationData.Processor.Family += (A.d & 0x0FF00000) >> 20;

		IdentificationData.Instructions.FloatingPoint			= (D.d >> 0) & 1;
		IdentificationData.Features.VirtualModeExtensions		= (D.d >> 1) & 1;
		IdentificationData.Features.DebuggingExtensions			= (D.d >> 2) & 1;
		IdentificationData.Features.PageSizeExtensions			= (D.d >> 3) & 1;
		IdentificationData.Features.TimeStampCounter			= (D.d >> 4) & 1;
		IdentificationData.Features.ModelSpecificRegisters		= (D.d >> 5) & 1;
		IdentificationData.Features.PhysicalAddressExtension	= (D.d >> 6) & 1;
		IdentificationData.Features.MachineCheckException		= (D.d >> 7) & 1;
		IdentificationData.Instructions.CompareAndExchange8		= (D.d >> 8) & 1;
		IdentificationData.Features.LocalAPIC					= (D.d >> 9) & 1;
		IdentificationData.Reserved.Feature10					= (D.d >> 10) & 1;
		IdentificationData.Instructions.FastSystemCall			= (D.d >> 11) & 1;
		IdentificationData.Features.MemoryTypeRangeRegisters	= (D.d >> 12) & 1;
		IdentificationData.Features.PageGlobalEnable			= (D.d >> 13) & 1;
		IdentificationData.Features.MachineCheckArchitecture	= (D.d >> 14) & 1;
		IdentificationData.Instructions.ConditionalMove			= (D.d >> 15) & 1;
		IdentificationData.Features.PageAttributeTable			= (D.d >> 16) & 1;
		IdentificationData.Features.PageSizeExtension36			= (D.d >> 17) & 1;
		IdentificationData.Features.ProcessorSerialNumber		= (D.d >> 18) & 1;
		IdentificationData.Instructions.CacheLineFlush			= (D.d >> 19) & 1;
		IdentificationData.Reserved.Feature20					= (D.d >> 20) & 1;
		IdentificationData.Features.DebugStore					= (D.d >> 21) & 1;
		IdentificationData.Features.ACPI						= (D.d >> 22) & 1;
		IdentificationData.Instructions.MMX						= (D.d >> 23) & 1;
		IdentificationData.Instructions.FXSR					= (D.d >> 24) & 1;
		IdentificationData.Instructions.SSE						= (D.d >> 25) & 1;
		IdentificationData.Instructions.SSE2					= (D.d >> 26) & 1;
		IdentificationData.Features.SelfSnoop					= (D.d >> 27) & 1;
		IdentificationData.Features.HyperThreadingTechnology	= (D.d >> 28) & 1;
		IdentificationData.Features.ThermalMonitor				= (D.d >> 29) & 1;
		IdentificationData.Instructions.IA64					= (D.d >> 30) & 1;
		IdentificationData.Features.SignalBreakOnFERR			= (D.d >> 31) & 1; //AKA PendingBreakEnable

		IdentificationData.Reserved.Feature32					= (C.d >> 0) & 1;
		IdentificationData.Reserved.Feature33					= (C.d >> 1) & 1;
		IdentificationData.Reserved.Feature34					= (C.d >> 2) & 1;
		IdentificationData.Reserved.Feature35					= (C.d >> 3) & 1;
		IdentificationData.Reserved.Feature36					= (C.d >> 4) & 1;
		IdentificationData.Reserved.Feature37					= (C.d >> 5) & 1;
		IdentificationData.Reserved.Feature38					= (C.d >> 6) & 1;
		IdentificationData.Reserved.Feature39					= (C.d >> 7) & 1;
		IdentificationData.Reserved.Feature40					= (C.d >> 8) & 1;
		IdentificationData.Reserved.Feature41					= (C.d >> 9) & 1;
		IdentificationData.Unknown.ContextID					= (C.d >> 10) & 1;	//Context ID
		IdentificationData.Reserved.Feature43					= (C.d >> 11) & 1;
		IdentificationData.Reserved.Feature44					= (C.d >> 12) & 1;
		IdentificationData.Reserved.Feature45					= (C.d >> 13) & 1;
		IdentificationData.Reserved.Feature46					= (C.d >> 14) & 1;
		IdentificationData.Reserved.Feature47					= (C.d >> 15) & 1;
		IdentificationData.Reserved.Feature48					= (C.d >> 16) & 1;
		IdentificationData.Reserved.Feature49					= (C.d >> 17) & 1;
		IdentificationData.Reserved.Feature50					= (C.d >> 18) & 1;
		IdentificationData.Reserved.Feature51					= (C.d >> 19) & 1;
		IdentificationData.Reserved.Feature52					= (C.d >> 20) & 1;
		IdentificationData.Reserved.Feature53					= (C.d >> 21) & 1;
		IdentificationData.Reserved.Feature54					= (C.d >> 22) & 1;
		IdentificationData.Reserved.Feature55					= (C.d >> 23) & 1;
		IdentificationData.Reserved.Feature56					= (C.d >> 24) & 1;
		IdentificationData.Reserved.Feature57					= (C.d >> 25) & 1;
		IdentificationData.Reserved.Feature58					= (C.d >> 26) & 1;
		IdentificationData.Reserved.Feature59					= (C.d >> 27) & 1;
		IdentificationData.Reserved.Feature60					= (C.d >> 28) & 1;
		IdentificationData.Reserved.Feature61					= (C.d >> 29) & 1;
		IdentificationData.Reserved.Feature62					= (C.d >> 30) & 1;
		IdentificationData.Reserved.Feature63					= (C.d >> 31) & 1;

		//The Pentium Pro incorrectly reports it support the Fast System Call. We correct it using
		//Intel's official algorithm. Which (as far as I can tell) also disables it on the
		//Pentium II OverDrive. But the description below the algorith also clearly specifies this
		//only occurs on the Pentium Pro Model 1
		if (!strcmp(IdentificationData.Processor.VendorID, "GenuineIntel"))
		{	if ((A.d & 0x0FFF3FFF) < 0x00000633)
				IdentificationData.Instructions.FastSystemCall = false;
		}

		//AMD K6-SSA5: LocalAPIC (9) -> PageGlobalEnable (13)
		if (!strcmp(IdentificationData.Processor.VendorID, "AuthenticAMD"))
		{	if ((A.d & 0x00000FF0) == 0x00000500)
			{
				IdentificationData.Features.PageGlobalEnable = IdentificationData.Features.LocalAPIC;
				IdentificationData.Features.LocalAPIC = false;
			}
		}

		//Cyrix: PhysicalAddressExtension (6) -> PTE (Which I believe is PageGlobalEnable (13))
		if (!strcmp(IdentificationData.Processor.VendorID, "CyrixInstead"))
		{	IdentificationData.Features.PageGlobalEnable = IdentificationData.Features.PhysicalAddressExtension;
			IdentificationData.Features.PhysicalAddressExtension = false;
		}

		//AMD K6: Reserved (10) -> SYSTEMCALL
		if (!strcmp(IdentificationData.Processor.VendorID, "AuthenticAMD"))
		{	if ((A.d & 0x00000FF0) == 0x00000560)
			{	IdentificationData.Instructions.SYSCALL = IdentificationData.Reserved.Feature10;
				IdentificationData.Reserved.Feature10 = false;
			}
		}

		//Cyrix: Reserved (10) -> SYSTEMCALL
		if (!strcmp(IdentificationData.Processor.VendorID, "CyrixInstead"))
		{	IdentificationData.Instructions.SYSCALL = IdentificationData.Reserved.Feature10;
			IdentificationData.Reserved.Feature10 = false;
		}

		//On Cyrix Processors bit 24 means Cyrix Enhanced MMX and not FXSAVE/FXRESTORE Support.
		if (!strcmp(IdentificationData.Processor.VendorID, "CyrixInstead"))
			IdentificationData.Instructions.cMMX = (C.d >> 24) & 1;

		if (!strcmp(IdentificationData.Processor.VendorID, "GenuineIntel")
			&& IdentificationData.Features.ProcessorSerialNumber)
				IdentificationData.Signature.SerialNumber3 = A.d;

		if (!strcmp(IdentificationData.Processor.VendorID, "GenuineIntel") ||
			!strcmp(IdentificationData.Processor.VendorID, "GenuineTMx86"))
		{
			IdentificationData.Processor.BrandNumber = B.b[0];

			if (IdentificationData.Instructions.CacheLineFlush)
				IdentificationData.Unknown.CacheLineSize = B.b[1] * 8;
			if (IdentificationData.Features.HyperThreadingTechnology)
				IdentificationData.Unknown.LogicalProcessors = B.b[2];
			if (IdentificationData.Processor.Family >= 0xF)
				IdentificationData.Unknown.LocalAPICPhysicalID = B.b[3];
		}
	}

	if (HighestStandardFunction >= 2)
	{
		if (!strcmp(IdentificationData.Processor.VendorID, "GenuineIntel"))
		{
			int CacheDescriptorTables = 1;
			
			for (int CacheIterator = 0; CacheIterator < CacheDescriptorTables; CacheIterator++)
			{
				CPUID(0, 2, A, B, C, D);

				CacheDescriptorTables = A.b[0];

				if (!(A.d & 0x80000000))
				{	IdentifyIntelCache(IdentificationData, A.b[1]);
					IdentifyIntelCache(IdentificationData, A.b[2]);
					IdentifyIntelCache(IdentificationData, A.b[3]);
				}

				if (!(B.d & 0x80000000))
				{	IdentifyIntelCache(IdentificationData, B.b[0]);
					IdentifyIntelCache(IdentificationData, B.b[1]);
					IdentifyIntelCache(IdentificationData, B.b[2]);
					IdentifyIntelCache(IdentificationData, B.b[3]);
				}
				if (!(C.d & 0x80000000))
				{	IdentifyIntelCache(IdentificationData, C.b[0]);
					IdentifyIntelCache(IdentificationData, C.b[1]);
					IdentifyIntelCache(IdentificationData, C.b[2]);
					IdentifyIntelCache(IdentificationData, C.b[3]);
				}

				if (!(D.d & 0x80000000))
				{	IdentifyIntelCache(IdentificationData, D.b[0]);
					IdentifyIntelCache(IdentificationData, D.b[1]);
					IdentifyIntelCache(IdentificationData, D.b[2]);
					IdentifyIntelCache(IdentificationData, D.b[3]);
				}
			}
		}
	}

	if (HighestStandardFunction >= 3)
	{
		CPUID(0, 3, A, B, C, D);

		if (!strcmp(IdentificationData.Processor.VendorID, "GenuineIntel"))
		{
			IdentificationData.Signature.SerialNumber1 = C.d;
			IdentificationData.Signature.SerialNumber2 = D.d;
		}

		else if (!strcmp(IdentificationData.Processor.VendorID, "GenuineTMx86"))
		{
			IdentificationData.Signature.SerialNumber1 = D.d;
			IdentificationData.Signature.SerialNumber2 = C.d;
			IdentificationData.Signature.SerialNumber3 = B.d;
			IdentificationData.Signature.SerialNumber4 = A.d;
		}
	}

	CPUID(0, 0x80000000, A, B, C, D);

	if (A.d >= 0x80000001)
	{
		HighestExtendedFunction = A.d - 0x80000000;

		memcpy(IdentificationData.Processor.ExtendedVendorID+0, B.b, 4);
		memcpy(IdentificationData.Processor.ExtendedVendorID+4, D.b, 4);
		memcpy(IdentificationData.Processor.ExtendedVendorID+8, C.b, 4);
		memset(IdentificationData.Processor.ExtendedVendorID+12, 0, 4);
	}

	if (HighestExtendedFunction >= 1)
	{
		CPUID(0, 0x80000001, A, B, C, D);

		IdentificationData.Processor.ExtendedStepping	= (A.d & 0x0000000F) >> 0;
		IdentificationData.Processor.ExtendedModel		= (A.d & 0x000000F0) >> 4;
		IdentificationData.Processor.ExtendedFamily		= (A.d & 0x00000F00) >> 8;
		IdentificationData.Processor.ExtendedType		= (A.d & 0x00003000) >> 12;

		if (IdentificationData.Processor.ExtendedModel >= 0xF)
			IdentificationData.Processor.ExtendedModel	+= (A.d & 0x000F0000) >> 16;
		if (IdentificationData.Processor.ExtendedFamily	>= 0xF)
			IdentificationData.Processor.ExtendedFamily	+= (A.d & 0x0FF00000) >> 20;

		//We ignore mirrored flags
		IdentificationData.Reserved.ExtendedFeature10			= (C.d >> 10) & 1;
		IdentificationData.Instructions.SYSCALL					= (C.d >> 11) & 1;
		IdentificationData.Reserved.ExtendedFeature18			= (C.d >> 18) & 1;
		IdentificationData.Features.MultiProcessing				= (C.d >> 19) & 1;
		IdentificationData.Reserved.ExtendedFeature20			= (C.d >> 20) & 1;
		IdentificationData.Reserved.ExtendedFeature21			= (C.d >> 21) & 1;
		IdentificationData.Instructions.aMMX					= (C.d >> 22) & 1;
		IdentificationData.Reserved.ExtendedFeature25			= (C.d >> 25) & 1;
		IdentificationData.Reserved.ExtendedFeature26			= (C.d >> 26) & 1;
		IdentificationData.Reserved.ExtendedFeature27			= (C.d >> 27) & 1;
		IdentificationData.Reserved.ExtendedFeature28			= (C.d >> 28) & 1;
		IdentificationData.Unknown.LongMode						= (C.d >> 29) & 1;
		IdentificationData.Instructions.ThreeDNowExtensions		= (C.d >> 30) & 1;
		IdentificationData.Instructions.ThreeDNow				= (C.d >> 31) & 1;


		/* WE OVERWITEFLAGS! */
		/* Transmeta CPUs / AMD pre K7 CPUs and the FCMOV Feature ! */
		/* K6 SYSCALL Replacement */
	}

	if (HighestExtendedFunction >= 2)
	{
		CPUID(0, 0x80000002, A, B, C, D);

		memcpy(IdentificationData.Processor.BrandString+0, A.b, 4);
		memcpy(IdentificationData.Processor.BrandString+4, B.b, 4);
		memcpy(IdentificationData.Processor.BrandString+8, C.b, 4);
		memcpy(IdentificationData.Processor.BrandString+12, D.b, 4);
	}
	
	if (HighestExtendedFunction >= 3)
	{
		CPUID(0, 0x80000003, A, B, C, D);

		memcpy(IdentificationData.Processor.BrandString+16, A.b, 4);
		memcpy(IdentificationData.Processor.BrandString+20, B.b, 4);
		memcpy(IdentificationData.Processor.BrandString+24, C.b, 4);
		memcpy(IdentificationData.Processor.BrandString+28, D.b, 4);
	}

	if (HighestExtendedFunction >= 4)
	{
		CPUID(0, 0x80000004, A, B, C, D);

		memcpy(IdentificationData.Processor.BrandString+32, A.b, 4);
		memcpy(IdentificationData.Processor.BrandString+36, B.b, 4);
		memcpy(IdentificationData.Processor.BrandString+40, C.b, 4);
		memcpy(IdentificationData.Processor.BrandString+44, D.b, 4);
		IdentificationData.Processor.BrandString[47] = '\0';
	}

	if (HighestExtendedFunction >= 5)
	{
		CPUID(0, 0x80000005, A, B, C, D);
	
		if (!strcmp(IdentificationData.Processor.VendorID, "AuthenticAMD"))
		{
			IdentificationData.Cache.L1CodeTLB2M.Present			= true;
			IdentificationData.Cache.L1CodeTLB2M.Entries			= A.b[0];
			IdentificationData.Cache.L1CodeTLB2M.Associativity		= A.b[1];
			IdentificationData.Cache.L1DataTLB2M.Present			= true;
			IdentificationData.Cache.L1DataTLB2M.Entries			= A.b[2];
			IdentificationData.Cache.L1DataTLB2M.Associativity		= A.b[3];

			IdentificationData.Cache.L1CodeTLB4M.Present			= true;
			IdentificationData.Cache.L1CodeTLB4M.Entries			= A.b[0] / 2;
			IdentificationData.Cache.L1CodeTLB4M.Associativity		= A.b[1];
			IdentificationData.Cache.L1DataTLB4M.Present			= true;
			IdentificationData.Cache.L1DataTLB4M.Entries			= A.b[2] / 2;
			IdentificationData.Cache.L1DataTLB4M.Associativity		= A.b[3];

			IdentificationData.Cache.L1CodeTLB4K.Present			= true;
			IdentificationData.Cache.L1CodeTLB4K.Entries			= B.b[0];
			IdentificationData.Cache.L1CodeTLB4K.Associativity		= B.b[1];
			IdentificationData.Cache.L1DataTLB4K.Present			= true;
			IdentificationData.Cache.L1DataTLB4K.Entries			= B.b[2];
			IdentificationData.Cache.L1DataTLB4K.Associativity		= B.b[3];

			IdentificationData.Cache.L1DataCache.Present			= true;
			IdentificationData.Cache.L1DataCache.LineSize			= C.b[0];
			IdentificationData.Cache.L1DataCache.LinesPerTag		= C.b[1];
			IdentificationData.Cache.L1DataCache.Associativity		= C.b[2];
			IdentificationData.Cache.L1DataCache.Size				= C.b[3];

			IdentificationData.Cache.L1CodeCache.Present			= true;
			IdentificationData.Cache.L1CodeCache.LineSize			= C.b[0];
			IdentificationData.Cache.L1CodeCache.LinesPerTag		= C.b[1];
			IdentificationData.Cache.L1CodeCache.Associativity		= C.b[2];
			IdentificationData.Cache.L1CodeCache.Size				= C.b[3];
		}

		/* Tranment support */
		/* Cyrix Support */

	}

	if (HighestExtendedFunction >= 6)
	{
		CPUID(0, 0x80000006, A, B, C, D);
		
		if (!strcmp(IdentificationData.Processor.VendorID, "AuthenticAMD"))
		{
			if (A.w[1] == 0)
			{
				IdentificationData.Cache.L2UnifiedTLB2M.Present			= true;
				IdentificationData.Cache.L2UnifiedTLB2M.Entries			= A.b[0]+(A.b[1]&0x0F)*256;
				IdentificationData.Cache.L2UnifiedTLB2M.Associativity	= AMDAssociativity(A.b[1]>>4);

				IdentificationData.Cache.L2UnifiedTLB4M.Present			= true;
				IdentificationData.Cache.L2UnifiedTLB4M.Entries			= A.b[0]+(A.b[1]&0x0F)*256;
				IdentificationData.Cache.L2UnifiedTLB4M.Associativity	= AMDAssociativity(A.b[1]>>4);
			} 
			else
			{
				IdentificationData.Cache.L2CodeTLB2M.Present			= true;
				IdentificationData.Cache.L2CodeTLB2M.Entries			= A.b[0]+(A.b[1]&0x0F)*256;
				IdentificationData.Cache.L2CodeTLB2M.Associativity		= AMDAssociativity(A.b[1]>>4);

				IdentificationData.Cache.L2CodeTLB4M.Present			= true;
				IdentificationData.Cache.L2CodeTLB4M.Entries			= A.b[0]+(A.b[1]&0x0F)*256;
				IdentificationData.Cache.L2CodeTLB4M.Associativity		= AMDAssociativity(A.b[1]>>4);

				IdentificationData.Cache.L2DataTLB2M.Present			= true;
				IdentificationData.Cache.L2DataTLB2M.Entries			= A.b[2]+(A.b[3]&0x0F)*256;
				IdentificationData.Cache.L2DataTLB2M.Associativity		= AMDAssociativity(A.b[3]>>4);

				IdentificationData.Cache.L2DataTLB4M.Present			= true;
				IdentificationData.Cache.L2DataTLB4M.Entries			= A.b[2]+(A.b[3]&0x0F)*256;
				IdentificationData.Cache.L2DataTLB4M.Associativity		= AMDAssociativity(A.b[3]>>4);
			}

			if (B.w[1] == 0)
			{
				IdentificationData.Cache.L2UnifiedTLB4K.Present			= true;
				IdentificationData.Cache.L2UnifiedTLB4K.Entries			= B.b[0]+(B.b[1]&0x0F)*256;
				IdentificationData.Cache.L2UnifiedTLB4K.Associativity	= AMDAssociativity(B.b[1]>>4);
			} 
			else
			{
				IdentificationData.Cache.L2CodeTLB4K.Present			= true;
				IdentificationData.Cache.L2CodeTLB4K.Entries			= B.b[0]+(B.b[1]&0x0F)*256;
				IdentificationData.Cache.L2CodeTLB4K.Associativity		= AMDAssociativity(B.b[1]>>4);

				IdentificationData.Cache.L2DataTLB4K.Present			= true;
				IdentificationData.Cache.L2DataTLB4K.Entries			= B.b[2]+(B.b[3]&0x0F)*256;
				IdentificationData.Cache.L2DataTLB4K.Associativity		= AMDAssociativity(B.b[3]>>4);
			}

			IdentificationData.Cache.L2UnifiedCache.LineSize			= C.b[0];
			IdentificationData.Cache.L2UnifiedCache.LinesPerTag			= C.b[1] & 0x0F;
			IdentificationData.Cache.L2UnifiedCache.Associativity		= AMDAssociativity(C.b[1]>>4);
			IdentificationData.Cache.L2UnifiedCache.Size				= C.w[1];			
		}

		/* Correct Duron Values (630 -> 64)*/
		/* Correct VIA CYRIX III Values */
	}

	if (HighestExtendedFunction >= 7)
	{
		CPUID(0, 0x80000007, A, B, C, D);
		
		if (!strcmp(IdentificationData.Processor.VendorID, "AuthenticAMD"))
		{
			IdentificationData.Features.TemperatureSensor				= (D.d >> 0) & 1;
			IdentificationData.Features.FrequencyIDControl				= (D.d >> 1) & 1;
			IdentificationData.Features.VoltageIDControl				= (D.d >> 2) & 1;
		}
	}

	if (HighestExtendedFunction >= 8)
	{
		CPUID(0, 0x80000008, A, B, C, D);
		
		if (!strcmp(IdentificationData.Processor.VendorID, "AuthenticAMD"))
		{
			IdentificationData.Unknown.MaximumPhysicalAddress			= A.b[0];
			IdentificationData.Unknown.MaximumLogicalAddress			= A.b[1];
		}
	}

	// ************ THE EXTRA NUMBER ******************** //
	// Type
	// Pentium II + III		Cache
	// Pentium III + 4		Brand ID
	// Athlon				Multi Processing / Cache

	int Extra;

	Extra = IdentificationData.Processor.Type;

	if (!strcmp(IdentificationData.Processor.VendorID, "GenuineIntel")
		&& IdentificationData.Processor.Family == 6
		&& IdentificationData.Processor.Model >= 3
		&& IdentificationData.Processor.Model <= 7)
	{
		Extra = IdentificationData.Cache.L2UnifiedCache.Size;
	}

	if (!strcmp(IdentificationData.Processor.VendorID, "GenuineIntel")
		&& IdentificationData.Processor.Family == 6
		&& IdentificationData.Processor.Model >= 8)
	{
		Extra = IdentificationData.Processor.BrandNumber;
	}

	if (!strcmp(IdentificationData.Processor.VendorID, "GenuineIntel")
		&& IdentificationData.Processor.Family == 0xF)
	{
		Extra = IdentificationData.Processor.BrandNumber;
	}

	if (!strcmp(IdentificationData.Processor.VendorID, "AuthenticAMD")
		&& IdentificationData.Processor.Family == 6)
	{
		Extra = IdentificationData.Cache.L2UnifiedCache.Size;
	}
	
	IdentifyProcessor(IdentificationData, Extra);

}

void IdentifyIntelCache(IdentificationStructure &IdentificationData, int CacheDescriptor)
{
	switch (CacheDescriptor)
	{	case 0x00: {return;
					}
		case 0x40:	{return;
					}
		case 0x01: {IdentificationData.Cache.L1CodeTLB4K.Present = true;
					IdentificationData.Cache.L1CodeTLB4K.Entries = 32;
					IdentificationData.Cache.L1CodeTLB4K.Associativity = 4;
					return;
				   }
		case 0x02: {IdentificationData.Cache.L1CodeTLB4M.Present = true;
					IdentificationData.Cache.L1CodeTLB4M.Entries = 2;
					IdentificationData.Cache.L1CodeTLB4M.Associativity = -1;
					return;
				   }
		case 0x03: {IdentificationData.Cache.L1DataTLB4K.Present = true;
					IdentificationData.Cache.L1DataTLB4K.Entries = 64;
					IdentificationData.Cache.L1DataTLB4K.Associativity = 4;
					return;
				   }
		case 0x04: {IdentificationData.Cache.L1DataTLB4M.Present = true;
					IdentificationData.Cache.L1DataTLB4M.Entries = 8;
					IdentificationData.Cache.L1DataTLB4M.Associativity = 4;
					return;
				   }
		case 0x06: {IdentificationData.Cache.L1CodeCache.Present = true;
					IdentificationData.Cache.L1CodeCache.Size = 8;
					IdentificationData.Cache.L1CodeCache.Associativity = 4;
					IdentificationData.Cache.L1CodeCache.LineSize = 32;
					IdentificationData.Cache.L1CodeCache.LinesPerTag = -1;
					return;
				   }
		case 0x08: {IdentificationData.Cache.L1CodeCache.Present = true;
					IdentificationData.Cache.L1CodeCache.Size = 16;
					IdentificationData.Cache.L1CodeCache.Associativity = 4;
					IdentificationData.Cache.L1CodeCache.LineSize = 32;
					IdentificationData.Cache.L1CodeCache.LinesPerTag = -1;
					return;
				   }
		case 0x0A: {IdentificationData.Cache.L1DataCache.Present = true;
					IdentificationData.Cache.L1DataCache.Size = 8;
					IdentificationData.Cache.L1DataCache.Associativity = 2;
					IdentificationData.Cache.L1DataCache.LineSize = 32;
					IdentificationData.Cache.L1DataCache.LinesPerTag = -1;
					return;
				   }
		case 0x0C: {IdentificationData.Cache.L1DataCache.Present = true;
					IdentificationData.Cache.L1DataCache.Size = 16;
					IdentificationData.Cache.L1DataCache.Associativity = 4;
					IdentificationData.Cache.L1DataCache.LineSize = 32;
					IdentificationData.Cache.L1DataCache.LinesPerTag = -1;
					return;
				   }
		case 0x22: {IdentificationData.Cache.L3UnifiedCache.Present = true;
					IdentificationData.Cache.L3UnifiedCache.Size = 512;
					IdentificationData.Cache.L3UnifiedCache.Associativity = 4;
					IdentificationData.Cache.L3UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L3UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x23: {IdentificationData.Cache.L3UnifiedCache.Present = true;
					IdentificationData.Cache.L3UnifiedCache.Size = 1024;
					IdentificationData.Cache.L3UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L3UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L3UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x25: {IdentificationData.Cache.L3UnifiedCache.Present = true;
					IdentificationData.Cache.L3UnifiedCache.Size = 2048;
					IdentificationData.Cache.L3UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L3UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L3UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x29: {IdentificationData.Cache.L3UnifiedCache.Present = true;
					IdentificationData.Cache.L3UnifiedCache.Size = 4096;
					IdentificationData.Cache.L3UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L3UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L3UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x39: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 128;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 4;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x3B: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 128;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 2;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x3C: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 256;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 4;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x41: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 128;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 4;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x42: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 256;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 4;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x43: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 512;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 4;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x44: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 1024;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 4;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x45: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 2048;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 4;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x50: {IdentificationData.Cache.L1CodeTLB4K.Present = true;
					IdentificationData.Cache.L1CodeTLB4K.Entries = 64;
					IdentificationData.Cache.L1CodeTLB4K.Associativity = -1;
					IdentificationData.Cache.L1CodeTLB2M.Present = true;
					IdentificationData.Cache.L1CodeTLB2M.Entries = 64;
					IdentificationData.Cache.L1CodeTLB2M.Associativity = -1;
					IdentificationData.Cache.L1CodeTLB4M.Present = true;
					IdentificationData.Cache.L1CodeTLB4M.Entries = 64;
					IdentificationData.Cache.L1CodeTLB4M.Associativity = -1;
					return;
				   }
		case 0x51: {IdentificationData.Cache.L1CodeTLB4K.Present = true;
					IdentificationData.Cache.L1CodeTLB4K.Entries = 128;
					IdentificationData.Cache.L1CodeTLB4K.Associativity = -1;
					IdentificationData.Cache.L1CodeTLB2M.Present = true;
					IdentificationData.Cache.L1CodeTLB2M.Entries = 128;
					IdentificationData.Cache.L1CodeTLB2M.Associativity = -1;
					IdentificationData.Cache.L1CodeTLB4M.Present = true;
					IdentificationData.Cache.L1CodeTLB4M.Entries = 128;
					IdentificationData.Cache.L1CodeTLB4M.Associativity = -1;
					return;
				   }
		case 0x52: {IdentificationData.Cache.L1CodeTLB4K.Present = true;
					IdentificationData.Cache.L1CodeTLB4K.Entries = 256;
					IdentificationData.Cache.L1CodeTLB4K.Associativity = -1;
					IdentificationData.Cache.L1CodeTLB2M.Present = true;
					IdentificationData.Cache.L1CodeTLB2M.Entries = 256;
					IdentificationData.Cache.L1CodeTLB2M.Associativity = -1;
					IdentificationData.Cache.L1CodeTLB4M.Present = true;
					IdentificationData.Cache.L1CodeTLB4M.Entries = 256;
					IdentificationData.Cache.L1CodeTLB4M.Associativity = -1;
					return;
				   }
		case 0x5B: {IdentificationData.Cache.L1DataTLB4K.Present = true;
					IdentificationData.Cache.L1DataTLB4K.Entries = 64;
					IdentificationData.Cache.L1DataTLB4K.Associativity = -1;
					IdentificationData.Cache.L1DataTLB4M.Present = true;
					IdentificationData.Cache.L1DataTLB4M.Entries = 64;
					IdentificationData.Cache.L1DataTLB4M.Associativity = -1;
					return;
				   }
		case 0x5C: {IdentificationData.Cache.L1DataTLB4K.Present = true;
					IdentificationData.Cache.L1DataTLB4K.Entries = 128;
					IdentificationData.Cache.L1DataTLB4K.Associativity = -1;
					IdentificationData.Cache.L1DataTLB4M.Present = true;
					IdentificationData.Cache.L1DataTLB4M.Entries = 128;
					IdentificationData.Cache.L1DataTLB4M.Associativity = -1;
					return;
				   }
		case 0x5D: {IdentificationData.Cache.L1DataTLB4K.Present = true;
					IdentificationData.Cache.L1DataTLB4K.Entries = 256;
					IdentificationData.Cache.L1DataTLB4K.Associativity = -1;
					IdentificationData.Cache.L1DataTLB4M.Present = true;
					IdentificationData.Cache.L1DataTLB4M.Entries = 256;
					IdentificationData.Cache.L1DataTLB4M.Associativity = -1;
					return;
				   }
		case 0x66: {IdentificationData.Cache.L1DataCache.Present = true;
					IdentificationData.Cache.L1DataCache.Size = 8;
					IdentificationData.Cache.L1DataCache.Associativity = 4;
					IdentificationData.Cache.L1DataCache.LineSize = 64;
					IdentificationData.Cache.L1DataCache.LinesPerTag = -1;
					return;
				   }
		case 0x67: {IdentificationData.Cache.L1DataCache.Present = true;		//Itanium 2
					IdentificationData.Cache.L1DataCache.Size = 16;
					IdentificationData.Cache.L1DataCache.Associativity = 4;
					IdentificationData.Cache.L1DataCache.LineSize = 64;
					IdentificationData.Cache.L1DataCache.LinesPerTag = -1;
					return;
				   }
		case 0x68: {IdentificationData.Cache.L1DataCache.Present = true;
					IdentificationData.Cache.L1DataCache.Size = 32;
					IdentificationData.Cache.L1DataCache.Associativity = 4;
					IdentificationData.Cache.L1DataCache.LineSize = 64;
					IdentificationData.Cache.L1DataCache.LinesPerTag = -1;
					return;
				   }
		case 0x70: {IdentificationData.Cache.TraceCache.Present = true;
					IdentificationData.Cache.TraceCache.MicroOps = 12;
					IdentificationData.Cache.TraceCache.Associativity = 8;
					return;
				   }
		case 0x71: {IdentificationData.Cache.TraceCache.Present = true;
					IdentificationData.Cache.TraceCache.MicroOps = 16;
					IdentificationData.Cache.TraceCache.Associativity = 8;
					return;
				   }
		case 0x72: {IdentificationData.Cache.TraceCache.Present = true;
					IdentificationData.Cache.TraceCache.MicroOps = 32;
					IdentificationData.Cache.TraceCache.Associativity = 8;
					return;
				   }
		case 0x77: {IdentificationData.Cache.L1CodeCache.Present = true;		//Itanium 2
					IdentificationData.Cache.L1CodeCache.Size = 16;
					IdentificationData.Cache.L1CodeCache.Associativity = 4;
					IdentificationData.Cache.L1CodeCache.LineSize = 64;
					IdentificationData.Cache.L1CodeCache.LinesPerTag = -1;
					return;
				   }
		case 0x79: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 128;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x7A: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 256;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x7B: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 512;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x7C: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 1024;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 64;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x7E: {IdentificationData.Cache.L2UnifiedCache.Present = true;		//Itanium 2
					IdentificationData.Cache.L2UnifiedCache.Size = 256;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 128;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x82: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 128;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x83: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 256;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x84: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 512;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x85: {IdentificationData.Cache.L2UnifiedCache.Present = true;
					IdentificationData.Cache.L2UnifiedCache.Size = 1024;
					IdentificationData.Cache.L2UnifiedCache.Associativity = 8;
					IdentificationData.Cache.L2UnifiedCache.LineSize = 32;
					IdentificationData.Cache.L2UnifiedCache.LinesPerTag = -1;
					return;
				   }
		case 0x8D: {IdentificationData.Cache.L3UnifiedCache.Present = true;		//Itanium 2
					IdentificationData.Cache.L3UnifiedCache.Size = 3072;
					IdentificationData.Cache.L3UnifiedCache.Associativity = 12;
					IdentificationData.Cache.L3UnifiedCache.LineSize = 128;
					IdentificationData.Cache.L3UnifiedCache.LinesPerTag = -1;
					return;
				   }
	}

//	printf("Unknown Intel Cache Descriptor: %x\n", CacheDescriptor);
}

int AMDAssociativity(int Value)
{
	switch (Value)
	{
		case 0x00: return 0;
		case 0x01: return 1;
		case 0x02: return 2;
		case 0x04: return 4;
		case 0x06: return 8;
		case 0x08: return 16;
		case 0x0F: return -1;
	}

//	puts("Unknown AMD Cache Descriptor");
	return -1;
}

void IdentifyProcessor(IdentificationStructure &IdentificationData, int Extra)
{
	for (int i = 0; i < 1000; i++)
	{
		if (ProcessorList[i].Family == IdentificationData.Processor.Family
			&& ProcessorList[i].Model == IdentificationData.Processor.Model
			&& ProcessorList[i].Stepping == IdentificationData.Processor.Stepping
			&& ProcessorList[i].Extra == Extra)
		{
			strcpy(IdentificationData.Processor.Name, ProcessorList[i].Name);
			return;
		}
	}

	strcpy(IdentificationData.Processor.Name, "Unknown Processor");
}

