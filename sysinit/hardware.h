extern void enterPM(void);

enum cpu
{
	/* As far as I know all the non-Intel 8086, 8088, 80186 and 80286 are exactly identical to	*/
	/* the Intel versions, because they are licenced from Intel. Intel let other companies		*/
	/* manufacture their processors, beacuse they couldn't keep up the demands themself.		*/
		
	//			FMRT	  (Family / Model / Revision / Type)
	i8088	= 0x0000,	//Intel i8088 / AMD Am8088
	i8086	= 0x0001,	//Intel i8088 / AMD Am8088
	i80C88	= 0x0010,	//Intel i80C88 / AMD Am80C88 / Harris HA80C88/883 / Siemens SAB8086 / Hitachi H80C88
	i80C86	= 0x0011,	//Intel i80C88 / AMD Am80C88 / Harris HA80C86/883 / Siemens SAB8086
	V20		= 0x0100,	//NEC V20H / Sony V20H
	V30		= 0x0101,	//NEC V30H
	V25		= 0x0110,	//NEC V25
	V35		= 0x0111,	//NEC V35
	V25SG	= 0x0120,	//NEC V25 Software Guard
	V35SG	= 0x0121,	//NEC V35 Software Guard
	V40		= 0x0130,	//NEC V40 / NEC V40H / NEC V45
	V50		= 0x0131,	//NEC V50 / NEC V50H / NEC V55
	i80188	= 0x1000,
	i80186	= 0x1001,
	V25Plus	= 0x1100,	//NEC V25 Plus
	V35Plus	= 0x1101,	//NEC V35 Plus
	
	i286	= 0x2000,
	i386	= 0x3000,
	i486	= 0x4000,

	//		= 0xFFFF	//Unknown CPU
};

enum fpu
{
	//			FMRH	(Family / Model / Revision / Host)
	i8087	= 0x0000,	//Intel i8087
	i80287	= 0x2002,	//Intel i80287 / AMD Am80287 / Cyrix Cx287
	i80187	= 0x3001,	//
	i287XL	= 0x3002,	//Intel i80287XL
	i387	= 0x3003,
	
};

typedef struct
{
	unsigned code;
	char* name;
} indexstring;

static indexstring processorNames[27];
static indexstring xprocessorNames[14];

int identifyCPU(void);
int identifyCPU0(void);
int identifyCPU2(void);
unsigned identifyFPU(void);

void switchA20(void);

/*char* a20Names[] =
{
	"Standard AT (KBC)",		//This works for 99.99% of the the PCs in the world
	"HP Vectra A / A+ (KBC)",	//HP Vectras hava a 'bug' in their Keyboard Controller
	"PS/2 (I/O)",				//PS/2 have a dedicated I/O port for this hob.
	"PS/2 (BIOS)",				//PS/2s and modern computer can use the BIOS
	"XMS (DOS)"					//Try to use HIMEM.SYS as a last resort
};  */