/**********************************************************************************************************************/
/* Processor Identification                                                                                           */
/**********************************************************************************************************************/

//Name      Title                                                                               Revision

/*
AMD         AMD-K6 Processor Model 6 Revision Guide                                             G       1998 August
AMD         AMD-K6 Processor Model 7 Revision Guide                                             H       1999 June
AMD         AMD-K6-2 Processor Model 8 Revision Guide                                           F       1999 June
AMD         AMD-K6-III Processor Model 9 Revision Guide                                         C       1999 July
AMD         AMD Athlon Processor Model 1 & Model 2 Revision Guide                               D       2000 August
AMD         AMD Duron Processor Model 3 Revision Guide                                          I       2002 December
AMD         AMD Athlon Processor Model 4 Revision Guide                                         I       2002 December
AMD         AMD Athlon Processor Model 6 Revision Guide                                         E       2002 December
AMD         AMD Duron Processor Model 7 Revision Guide                                          C       2002 December
AMD         AMD Athlon Processor Model 8 Revision Guide                                         C       2002 December

Intel       Intel386 CX/SXSA Microprocessor Specification Update                                002     1997 January
Intel       Intel386 DX Processor Specification Update                                          002     1997 January
Intel       Intel386 EX Embedded Processor Specification Update                                 010     1998 October
Intel       60- and 66-MHz Pentium Processor Specification Update                               001     1997 February
Intel       Pentium Processor Specification Update                                              041     1999 January
Intel       Pentium Pro Processor Specification Update                                          039     1999 January
Intel       Mobile Intel Celeron Processor at 466 MHz, ... Specification Update                 038     2002 November
Intel       Mobile Intel Pentium II Processor Specification Update                              046     2002 November
Intel       Intel Pentium II Xeon Processor Specification Update                                032     2002 January
Intel       Intel Pentium II Processor Specification Update                                     049     2002 July
Intel       Intel Celeron Processor Specification Update                                        047     2002 October
Intel       Intel Pentium III Processor Specification Update                                    045     2002 November
Intel       Mobile Intel Celeron Processor (0.18µ and 0.13µ) Specification Update               030     2002 August
Intel       Mobile Intel Pentium III Processor and ... Specification Update                     036     2002 November
Intel       Intel Pentium III Xeon Processor Specification Update                               037     2002 July
Intel       Intel Pentium 4 Processor Specification Update                                      029     2002 November
Intel       Mobile Intel Pentium 4 Processor-M Specification Update                             008     2002 November
Intel       Intel Celeron Processor in the 478-Pin Package Specification Update                 005     2002 November
Intel       Mobile Intel Celeron Processor on .13 Micron ... Specification Update               002     2002 August
Intel       Intel Xeon Processor Specification Update                                           020     2002 November
Intel       Intel Xeon Processor MP Specification Updata                                        009     2002 November
Intel       Low Voltage Intel Xeon Processor Specification Update                               003     2002 November
Intel       Intel Pentium M Processor                                                           001     2003 March

Intel       Intel Itanium Processor Specification Update                                        008     2003 January
Intel       Intel Itanium 2 Processor Specification Update                                      007     2003 January

AMD         AMD Processor Recognition                                                           W-1     2002 November
Intel       Intel Processor Identification and the CPUID Instruction                            023     2003 March
Intel       Intel Processor Serial Number                                                       001     1999 March

IDT         IDT WinChip C6 Data Sheet                                                           1.10    1998 March
*/

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



  8086 - 80368  Intel Only
  80486         Lots of manufacturers, almost no stpping info
  80586         Lots of incorrect information and processors that were never sold, no stepping info
  80686         Celeron / Pentium / Xeon // !Mobile! (Inel realy srewed up the names here)
  80786         VERY WELL DONE BY INTEL (at least names are a bit more consistant)
  80886         Not officialy realeasd at the moment

    Intel detection:    AAA xxh doesn't #UD
    Cyrix Detection:    Read the chipset data, but I heard there was a better one
    AMD Detection       If there not TI, IBM, UMC, Cyrix or Intel, must be AMD, need sometin' better
    UMC Detection       support CPUID I believe
    Texas Detection     Models do not real conflic (aren't those things the same as IBM have to check)
    IBM Detection       Ax or 8x as family (but there are exceptions) and models do not conflict


    CYRIX/TI/IBM Identificaton through Chipset Data (I/O 22h and 23h)


    Not about the use of stepping and revision:
        Stepping is used always. I try to change this into: Stepping = A0 / Revision = 3h
        Intel also calls the revion Stepping ID


    386 Reset Data
     0- 3   Minor Stepping      Revision
     4- 7   Major Stepping      Model
     8-11   Family              Family
    12-15   Type                DX/SX/SL and TI/IBM/Intel


    486+ Reset Data
     0- 3   Revision
     4- 7   Model
     8-11   Family
    12-13   Type                0 = Normal, 1 = OverDrive, 2 = Second Processor, 3 = Reserved
    14-15   Reserved
    16-19   Extended Model
    20-27   Extended Family
    28-30   Reserved
    31      Reserved            Has Serial Number


    All over drives could also have type 0 if they are an errata (whatever that means)

    Legal Mumbo Jumbo: In the CPUID Documentation, Intel says the PSN could be reported wrongly, for
        example if the voltage or frequency is wrong. It doesn't say it's corec when the processor is
        working on the correct voltage and frequency...

  IF HighetExtened CPUID Fucntion > 0x80000000 Brand String is supported, even if 0x800000001 or 2 ???

  Should OverDrives just be ignored? According to Intel internal caches or execution times may vary
  According to Intel CPUID is unreliable in V86 Mode
  According to Intel MSRs vary between different Models of the Pentium (P5 that is)
  PSN is not guaranteed to be unique
  Intel PSN Style: XXXX-XXXX-XXXX-XXXX-XXXX-XXXX        (96 bit)
  Transmeta PSN S: XXXXXXXX:XXXXXXXX:XXXXXXXX:XXXXXXXX  (128 bit)
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

    8086    EFLAGS 12-15 are always set
    80286   EFLAGS 12-15 are clear in RM
    80366   EFLAGS 18   Cant be set, if it can it a 486+
    80848   EFLAGS 21   Can't be set, if it can use CPUID

    FPU     If control/status word can be saved it's present
    27/387  Infinity control Rounding Stuff

    487     486 with coproc


  What about the Xeon DP????

  CMXCHG8B  Disabled because of Stuoid MSWinNT bug (studpid. Microsft not diabling. stupid)




  sAVE bRAND sTRING BEFRORE s3 POWER DOWN


  NSC Geode!!!!



  "The iAPX 286 will push a different value on the stack for PUSH SP than the iAPX 86/88."
  "When a word write is performed at offset FFFFh in a segment, the 8086 will write one byte at offset
        FFFFh, and the other at offset 0, while an 80186 family processor will write one byte at offset
        FFFFh, and the other at offset 10000h (one byte beyond the end of the segment)."

  
//  A finalty note: I'm looking for some information on the Intel Timna (Intel's MediaGX). The project
//  was abandonned so Intel never published any useful material on this. It was based on the P-III.

//  Also some info in the Microsoft X-Box' special P-III would help




 */

typedef struct {
    unsigned   n;
    char*    i;
    char* v;
} VENDORLIST;

VENDORLIST VendorList[] =
{
    {0x0001, "ThinkTrinary", "Trinary Technologies"},
    {0x0002, "GenuineIntel", "Intel"},
    {0x0003, "AuthenticAMD", "AMD"},
    {0x0003, "AMD ISBETTER", "AMD"},
    {0x0004, "CentaurHauls", "Centaur (IDT / VIA)"},
    {0x0005, "CyrixInstead", "Cyrix (VIA)"},
    {0x0006, "GenuineTMx86", "Transmeta"},
    {0x0007, "Geode by NSC", "National Semiconductor"},
    {0x0008, "NexGenDriven", "NexGen"},
    {0x0009, "RiseRiseRise", "Rise"},
    {0x000A, "SiS SiS SiS ", "SiS"},
    {0x000B, "UMC UMC UMC ", "UMC"},
};

typedef struct {
    long long id;
    bool    verified;
    char* name;
} PROCLIST;



PROCLIST ProcessorList[] =
{
    {0x00FFFFFF, false, "Unknown x86 Processor"},
        {0x0000FFFF, false, "Unknown 8086 Compatible Processor"},
        {0x0001FFFF, false, "Unknown 186 Compatible Processor"},    
        {0x0002FFFF, false, "Unknown 286 Compatible Processor"},
        {0x0003FFFF, false, "Unknown 386 Compatible Processor"},
        {0x0004FFFF, false, "Unknown 486 Compatible Processor"},
        {0x0005FFFF, false, "Unknown 586 Compatible Processor"},
        {0x0006FFFF, false, "Unknown 686 Compatible Processor"},
    {0x02FFFFFF, false, "Unknown Intel Processor"},
        {0x0203FFFF, false, "Unknown Intel i386 Processor"},
        {0x0204FFFF, false, "Unknown Intel i486 Processor"},
        {0x0205FFFF, false, "Unknown Intel Pentium Processor"},
            {0x020501FF, false, "Intel Pentium Classic"},
            {0x020502FF, false, "Intel Pentium"},
            {0x020503FF, false, "Intel Pentium OverDrive"},
            {0x020504FF, false, "Intel Pentium MMX"},
            {0x020507FF, false, "Intel Pentium Mobile"},
            {0x020508FF, false, "Intel Pentium MMX Mobile 'Tillamook'"},
        {0x0206FFFF, false, "Unknown Intel P6 Processor"},
            {0x020601FF, false, "Intel Pentium Pro"},
            {0x020603FF, false, "Unknown Intel Pentium II"},
                {0x02060301, false, "Intel Pentium II 'Klamath'"},      /* 0512 - 0512     */
                {0x02060305, false, "Intel Pentium II OverDrive"},      /* OVERDRIVE       */
            {0x020605FF, false, "Unknown Intel Pentium II"},
                {0x02060500, false, "Intel Celeron II 'Covington'"},    /* 0000 - 0000     */
                {0x02060501, false, "Intel Pentium II 'Deschutes'"},    /* 0512 - 0512     */
                {0x02060502, false, "Intel Xeon II 'Drake'"},           /* 0512 - 2048     */
                {0x02060504, false, "Intel Pentium II Mobile 'Tonga'"}, /* 0512 - 0512     */
            {0x020606FF, false, "Unknown Intel Pentium II"},
                {0x02060600, false, "Intel Celeron II 'Mendocino'"},    /* 0128 - 0128     */
/**/            {0x02060603, false, "Intel Celeron II Mobile"},         /* 0128 - 0128 (A) */
                {0x02060604, false, "Intel Pentium II Mobile 'Dixon'"}, /* 0256 - 0256 (A) */
            {0x020607FF, false, "Unknown Intel Pentium III"},
                {0x02060701, false, "Intel Pentium III 'Katmai'"},      /* 0512 - 0512     */
                {0x02060702, false, "Intel Xeon III 'Tanner'"},         /* 0512 - 2048     */
            {0x020608FF, false, "Unknown Intel Pentium III"},
                {0x02060801, false, "Intel Celeron III 'Coppermine'"},
                {0x02060802, false, "Intel Pentium III (Mobile) 'Coppermine'"},
                {0x02060803, false, "Intel Xeon III 'Cascades'"},
            {0x020609FF, false, "Unknown Intel Pentium M"},
                {0x02060916, false, "Intel Pentium M 'Banias'"},
            {0x02060AFF, false, "Unknown Intel Pentium III"},
                {0x02060A03, false, "Intel Xeon III 'Cascades'"},
            {0x02060BFF, false, "Unknown Intel Pentium III"},
                {0x02060B03, false, "Intel Celeron III 'Tualatin'"},
                {0x02060B04, false, "Intel Pentium III 'Coppermine'"},
                {0x02060B06, false, "Intel Pentium III Mobile 'Geyserville'"},
                {0x02060B07, false, "Intel Celeron III Mobile 'Geyserville'"},
        {0x0207FFFF, false, "Unknown Intel Itanium"},
        {0x020FFFFF, false, "Unknown Intel NetBurst Processor"},
                {0x020F0008, false, "Intel Pentium 4 'Willamette'"},
                {0x020F000E, false, "Intel Xeon 4 'Foster'"},
                {0x020F0108, false, "Intel Pentium 4 'Willamette'"},
                {0x020F0109, false, "Intel Pentium 4 'Willamette'"},
                {0x020F010A, false, "Intel Celeron 4 'Willamette'"},
                {0x020F010B, false, "Intel Xeon 4 MP 'Foster'"},
                {0x020F010E, false, "Intel Xeon 4 'Foster'"},
                {0x020F020C, false, "Intel Xeon 4 MP 'Gallatin'"},
                {0x020F0208, false, "Intel Celeron 4 Mobile 'Northwood'"},
                {0x020F0209, false, "Intel Pentium 4 'Northwood'"},
                {0x020F020B, false, "Intel Xeon 4 'Prestonia'"},
                {0x020F020E, false, "Intel Pentium 4 Mobile 'Northwood'"},
                {0x020F020A, false, "Intel Celeron 4 'Northwood'"},
        {0x0210FFFF, false, "Unknown Intel Itanium 2"},
    {0x03FFFFFF, false, "Unknown AMD Processor"},
        {0x0306FFFF, false, "Unknown AMD Athlon Processor"},
            {0x030601FF, false, "AMD Athlon 'Pluto'"},
            {0x030602FF, false, "AMD Athlon 'Argon'"},
            {0x030603FF, false, "AMD Duron 'Spitfire'"},
            {0x030604FF, false, "AMD Athlon 'Thunderbird'"},
            {0x030605FF, false, "AMD Athlon Ultra 'Mustang'"},
            {0x030606FF, false, "AMD Athlon MP 'Palomino'"},
            {0x030606FF, false, "AMD Athlon XP/MP 'Palomino'"},
            {0x030606FF, false, "AMD Athlon 4 Mobile 'Palomino'"},
            {0x030607FF, false, "AMD Duron 'Morgan'"},
            {0x030607FF, false, "AMD Duron MP 'Morgan'"},
            {0x030607FF, false, "AMD Duron Mobile 'Morgan'"},
            {0x030608FF, false, "AMD Athlon XP 'Thoroughbred'"},
            {0x030608FF, false, "AMD Athlon MP 'Thoroughbred'"},
            {0x030608FF, false, "AMD Athlon XP Mobile 'Thoroughbred'"},
            {0x030609FF, false, "AMD Duron 'Appaloosa'"},
            {0x030609FF, false, "AMD Duron MP 'Appaloosa'"},
            {0x030609FF, false, "AMD Duron Mobile 'Appaloosa'"},
            {0x03060AFF, false, "AMD Athlon XP 'Barton'"},
            {0x03060AFF, false, "AMD Athlon MP 'Barton'"},
    {0x04FFFFFF, false, "Unknown IDT / VIA Processor"},
        {0x0405FFFF, false, "Unknown IDT WinChip"},
            {0x040504FF, false, "IDT WinChip C6"},
            {0x040508FF, false, "IDT WinChip 2"},
            {0x040509FF, false, "IDT WinChip 3"},
        {0x0406FFFF, false, "Unknown VIA C3"},
            {0x040606FF, false, "VIA C3 'Samuel 1' / VIA Eden 4000"},
            {0x040607FF, false, "VIA C3 'Samuel 2 / Ezra' / VIA Eden 5000 / VIA Eden 6000"}, /* 0-7 / 8-F */
            {0x040608FF, false, "VIA C3 'Ezra-T' (VIA Eden 7000)"},
//          {0x040609FF, false, "VIA C3 'Nehalem VIA Eden 8000"},
    {0x05FFFFFF, false, "Unknown Cyrix Processor"},
        {0x0506FFFF, false, "Unknown VIA Cyrix III"},
            {0x050605FF, false, "VIA Cyrix III 'Joshua'"},
    {0x06FFFFFF, false, "Unknown Transmeta Processor"},
        {0x0604FFFF, false, "Transmeta Crusoe 3x00 / 5x00 Processor"},
    {0x08FFFFFF, false, "Unknown NexGen Processor"},
        {0x0805FFFF, false, "Unknown NexGen Nx586 / Nx686 Processor"},
            {0x080500FF, false, "Unknown NexGen Nx586"},
                {0x08050000, false, "NexGen Nx586"},
                {0x08050001, false, "NexGen Nx586FP"},
            //{0x0805??FF, false, "Unknown NexGen Nx686"},
    {0x0CFFFFFF, false, "Unknown UMC Processor"},
        {0x0C04FFFF, false, "Unknown UMC 486 Processor"},
            {0x0C0401FF, false, "UMC U5SD"},
            {0x0C0402FF, false, "UMC U5S"},
            {0x0C0403FF, false, "UMC U486DX2"},
            {0x0C0405FF, false, "UMC U486SX2"},








  {0xABCDABCD, false, "XXX"}
};


#if 0
    /**********************************************************************************************/
//  {"GenuineIntel", 0x05, 0x00, 0x0?,    0, false, "Intel Pentium Classic (A*)"},
//  {"GenuineIntel", 0x05, 0x01, 0x02,    0, false, "Intel Pentium Classic (B*)"},
//  {"GenuineIntel", 0x05, 0x01, 0x04,    0, false, "Intel Pentium Classic (B2)"},
//  {"GenuineIntel", 0x05, 0x04, 0x01,    0, false, "Intel Pentium MMX (A1)"},
//  {"GenuineIntel", 0x05, 0x04, 0x02,    0, false, "Intel Pentium MMX (A2)"},
//  {"GenuineIntel", 0x05, 0x05, 0x0?,    0, false, "Intel Pentium MMX OverDrive"},
//  {"GenuineIntel", 0x05, 0x06, 0x0?,    0, false, "Intel Pentium MMX OverDrive"},
//  {"GenuineIntel", 0x06, 0x00, 0x0?,    0, false, "Intel Pentium Pro (A0)"},
//  {"GenuineIntel", 0x06, 0x04, 0x0?,    0, false, "Intel Pentium II OverDrive (?)"},
//  {"GenuineIntel", 0x0F, 0x02, 0x07, 0x0E, false, "Intel Pentium 4 Mobile (C1)"},
//  {"AuthenticAMD", 0x06, 4, 4, 0, false, "AMD Athlon 'Thunderbird' Model 4 (B0)"},    //??Grzegorz
//  {"AuthenticAMD", 0x06,5?, ?, 0, false, "AMD Athlon Ultra 'Mustang' Model 5? (??)"},         /* CANCELED */
//  {"GenuineIntel",F?,3?, ?, ?, "Intel Pentium 4 'Prescott' (??)"},    //.09
//  {"GenuineIntel",F?,3?, ?, ?, "Intel Xeon 4 'Nocona' (??)"},         //.09
//  {"GenuineIntel",F?,4?, ?, ?, "Intel Pentium 4 'Tyler' (??)"},
//  {"GenuineIntel",F?,4?, ?, ?, "Intel Pentium 4 'Tejas' (??)"},
//  {"GenuineIntel",F?,4?, ?, ?, "Intel Xeon 4 'Potomac' (??)"},
//  {"GenuineIntel", ?,?, ?, ?, "Intel Mobillium 'Banias' (??)"},
//  {"GenuineIntel", ?,?, ?, ?, "Intel Mobillium 'Dothan' (??)"},
//  Intel's truly mobile processor. Intel says this is a completly new processor. Sources say it's just
//  a rework of the PIII or P4. I don't believe this, beacause it has SSE2 (not in PIII) and is faster
//  than the P4. I guess they just shortened the enormous 20 stage P4 pipeline a bit, which is too long
//  to be used effecivly. More backup is provided for the fact that the Pentium 5 will be based upon
//  this chip. And another thing many sources will tell you this chip will be called 'Intel Banias',
//  didn't Intel call the Pentium III, Intel Katmai for a very long time. With this in mind it wouldn't
//  even surprise me if this processor is goin to be called Pentium 5. Sorry but I have to go one now
//  I'm brainstorming. The mobile part of it might not even be used for mobile computers, but for
//  desktops and servers as well, because cooling has become almost impossible today. If speeds are
//  going to get even higher the next couple of years, the processor cores will just melt. Because
//  AMD's processors get even hotter and isn't working on a similar project Intel might even regain
//  it's market monopoly (wheter this is good or bad, I don't know?)
//  {"GenuineIntel",F?,?, ?, ?, "Intel Pentium 5 'Nehalem' (??)"},
//  This is just a rumor. It's supposed to come out in 2006, run at 6Ghz and have a bus speed of
//  1.5Ghz. It COULD be using the Intel Banias core. Suggesting the Banias is a Pentium 5 and that it
//  IS completely new. IF you read the note above this could also be the Pentium 6 or something.
//  {"GenuineIntel", 7, 6, 4, 0, "Intel Itanium 'Merced' (C0)"},                //0007000604
//  {"GenuineIntel", 7, 7, 4, 0, "Intel Itanium 'Merced' (C1)"},                //0007000704
//  {"GenuineIntel", 7, 7, 4, 0, "Intel Itanium 'Merced' (C2)"},                //0007000804
//  {"GenuineIntel", 0x10, 0, ?, 0, "Intel Itanium 2 'McKinley' (B3)"},         //001F000704
//  {"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2 'Madison' (??)"},
//  {"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2 'Deerfield' (??)"},
//  {"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2 'Montecito' (??)"}
//  {"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2 'Shavano' (??)"},
//  {"GenuineIntel",A?, ?, ?, ?,  ???, "Intel Itanium 2? 'Yosemite' (??)"},

//  {"AuthenticAMD", ?, ?, ?, ?, "AMD Athlon XP64 / Hammer 'Clawhammer' (??)"},
//  {"AuthenticAMD", ?, ?, ?, ?, "AMD Athlon XP64 / Hammer 'San Diego' (??)"},
//  {"AuthenticAMD", ?, ?, ?, ?, "AMD Athlon XP64 / Hammer Mobile 'Odessa' (??)"},
//  {"AuthenticAMD", ?, ?, ?, ?, "AMD Opteron 'Sledgehammer' (??)"},
//  {"AuthenticAMD", ?, ?, ?, ?, "AMD Opteron 'Athens' (??)"},
//  {"CentaurHauls", 0x05, 0x08, 0x01, 0x00, false, "IDT WinChip 2"},
//  {"CentaurHauls", 6, 0xA, ?, 0, "IDT WinChip 4"},        //PROBABLY DOESN'T EXIST! -> Is a VIA C3!!!

    /** Intel 8086 / 8088 (Includes model manufactured by AMD, Harris, Siemens, Hitachi) ************/

    //I belive there an alroithm to identify the diff between HMOS and CMOS models
    {"GenuineIntel", 1, 0, 0, 0, false, "Intel 8088"},
    {"GenuineIntel", 1, 0, 0, 1, false, "Intel 8086"},
    {"GenuineIntel", 1, 0, 0, 2, false, "Intel 80C88"},
    {"GenuineIntel", 1, 0, 0, 3, false, "Intel 80C86"},
    {"GenuineIntel", 1, 0, 0, 4, false, "Intel 80188"}, //XL/EA/EB/EC       AMD/Siemens
    {"GenuineIntel", 1, 0, 0, 5, false, "Intel 80186"}, //XL/EA/EB/EC       AMD/Siemens
    {"GenuineIntel", 1, 0, 0, 6, false, "NEC V20"}, //V20H/V25/V25 Plus/V25 Softwae Guard/V40/V40H//V45
    {"GenuineIntel", 1, 0, 0, 7, false, "NEC V30"}, //V30H/V35/V35 Plus/V35 Softwae Guard/V50/V50H//V55
    //Intel 80886???

    {"GenuineIntel", 2, 0, 0, 0, false, "Intel 80286"},//amd/harris/siemens/fujitsu/kruger
    
    
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
    // * Intel i386DX           : F0
    {"GenuineIntel", 3, 0, 3, 0, false, "Intel i386DX (B0/B1/B2/B3/B4/B5/B6/B7/B8/B9/B10)"},
    {"GenuineIntel", 3, 0, 4, 0, false, "Intel i386DX (C???)"}, // Stepping not confiremed
    {"GenuineIntel", 3, 0, 5, 0, false, "Intel i386DX (D0)"},
    {"GenuineIntel", 3, 0, 8, 0, false, "Intel i386DX (D1/D2/E0/E1/F0)"}, //E0/E1/F0 coulld also be 9!!!
    
    //The family 23 could also simply be 3 (I don't know were the 2 stands for???) Officialy not part
    //Difference between DX and SX perhaps (I hope so)
    // * Intel i386CX/SXSA      : A2 / B
    // * Intel i386EX           : A0 / B1 / B2
    {"GenuineIntel",23, 0, 4, 0, false, "Intel i386SX (A0)"},
    {"GenuineIntel",23, 0, 5, 0, false, "Intel i386SX (B)"},
    {"GenuineIntel",23, 0, 8, 0, false, "Intel i386SX (C/D/E)"},
    {"GenuineIntel",23, 0, 8, 0, false, "Intel i386CXSA/B (A) / i386EX (A) / i386SXSA (?)"},    //A || B
    {"GenuineIntel",23, 0, 9, 0, false, "Intel i386SX (?)"},    //EMBEDDED (CX/FX
    {"GenuineIntel",23, 0, 9, 0, false, "Intel i386EX (A0/B1/C1)"},
    
    //Dito for 33 (376 perhaps)
    {"GenuineIntel",33, 0, 5, 0, false, "Intel i376 (A0)"}, //Never used in PC because they only work in PM
    {"GenuineIntel",33, 0, 8, 0, false, "Intel i376 (B)"},  //...

    //And againt for 43 (386SL)
    //have a signatur register @ 30e
    //step level A0: 0x4300, 
    //step level A1: 0x4300, 
    //step level A2: 0x4301, 
    //step level A3: 0x4302, 
    //step level B0: 0x4310, 
    //step level B1: 0x4311. 
//  {"GenuineIntel",43, 0, 5, ?, false, "Intel i386SL (B)"},
//  {"GenuineIntel",43, 0, 5, ?, false, "Intel i386SL (A0/A1/A2/A3)"},  //Not sure about this
//  {"GenuineIntel",43, 1, 0, 0, false, "Intel i386SL (A0/A1/A2/A3)"},
//  {"GenuineIntel",43, 1, 1, 0, false, "Intel i386SL (B0/B1)"},

    //RapidCADs are not so familiar to me, where they ever used in PCs???
    {"GenuineIntel", 3, 4, 0, 0, false, "Intel RapidCAD (A)"},
    {"GenuineIntel", 3, 4, 1, 0, false, "Intel RapidCAD (B)"},


    /** Intel 486 ***********************************************************************************/
    
    //According to Intel only SL Enhanced and WB Enhanced processors support CPUID
    
    {"GenuineIntel", 4, 0, 0, 0, false, "Intel i486DX (A0/A1)"},
    {"GenuineIntel", 4, 0, 1, 0, false, "Intel i486DX (B2/B3/B4/B5/B6)"},
    {"GenuineIntel", 4, 0, 2, 0, false, "Intel i486DX (C0)"},
    {"GenuineIntel", 4, 0, 3, 0, false, "Intel i486DX (C1)"},
    {"GenuineIntel", 4, 0, 4, 0, false, "Intel i486DX (D0)"},
//  {"GenuineIntel", 4, 0, ?, 0, false, "Intel i486DX"},

    {"GenuineIntel", 4, 1, 0, 0, false, "Intel i486DX (cA2/cA3)"},
    {"GenuineIntel", 4, 1, 1, 0, false, "Intel i486DX (cB0/cB1)"},
    {"GenuineIntel", 4, 1, 3, 0, false, "Intel i486DX (cC0)"},
    {"GenuineIntel", 4, 1, 4, 0, false, "Intel i486DX (aA0/aA1)"},  //SL Enhanced
    {"GenuineIntel", 4, 1, 5, 0, false, "Intel i486DX (aB0)"},  //SL Enhanced
//  {"GenuineIntel", 4, 1, ?, 0, false, "Intel i486DX"},

    {"GenuineIntel", 4, 2, 0, 0, false, "Intel i486SX / i487SX (A0)"},  //Should 487 be model 3
    {"GenuineIntel", 4, 2, 1, 0, false, "Intel i487SX (B0)"},   //Should 487 be model 3
    {"GenuineIntel", 4, 2, 2, 0, false, "Intel i486SX (B0)"},
    {"GenuineIntel", 4, 2, 3, 0, false, "Intel i486SX (bBx)"},  //SL Enhanced and... CPUID
    {"GenuineIntel", 4, 2, 4, 0, false, "Intel i486SX (gAx)"},
    {"GenuineIntel", 4, 2, 7, 0, false, "Intel i486SX (cA0)"},
    {"GenuineIntel", 4, 2, 8, 0, false, "Intel i486SX (cB0)"},
    {"GenuineIntel", 4, 2, 0xA, 0, false, "Intel i486SX (aA0/aA1)"},    //SL Enhanced
    {"GenuineIntel", 4, 2, 0xB, 0, false, "Intel i486SX (aB0/aC0)"},    //SL Enhanced
    {"GenuineIntel", 4, 2, 0xE, 0, false, "Intel i486SX (E)"},  //SL Enhanced??? Grzegorz
//  {"GenuineIntel", 4, 2, ?, 0, false, "Intel i486SX"},

//  {"GenuineIntel", 4, 3, ?, 0, false, "Intel i486DX2 / i486DX2 OverDrive / i487"},
    {"GenuineIntel", 4, 3, 2, 0, false, "Intel i486DX2 (A0/A1/A2)"},
    {"GenuineIntel", 4, 3, 3, 0, false, "Intel i486DX2 (B1)"},
    {"GenuineIntel", 4, 3, 4, 0, false, "Intel i486DX2 (aA0/aA1)"}, //SL Enhanced
    {"GenuineIntel", 4, 3, 5, 0, false, "Intel i486DX2 (aB0/aC0)"}, //SL Enhanced
    {"GenuineIntel", 4, 3, 6, 0, false, "Intel i486DX2"},   //Possibly as WB in WT Mode

    {"GenuineIntel", 4, 4, 0, 0, false, "Intel i486SL (A)"},
    {"GenuineIntel", 4, 4, 1, 0, false, "Intel i486SL (?)"},
    {"GenuineIntel", 4, 4, 3, 0, false, "Intel i486SL (?)"},    //In Intel Docs, saupoosed to support CPUID
//  {"GenuineIntel", 4, 4, ?, 0, false, "Intel i486SL"},

//  {"GenuineIntel", 4, 5, ?, 0, false, "Intel i486SX2"},
    {"GenuineIntel", 4, 5, 0xB, 0, false, "Intel i486SX2 (aC0)"},   //SL Enhanced

    {"GenuineIntel", 4, 7, 0, 0, false, "Intel i486DX2-WB (A)"},
    {"GenuineIntel", 4, 7, 3, 0, false, "Intel i486DX2-WB (?)"},    //In Intel Docs, saupoosed to support CPUID
//  {"GenuineIntel", 4, 7, ?, 0, false, "Intel i486DX2-WB"},

    {"GenuineIntel", 4, 8, 0, 0, false, "Intel i486DX4 (A)"},
    {"GenuineIntel", 4, 8, 0, 1, false, "Intel i486DX4 OverDrive (A)"},
    {"GenuineIntel", 4, 8, 3, 0, false, "Intel i486DX4 (A)"},   //Possibly as WB in WT Mode, Support CPUID
//  {"GenuineIntel", 4, 8, ?, 0, false, "Intel i486DX4 / i486DX4 OverDrive"},

    {"GenuineIntel", 4, 9, 0, 0, false, "Intel i486DX4-WB (A)"}, //(Do not exist according to Intel CPUID Inf)
//  {"GenuineIntel", 4, 9, ?, 0, false, "Intel i486DX4-WB"},


    /** AMD *****************************************************************************************/
    
    {"AuthenticAMD", 4, 1, 2, 0, false, "AMD 486DX"},
    {"AuthenticAMD", 4, 3, 2, 0, false, "AMD 486DX/2"}, //DX4 (WT2x) toooo && DXL2 / DX4NV8T
    {"AuthenticAMD", 4, 3, 4, 0, false, "AMD 486DX/2"}, //DX4 (WT2x) toooo && DXL2 / DX4SV8B
//  {"AuthenticAMD", 4, 7, ?, 0, false, "AMD 486DX/2-WB"},  //DX4 (WB2x)
    {"AuthenticAMD", 4, 7, 4, 0, false, "AMD SV8B (WT)"},
//  {"AuthenticAMD", 4, 8, ?, 0, false, "AMD 486DX/4"},     //5x86 toooo
    {"AuthenticAMD", 4, 8, 4, 0, false, "AMD 486DX/4"}, //3xWT
    {"AuthenticAMD", 4, 9, 4, 0, false, "AMD 486DX/4-WB"},  //3xWB
    {"AuthenticAMD", 4, 0xE, 4, 0, false, "AMD Am5x86-WT"},     //AMD Enhanced 486
    {"AuthenticAMD", 4, 0xF, 4, 0, false, "AMD Am5x86-WB (4)"}, //AMD Enhanced 486
    
    //cores: 5.0 / 5.0 (MMX) / 5.1 / 5.2
    {"AuthenticAMD", 5, 0, 0, 0, false, "AMD K5 SSA/5 (E)"},        //??? Stepping Name
    {"AuthenticAMD", 5, 0, 1, 0, false, "AMD K5 SSA/5 (F)"},        //??? Stepping Name
//  {"AuthenticAMD", 5, 0, ?, 0, false, "AMD K5 SSA/5 (?)"},        //??? Stepping Name
//  {"AuthenticAMD", 5, 1, ?, 0, false, "AMD K5 5k86 Model 1 (?)"},     //??? Stepping Name
    {"AuthenticAMD", 5, 1, 1, 0, false, "AMD K5 5k86 Model 1 (?)"},     //??? Stepping Name
    {"AuthenticAMD", 5, 1, 2, 0, false, "AMD K5 5k86 Model 1 (?)"},     //??? Stepping Name
    {"AuthenticAMD", 5, 1, 4, 0, false, "AMD K5 5k86 Model 1 (?)"},     //CLKMUL=1.5
//  {"AuthenticAMD", 5, 2, ?, 0, false, "AMD K5 5k86 Model 1 (?)"},     //??? Stepping Name
    {"AuthenticAMD", 5, 2, 4, 0, false, "AMD K5 5k86 Model 2 (?)"},     //CLKMUL=1.75
//  {"AuthenticAMD", 5, 3, ?, 0, false, "AMD K5 5k86 Model 3 (?)"},     //??? Stepping Name (NOT RELEASED)
    {"AuthenticAMD", 5, 3, 4, 0, false, "AMD K5 5k86 Model 1 (?)"},     //CLKMUL=2.0
    
    
    //Missing: MobileS (= k6-7!!!) / K6-2+ n/ K6-III+
    {"AuthenticAMD", 5, 6, 1, 0, false, "AMD-K6 Model 6 (B)"},
    {"AuthenticAMD", 5, 6, 2, 0, false, "AMD-K6 Model 6 (C)"},
    {"AuthenticAMD", 5, 7, 0, 0, false, "AMD-K6 Model 7 'Little Foot' (A)"},
    {"AuthenticAMD", 5, 8, 0, 0, false, "AMD-K6-2 Model 8 'Chomper' (A0)"}, //doesnt CXT stnd fr Chomber XT
//  {"AuthenticAMD", 5, 8, 8, 0, false, "AMD-K6-2 Model 8 'Chomper' (AC)"}, //In Recognition < CXT
    {"AuthenticAMD", 5, 8, 0xC, 0, false, "AMD-K6-2 Model 8 'Chomper' (AC)"},   //CXT Core (Write COmbining) I believe YES!!! avvording to Chase
    {"AuthenticAMD", 5, 9, 1, 0, false, "AMD-K6-III 'Sharptooth' Model 9 (B)"},
//  {"AuthenticAMD", 5, 0xD, ?, 0, false, "AMD-K6-2+ / K6-III+ 'Sharptooth' (?)"}, //Not doced by AMD (3DNow!+)

//* {"AuthenticAMD", 6, 0, ?, 0, "AMD K7 [ES]"},        //UNDOCUMENTED!?!


    /* Cyrix **************************************************************************************/

    //My sources are unreliable at best for these suckers, so I list them all
    //Also I belive the names aren't entire ly correct, confused codename/ actualt name and extensions

    {"CyrixInstead", 0, 0, 5, 0, false, "Cyrix M5 Cx486S/D"},   //No CPUID I believe (is family correct?)
    {"CyrixInstead", 0, 0, 6, 0, false, "Cyrix M6 Cx486DX"},    //...
    {"CyrixInstead", 0, 0, 7, 0, false, "Cyrix M7 Cx486DX2"},   //...
    {"CyrixInstead", 0, 0, 8, 0, false, "Cyrix M8 Cx486DX4"},   
    //...

    {"CyrixInstead", 4, 1, 0, 0, false, "Cyrix 4x86SLC"},
//  {"CyrixInstead", 4, 2, ?, 0, false, "Cyrix 5x86"},
    {"CyrixInstead", 4, 2, 9, 0, false, "Cyrix 5x86 (Rev 1-)"}, //Bus *2
    {"CyrixInstead", 4, 2, 0xB, 0, false, "Cyrix 5x86 (Rev 1-)"},   //Bus *2
    {"CyrixInstead", 4, 2, 0xD, 0, false, "Cyrix 5x86 (Rev 1-)"},   //Bus *3
    {"CyrixInstead", 4, 2, 0xF, 0, false, "Cyrix 5x86 (Rev 1-)"},   //Bus *3
//  {"CyrixInstead", 4, 4, ?, 0, false, "Cyrix MediaGX"},
    {"CyrixInstead", 4, 9, 0, 0, false, "Cyrix 5x86 (Rev 2+)"},
//  {"CyrixInstead", 4, 9, ?, 0, false, "Cyrix 5x86"},

    
//  IBM ID=15h Top (65 KB JPG) and Bottom (104 KB JPG)
//  IBM ID=17h Top (71 KB JPG) and Bottom (110 KB JPG)
//  Cyrix ID=17h Top (63 KB JPG) and Bottom (102 KB JPG)
//  IBM ID=22h Top (82 KB JPG) and Bottom (99 KB JPG) 
//  {"CyrixInstead", 5, 0, ?, 0, false, "Cyrix M1 (6x86)"}, //Grzegorz
    {"CyrixInstead", 5, 2, 0, 0, false, "Cyrix M1 (6x86)"}, //Early Models (L / non-L versions???? (LV too))
//  {"CyrixInstead", 5, 2, ?, 0, false, "Cyrix M1 (6x86)"}, //Early Models (L / non-L versions???? (LV too))
    {"CyrixInstead", 5, 3, 0, 0, false, "Cyrix M1 (6x86)"}, //1.0x Bus Ratio
    {"CyrixInstead", 5, 3, 1, 0, false, "Cyrix M1 (6x86)"}, //2.0x Bus Ratio
    {"CyrixInstead", 5, 3, 2, 0, false, "Cyrix M1 (6x86)"}, //1.0x Bus Ratio
    {"CyrixInstead", 5, 3, 3, 0, false, "Cyrix M1 (6x86)"}, //2.0x Bus Ratio
    {"CyrixInstead", 5, 3, 4, 0, false, "Cyrix M1 (6x86)"}, //3.0x Bus Ratio
    {"CyrixInstead", 5, 3, 5, 0, false, "Cyrix M1 (6x86)"}, //4.0x Bus Ratio
    {"CyrixInstead", 5, 3, 6, 0, false, "Cyrix M1 (6x86)"}, //3.0x Bus Ratio
    {"CyrixInstead", 5, 3, 7, 0, false, "Cyrix M1 (6x86)"}, //4.0x Bus Ratio
//  {"CyrixInstead", 5, 4, ?, 0, false, "Cyrix MediaGX MMX"},


//  ID=02h Top (73 KB JPG) and Bottom (100 KB JPG)
//  ID=04h Top (79 KB JPG) and Bottom (106 KB JPG)
//  ID=08h Top (66 KB JPG) and Bottom (101 KB JPG) 
//  ID=53 07
    {"CyrixInstead", 6, 0, 0, 0, false, "Cyrix MII (6x86MX)"},
//  {"CyrixInstead", 6, 0, ?, 0, "Cyrix MII (6x86MX)"},

    //These guys are actualy a Cyrix M2 with minor enhancemets (3DNow! / better FPU), but who cares,
    //they were never taken into procuvtion. Although VIA C3 probalby stands for Cyrix M3 and not,
    //Centaur WinChip 3. THey got a WinChip 4 core. Josua was nOT released! Start with samual and Samual 2 then Ezra and Ezra-T
 //   {"CyrixInstead", 6, 5, 1, 0, false, "VIA Cyrix III 'Joshua'"},  //2.0x Bus Ratio

    //Other names heard: Cyrix M-III 'Mojave' (Chase, so reliable never produced!)
    // Cayenne / Gobi / Jalapeno
    // Cayenne, then Gobi, then Joshua

    //THE VIA Series!!!!!
    //New models : C4 'Nehemia' Has SSE instead of #dnOW! newer modles will be Esther
    //             CZA is a P4 clone

    /************************************************************************************************/
    




//  I'm not sure about the CNs
//  {"RiseRiseRise", 5, 0, ?, 0, "Rise mP6 iDragon '6401?' (Model 0)"}, //0.25
//  {"RiseRiseRise", 5, 0, 4, 0, "Rise mP6 iDragon '6401?' (Model 0)"}, //0.25
//  {"RiseRiseRise", 5, 1, ?, 0, "Rise mP6 iDragon 'Kirin?' (Model 1)"},
//  {"RiseRiseRise", 5, 2, ?, 0, "Rise mP6 iDragon 'Lynx?' (Model 2)"}, //0.18
//  {"RiseRiseRise", 5, 8, ?, 0, "Rise mP6 iDragon II"},
//  {"RiseRiseRise", 5, 9, ?, 0, "Rise mP6 iDragon II"},
//   Rise Tiger = MMX+SSE Unknown Nmae


#endif /* 0 */


typedef struct
{
    bool    pCertified;
    string  pName;

    unt32   vFamily;
    unt32   vModel;
    unt32   vStepping;
    unt32   vType;
    unt32   vBrand;
    char    vVendor[13];
    string  vName;

    bool    iFloatingPoint;
    bool    iTranscedental;
    bool    iCompareExchange64;
    bool    iConditionalMove;
    bool    iCLFLUSH;
    bool    iMMX;
    bool    iSSE;
    bool    iSSE2;
    bool    iSSE3;
    bool    iMonitor;
    bool    iFastSystemCall;
    bool    iFXSR;

    bool    fVirtualModeExtensions;
    bool    fDebuggingExtensions;
    bool    fPageSizeExtensions;
    bool    fTimeStampCounter;
    bool    fModelSpecificRegisters;
    bool    fPhysicalAddressExtension;
    bool    fMachineCheckException;
    bool    fLocalAPIC;
    bool    fMemoryTypeRangeRegisters;
    bool    fPageGlobalEnable;
    bool    fMachineCheckArchitecture;
    bool    fPageAttributeTable;
    bool    fPageSizeExtension;
    bool    fProcessorSerialNumber;
    bool    fDebugStore;
    bool    fACPI;
    bool    fSelfSnoop;
    bool    fHyperThreading;
    bool    fThermalMonitor;
    bool    fIA64;
    bool    fSignalBreakOnFERR;
    bool    fQualifiedDebugStore;
    bool    fThermalMonitor2;
    bool    fContextID;

    unt32   cLineSize;

    unt32   cL1CodeCacheSize;
    unt32   cL1CodeCacheAssociativity;
    unt32   cL1CodeCacheLineSize;
    unt32   cL1CodeCacheLinesPerTag;

    unt32   cL1DataCacheSize;
    unt32   cL1DataCacheAssociativity;
    unt32   cL1DataCacheLineSize;
    unt32   cL1DataCacheLinesPerTag;

    unt32   cL1UnifiedCacheSize;
    unt32   cL1UnifiedCacheAssociativity;
    unt32   cL1UnifiedCacheLineSize;
    unt32   cL1UnifiedCacheLinesPerTag;

    unt32   cL2UnifiedCacheSize;
    unt32   cL2UnifiedCacheAssociativity;
    unt32   cL2UnifiedCacheLineSize;
    unt32   cL2UnifiedCacheLinesPerTag;
    
    unt32   cL3UnifiedCacheSize;
    unt32   cL3UnifiedCacheAssociativity;
    unt32   cL3UnifiedCacheLineSize;
    unt32   cL3UnifiedCacheLinesPerTag;

    unt32   cL1CodeTLB4KEntries;
    int32   cL1CodeTLB4KAssociativity;

    unt32   cL1CodeTLB2MEntries;
    int32   cL1CodeTLB2MAssociativity;

    unt32   cL1CodeTLB4MEntries;
    int32   cL1CodeTLB4MAssociativity;

    unt32   cL1DataTLB4KEntries;
    int32   cL1DataTLB4KAssociativity;

    unt32   cL1DataTLB2MEntries;
    int32   cL1DataTLB2MAssocitivity;

    unt32   cL1DataTLB4MEntries;
    int32   cL1DataTLB4MAssociativity;

    unt32   cL2CodeTLB4KEntries;
    int32   cL2CodeTLB4KAssociativity;

    unt32   cL2CodeTLB2MEntries;
    int32   cL2CodeTLB2MAssociativity;

    unt32   cL2CodeTLB4MEntries;
    int32   cL2CodeTLB4MAssociativity;

    unt32   cL2DataTLB4KEntries;
    int32   cL2DataTLB4KAssociativity;

    unt32   cL2DataTLB2MEntries;
    int32   cL2DataTLB2MAssociativity;

    unt32   cL2DataTLB4MEntries;
    int32   cL2DataTLB4MAssociativity;

    unt32   cL2UnifiedTLB4KEntries;
    int32   cL2UnifiedTLB4KAssociativity;

    unt32   cL2UnifiedTLB2MEntries;
    int32   cL2UnifiedTLB2MAssociativity;

    unt32   cL2UnifiedTLB4MEntries;
    int32   cL2UnifiedTLB4MAssociativity;

    bool    cTraceCachePresent;
    unt32   cTraceCacheMicroOps;
    unt32   cTraceCacheAssociativity;
    
    unt32   uOnChipFPU;
    unt32   uLogicalProcessorCount;
    unt32   uAPICID;

    bool    rFeature10;
    bool    rFeature20;
    bool    rFeature33;
    bool    rFeature34;
    bool    rFeature37;
    bool    rFeature38;
    bool    rFeature39;
    bool    rFeature41;

    bool    rFeature42;
    bool    rFeature43;
    bool    rFeature44;
    bool    rFeature45;
    bool    rFeature46;
    bool    rFeature47;
    bool    rFeature48;
    bool    rFeature49;
    bool    rFeature50;
    bool    rFeature51;
    bool    rFeature52;
    bool    rFeature53;
    bool    rFeature54;
    bool    rFeature55;
    bool    rFeature56;
    bool    rFeature57;
    bool    rFeature58;
    bool    rFeature59;
    bool    rFeature60;
    bool    rFeature61;
    bool    rFeature62;
    bool    rFeature63;

} prcInformation;

void discardable prcInit(void);
void discardable prcIdentify(unt64 processor, prcInformation* information);
void discardable prcCPUID(unt64 processor, unt32 function, unt32* a, unt32* b, unt32* c, unt32* d);
void IdentifyIntelCache(prcInformation* information, int descriptor);
void IdentifyProcessor(prcInformation* information, int Extra);

typedef union {unsigned int d; unsigned short w[2]; unsigned char b[4];} prcIdentificationData;

void discardable prcInit(void)
{
    prcInformation information;
    prcIdentify(0, &information);
    logStatus(logSuccess);
    logSubItem("Processor #0", information.pName);
}

void discardable prcIdentify(unt64 processor, prcInformation* information)
{
    unt32   a, b, c, d;
    unt32   highestStandard, highestExtended;
    int     i, n, Extra;

    /*** 0x00000000 - Vendor **********************/
    prcCPUID(processor, 0x00000000, &a, &b, &c, &d);

    highestStandard = a;

    *((unt32*)(information->vVendor + 0)) = b;
    *((unt32*)(information->vVendor + 4)) = d;
    *((unt32*)(information->vVendor + 8)) = c;
    information->vVendor[12] = '\0';

    
    /*** 0x00000001 - Version and Features ********/
    prcCPUID(processor, 0x00000001, &a, &b, &c, &d);

    information->vStepping  = (a & 0x0000000F) >>  0;
    information->vModel     = (a & 0x000000F0) >>  4;
    information->vFamily    = (a & 0x00000F00) >>  8;
    information->vType      = (a & 0x00003000) >> 12;

    if (information->vModel  == 0xF) information->vModel  += (a & 0x000F0000) >> 16;
    if (information->vFamily == 0xF) information->vFamily += (a & 0x0FF00000) >> 20;

    information->uOnChipFPU                 = (d >>  0) & 0x00000001;
    information->fVirtualModeExtensions     = (d >>  1) & 0x00000001;
    information->fDebuggingExtensions       = (d >>  2) & 0x00000001;
    information->fPageSizeExtension         = (d >>  3) & 0x00000001;
    information->fTimeStampCounter          = (d >>  4) & 0x00000001;
    information->fModelSpecificRegisters    = (d >>  5) & 0x00000001;
    information->fPhysicalAddressExtension  = (d >>  6) & 0x00000001;
    information->fMachineCheckException     = (d >>  7) & 0x00000001;
    information->iCompareExchange64         = (d >>  8) & 0x00000001;
    information->fLocalAPIC                 = (d >>  9) & 0x00000001;
    information->rFeature10                 = (d >> 10) & 0x00000001;
    information->iFastSystemCall            = (d >> 11) & 0x00000001;
    information->fMemoryTypeRangeRegisters  = (d >> 12) & 0x00000001;
    information->fPageGlobalEnable          = (d >> 13) & 0x00000001;
    information->fMachineCheckArchitecture  = (d >> 14) & 0x00000001;
    information->iConditionalMove           = (d >> 15) & 0x00000001;
    information->fPageAttributeTable        = (d >> 16) & 0x00000001;
    information->fPageSizeExtension         = (d >> 17) & 0x00000001;
    information->fProcessorSerialNumber     = (d >> 18) & 0x00000001;
    information->iCLFLUSH                   = (d >> 19) & 0x00000001;
    information->rFeature20                 = (d >> 20) & 0x00000001;
    information->fDebugStore                = (d >> 21) & 0x00000001;
    information->fACPI                      = (d >> 22) & 0x00000001;
    information->iMMX                       = (d >> 23) & 0x00000001;
    information->iFXSR                      = (d >> 24) & 0x00000001;
    information->iSSE                       = (d >> 25) & 0x00000001;
    information->iSSE2                      = (d >> 26) & 0x00000001;
    information->fSelfSnoop                 = (d >> 27) & 0x00000001;
    information->fHyperThreading            = (d >> 28) & 0x00000001;
    information->fThermalMonitor            = (d >> 29) & 0x00000001;
    information->fIA64                      = (d >> 30) & 0x00000001;
    information->fSignalBreakOnFERR         = (d >> 31) & 0x00000001;

    information->iSSE3                      = (c >>  0) & 0x00000001;
    information->rFeature33                 = (c >>  1) & 0x00000001;
    information->rFeature34                 = (c >>  2) & 0x00000001;
    information->iMonitor                   = (c >>  3) & 0x00000001;
    information->fQualifiedDebugStore       = (c >>  4) & 0x00000001;
    information->rFeature37                 = (c >>  5) & 0x00000001;
    information->rFeature38                 = (c >>  6) & 0x00000001;
    information->rFeature39                 = (c >>  7) & 0x00000001;
    information->fThermalMonitor2           = (c >>  8) & 0x00000001;
    information->rFeature41                 = (c >>  9) & 0x00000001;
    information->fContextID                 = (c >> 10) & 0x00000001;
    information->rFeature43                 = (c >> 11) & 0x00000001;
    information->rFeature44                 = (c >> 12) & 0x00000001;
    information->rFeature45                 = (c >> 13) & 0x00000001;
    information->rFeature46                 = (c >> 14) & 0x00000001;
    information->rFeature47                 = (c >> 15) & 0x00000001;
    information->rFeature48                 = (c >> 16) & 0x00000001;
    information->rFeature49                 = (c >> 17) & 0x00000001;
    information->rFeature50                 = (c >> 18) & 0x00000001;
    information->rFeature51                 = (c >> 19) & 0x00000001;
    information->rFeature52                 = (c >> 20) & 0x00000001;
    information->rFeature53                 = (c >> 21) & 0x00000001;
    information->rFeature54                 = (c >> 22) & 0x00000001;
    information->rFeature55                 = (c >> 23) & 0x00000001;
    information->rFeature56                 = (c >> 24) & 0x00000001;
    information->rFeature57                 = (c >> 25) & 0x00000001;
    information->rFeature58                 = (c >> 26) & 0x00000001;
    information->rFeature59                 = (c >> 27) & 0x00000001;
    information->rFeature60                 = (c >> 28) & 0x00000001;
    information->rFeature61                 = (c >> 29) & 0x00000001;
    information->rFeature62                 = (c >> 30) & 0x00000001;
    information->rFeature63                 = (c >> 31) & 0x00000001;

    information->vBrand                 = (b & 0x000000FF) >>  0;
    if (information->iCLFLUSH)
        information->cLineSize              = (b & 0x0000FF00) >>  8;
    if (information->fHyperThreading)
        information->uLogicalProcessorCount = (b & 0x00FF0000) >> 16;
    if (information->vFamily >= 0xF)
        information->uAPICID                = (b & 0xFF000000) >> 24;

    /*** 0x00000002 - Cache Descriptors ***********/
    n = 1;
    
    for (i = 0; i < n; i++)
    {
        prcCPUID(processor, 0x00000002, &a, &b, &c, &d);

        n = a & 0x000000FF;

        if (!(a & 0x80000000))
        {   IdentifyIntelCache(information, (a >>  8) & 0x000000FF);
            IdentifyIntelCache(information, (a >> 16) & 0x000000FF);
            IdentifyIntelCache(information, (a >> 24) & 0x000000FF);
        }

        if (!(b & 0x80000000))
        {   IdentifyIntelCache(information, (b >>  0) & 0x000000FF);
            IdentifyIntelCache(information, (b >>  8) & 0x000000FF);
            IdentifyIntelCache(information, (b >> 16) & 0x000000FF);
            IdentifyIntelCache(information, (b >> 24) & 0x000000FF);
        }
        if (!(c & 0x80000000))
        {   IdentifyIntelCache(information, (c >>  0) & 0x000000FF);
            IdentifyIntelCache(information, (c >>  8) & 0x000000FF);
            IdentifyIntelCache(information, (c >> 16) & 0x000000FF);
            IdentifyIntelCache(information, (c >> 24) & 0x000000FF);
        }

        if (!(d & 0x80000000))
        {   IdentifyIntelCache(information, (d >>  0) & 0x000000FF);
            IdentifyIntelCache(information, (d >>  8) & 0x000000FF);
            IdentifyIntelCache(information, (d >> 16) & 0x000000FF);
            IdentifyIntelCache(information, (d >> 24) & 0x000000FF);
        }
    }

    /*** 0x00000003 - Serial Number ***************/

    /*** 0x00000004 - Cache Parameters ************/

    /*** 0x00000005 - Monitor *********************/

    // ************ THE EXTRA NUMBER ******************** //
    // Type
    // Pentium II + III     Cache
    // Pentium III + 4      Brand ID
    // Athlon               Multi Processing / Cache

    Extra = information->vType;

    if (!strcmp(information->vVendor, "GenuineIntel")
        && information->vFamily == 6
        && information->vModel >= 3
        && information->vModel <= 7)
    {
        Extra = information->cL2UnifiedCacheSize;
    }

    if (!strcmp(information->vVendor, "GenuineIntel")
        && information->vFamily == 6
        && information->vModel >= 8)
    {
        Extra = information->vBrand;
    }

    if (!strcmp(information->vVendor, "GenuineIntel")
        && information->vFamily == 0xF)
    {
        Extra = information->vBrand;
    }

    if (!strcmp(information->vVendor, "AuthenticAMD")
        && information->vFamily == 6)
    {
        Extra = 0;
    }
    
    IdentifyProcessor(information, Extra);

}

void discardable prcCPUID(unt64 processor, unt32 function, unt32* a, unt32* b, unt32* c, unt32* d)
{
    asm ("cpuid" : "=a" (*a), "=b" (*b), "=c" (*c), "=d" (*d) : "a" (function));
}

void IdentifyIntelCache(prcInformation* information, int descriptor)
{
    switch (descriptor)
    {   case 0x00: {return;
                   }
        case 0x40: {return;
                   }
        case 0x01: {information->cL1CodeTLB4KEntries = 32;
                    information->cL1CodeTLB4KAssociativity = 4;
                    return;
                   }
        case 0x02: {information->cL1CodeTLB4MEntries = 2;
                    information->cL1CodeTLB4MAssociativity = -1;
                    return;
                   }
        case 0x03: {information->cL1DataTLB4KEntries = 64;
                    information->cL1DataTLB4KAssociativity = 4;
                    return;
                   }
        case 0x04: {information->cL1DataTLB4MEntries = 8;
                    information->cL1DataTLB4MAssociativity = 4;
                    return;
                   }
        case 0x06: {information->cL1CodeCacheSize = 8;
                    information->cL1CodeCacheAssociativity = 4;
                    information->cL1CodeCacheLineSize = 32;
                    information->cL1CodeCacheLinesPerTag = -1;
                    return;
                   }
        case 0x08: {information->cL1CodeCacheSize = 16;
                    information->cL1CodeCacheAssociativity = 4;
                    information->cL1CodeCacheLineSize = 32;
                    information->cL1CodeCacheLinesPerTag = -1;
                    return;
                   }
        case 0x0A: {information->cL1DataCacheSize = 8;
                    information->cL1DataCacheAssociativity = 2;
                    information->cL1DataCacheLineSize = 32;
                    information->cL1DataCacheLinesPerTag = -1;
                    return;
                   }
        case 0x0C: {information->cL1DataCacheSize = 16;
                    information->cL1DataCacheAssociativity = 4;
                    information->cL1DataCacheLineSize = 32;
                    information->cL1DataCacheLinesPerTag = -1;
                    return;
                   }
        case 0x22: {information->cL3UnifiedCacheSize = 512;
                    information->cL3UnifiedCacheAssociativity = 4;
                    information->cL3UnifiedCacheLineSize = 64;
                    information->cL3UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x23: {information->cL3UnifiedCacheSize = 1024;
                    information->cL3UnifiedCacheAssociativity = 8;
                    information->cL3UnifiedCacheLineSize = 64;
                    information->cL3UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x25: {information->cL3UnifiedCacheSize = 2048;
                    information->cL3UnifiedCacheAssociativity = 8;
                    information->cL3UnifiedCacheLineSize = 64;
                    information->cL3UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x29: {information->cL3UnifiedCacheSize = 4096;
                    information->cL3UnifiedCacheAssociativity = 8;
                    information->cL3UnifiedCacheLineSize = 64;
                    information->cL3UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x39: {information->cL2UnifiedCacheSize = 128;
                    information->cL2UnifiedCacheAssociativity = 4;
                    information->cL2UnifiedCacheLineSize = 64;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x3B: {information->cL2UnifiedCacheSize = 128;
                    information->cL2UnifiedCacheAssociativity = 2;
                    information->cL2UnifiedCacheLineSize = 64;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x3C: {information->cL2UnifiedCacheSize = 256;
                    information->cL2UnifiedCacheAssociativity = 4;
                    information->cL2UnifiedCacheLineSize = 64;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x41: {information->cL2UnifiedCacheSize = 128;
                    information->cL2UnifiedCacheAssociativity = 4;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x42: {information->cL2UnifiedCacheSize = 256;
                    information->cL2UnifiedCacheAssociativity = 4;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x43: {information->cL2UnifiedCacheSize = 512;
                    information->cL2UnifiedCacheAssociativity = 4;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x44: {information->cL2UnifiedCacheSize = 1024;
                    information->cL2UnifiedCacheAssociativity = 4;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x45: {information->cL2UnifiedCacheSize = 2048;
                    information->cL2UnifiedCacheAssociativity = 4;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x50: {information->cL1CodeTLB4KEntries = 64;
                    information->cL1CodeTLB4KAssociativity = -1;
                    information->cL1CodeTLB2MEntries = 64;
                    information->cL1CodeTLB2MAssociativity = -1;
                    information->cL1CodeTLB4MEntries = 64;
                    information->cL1CodeTLB4MAssociativity = -1;
                    return;
                   }
        case 0x51: {information->cL1CodeTLB4KEntries = 128;
                    information->cL1CodeTLB4KAssociativity = -1;
                    information->cL1CodeTLB2MEntries = 128;
                    information->cL1CodeTLB2MAssociativity = -1;
                    information->cL1CodeTLB4MEntries = 128;
                    information->cL1CodeTLB4MAssociativity = -1;
                    return;
                   }
        case 0x52: {information->cL1CodeTLB4KEntries = 256;
                    information->cL1CodeTLB4KAssociativity = -1;
                    information->cL1CodeTLB2MEntries = 256;
                    information->cL1CodeTLB2MAssociativity = -1;
                    information->cL1CodeTLB4MEntries = 256;
                    information->cL1CodeTLB4MAssociativity = -1;
                    return;
                   }
        case 0x5B: {information->cL1DataTLB4KEntries = 64;
                    information->cL1DataTLB4KAssociativity = -1;
                    information->cL1DataTLB4MEntries = 64;
                    information->cL1DataTLB4MAssociativity = -1;
                    return;
                   }
        case 0x5C: {information->cL1DataTLB4KEntries = 128;
                    information->cL1DataTLB4KAssociativity = -1;
                    information->cL1DataTLB4MEntries = 128;
                    information->cL1DataTLB4MAssociativity = -1;
                    return;
                   }
        case 0x5D: {information->cL1DataTLB4KEntries = 256;
                    information->cL1DataTLB4KAssociativity = -1;
                    information->cL1DataTLB4MEntries = 256;
                    information->cL1DataTLB4MAssociativity = -1;
                    return;
                   }
        case 0x66: {information->cL1DataCacheSize = 8;
                    information->cL1DataCacheAssociativity = 4;
                    information->cL1DataCacheLineSize = 64;
                    information->cL1DataCacheLinesPerTag = -1;
                    return;
                   }
        case 0x67: {information->cL1DataCacheSize = 16;
                    information->cL1DataCacheAssociativity = 4;
                    information->cL1DataCacheLineSize = 64;
                    information->cL1DataCacheLinesPerTag = -1;
                    return;
                   }
        case 0x68: {information->cL1DataCacheSize = 32;
                    information->cL1DataCacheAssociativity = 4;
                    information->cL1DataCacheLineSize = 64;
                    information->cL1DataCacheLinesPerTag = -1;
                    return;
                   }
        case 0x70: {information->cTraceCacheMicroOps = 12;
                    information->cTraceCacheAssociativity = 8;
                    return;
                   }
        case 0x71: {information->cTraceCacheMicroOps = 16;
                    information->cTraceCacheAssociativity = 8;
                    return;
                   }
        case 0x72: {information->cTraceCacheMicroOps = 32;
                    information->cTraceCacheAssociativity = 8;
                    return;
                   }
        case 0x77: {information->cL1CodeCacheSize = 16;
                    information->cL1CodeCacheAssociativity = 4;
                    information->cL1CodeCacheLineSize = 64;
                    information->cL1CodeCacheLinesPerTag = -1;
                    return;
                   }
        case 0x79: {information->cL2UnifiedCacheSize = 128;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 64;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x7A: {information->cL2UnifiedCacheSize = 256;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 64;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x7B: {information->cL2UnifiedCacheSize = 512;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 64;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x7C: {information->cL2UnifiedCacheSize = 1024;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 64;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x7E: {information->cL2UnifiedCacheSize = 256;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 128;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x82: {information->cL2UnifiedCacheSize = 128;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x83: { information->cL2UnifiedCacheSize = 256;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x84: {information->cL2UnifiedCacheSize = 512;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x85: {information->cL2UnifiedCacheSize = 1024;
                    information->cL2UnifiedCacheAssociativity = 8;
                    information->cL2UnifiedCacheLineSize = 32;
                    information->cL2UnifiedCacheLinesPerTag = -1;
                    return;
                   }
        case 0x8D: {information->cL3UnifiedCacheSize = 3072;
                    information->cL3UnifiedCacheAssociativity = 12;
                    information->cL3UnifiedCacheLineSize = 128;
                    information->cL3UnifiedCacheLinesPerTag = -1;
                    return;
                   }
    }

//  printf("Unknown Intel Cache Descriptor: %x\n", CacheDescriptor);
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

//  puts("Unknown AMD Cache Descriptor");
    return -1;
}

void IdentifyProcessor(prcInformation* information, int Extra)
{
    int i;

    for (i = 0; i < (sizeof(ProcessorList) / sizeof(PROCLIST)); i++)
    {
        if (ProcessorList[i].id == 0x02000000 + (information->vFamily << 16) + (information->vModel << 8) + Extra)
        {
            information->pName = ProcessorList[i].name;
            information->pCertified = ProcessorList[i].verified;
            return;
        }
    }

    for (i = 0; i < (sizeof(ProcessorList) / sizeof(PROCLIST)); i++)
    {
        if (ProcessorList[i].id == 0x020000FF + (information->vFamily << 16) + (information->vModel << 8))
        {
            information->pName = ProcessorList[i].name;
            information->pCertified = ProcessorList[i].verified;
            return;
        }
    }

    for (i = 0; i < (sizeof(ProcessorList) / sizeof(PROCLIST)); i++)
    {
        if (ProcessorList[i].id == 0x0200FFFF + (information->vFamily << 16))
        {
            information->pName = ProcessorList[i].name;
            information->pCertified = ProcessorList[i].verified;
            return;
        }
    }

    for (i = 0; i < (sizeof(ProcessorList) / sizeof(PROCLIST)); i++)
    {
        if (ProcessorList[i].id == 0x02FFFFFF)
        {
            information->pName = ProcessorList[i].name;
            information->pCertified = ProcessorList[i].verified;
            return;
        }
    }

    information->pName = "Unknown Processor";
    information->pCertified = false;
}
