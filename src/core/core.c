#include "compiler.c"

#include "rtl.c"
#include "log.c"
#include "debug.c"

#include "system.c"
#include "processor.c"
#include "memory.c"
#include "signal.c"

void sigSwitch(void);

/* :: TEMPORARY :: BEGIN :: */
    void task1(void);
    void task2(void);
    void task3(void);
    void task4(void);
    void task5(void);
    void task6(void);
    void task7(void);
    void task8(void);
    void task9(void);
    void task10(void);


    struct
    {
        unsigned volatile eax;
        unsigned volatile ebx;
        unsigned volatile ecx;
        unsigned volatile edx;
        unsigned volatile esi;
        unsigned volatile edi;
        unsigned volatile ebp;
        unsigned volatile esp;
        unsigned volatile efl;
        unsigned volatile eip;
        unsigned volatile stack[256];
    } task[11];

        unsigned volatile eax;
        unsigned volatile ebx;
        unsigned volatile ecx;
        unsigned volatile edx;
        unsigned volatile esi;
        unsigned volatile edi;
        unsigned volatile ebp;
        unsigned volatile esp;
        unsigned volatile efl;
        unsigned volatile eip;

    unsigned volatile currentTask;
/* :: TEMOPRARY ::  END  :: */

int main(void)
{
    //char buffer[20];
    unsigned stop, time, i;
    
    /* :: TEMPORARY :: BEGIN :: */
        logStatus(logSuccess);
    /* :: TEMOPRARY ::  END  :: */

    /* Initialize System Management */
        logItem("Initializing System Management");
        sysInit();
        logStatus(logSuccess);

    /* Initialize Processor Management */
        logItem("Initializing Processor Management");
        prcInit();
        logStatus(logSuccess);

    /* Initialize Signal Management */
        logItem("Initializing Signal Management");
        sigInit();
        logStatus(logSuccess);
        
    /* Initialize Memory Management */
        logItem("Initializing Memory Management");
        mmInit();
        logStatus(logSuccess);

    /* :: TEMPORARY :: BEGIN :: */
        logNote("The following parameters were set at compile time!");
        logSubItem("Physical Memory", "16378 kB");
        logSubItem("Reserved Memory", "1024 kB");

        for (i = 1; i < 11; i++)
        {   task[i].eax = i+1;
            task[i].ebx = i+1;
            task[i].ecx = i+1;
            task[i].edx = i+1;
            task[i].esi = i+1;
            task[i].edi = i+1;
            task[i].ebp = (unsigned)(task[i].stack)+256*4-1;
            task[i].esp = (unsigned)(task[i].stack)+256*4-1;
            task[i].efl = 0x00000200;       //IOPL = 0 / IF = 1
        }

        task[1].eip = (unsigned)(task1);
        task[2].eip = (unsigned)(task2);
        task[3].eip = (unsigned)(task3);
        task[4].eip = (unsigned)(task4);
        task[5].eip = (unsigned)(task5);
        task[6].eip = (unsigned)(task6);
        task[7].eip = (unsigned)(task7);
        task[8].eip = (unsigned)(task8);
        task[9].eip = (unsigned)(task9);
        task[10].eip = (unsigned)(task10);
                
        for (i = 0; i < 256; i ++)
        {
            task[1].stack[i] = '1111';
            task[2].stack[i] = '2222';
            task[3].stack[i] = '3333';
            task[4].stack[i] = '4444';
            task[5].stack[i] = '5555';
            task[6].stack[i] = '6666';
            task[7].stack[i] = '7777';
            task[8].stack[i] = '8888';
            task[9].stack[i] = '9999';
            task[10].stack[i] = 'AAAA';
        }
        
        currentTask = 0;

        asm ("sti");
        for (;;) asm volatile ("hlt");
    /* :: TEMOPRARY ::  END  :: */

}

/* :: TEMPORARY :: BEGIN :: */
void sigSwitch(void)
{
    char s[20];

 //   itoa(task[currentTask].eip, s, 16);
 //   logSubItem("FROM", s);
    
    task[currentTask].eax = eax;
    task[currentTask].ebx = ebx;
    task[currentTask].ecx = ecx;
    task[currentTask].edx = edx;
    task[currentTask].edi = edi;
    task[currentTask].esi = esi;
    task[currentTask].ebp = ebp;
    task[currentTask].esp = esp;
    task[currentTask].eip = eip;
    task[currentTask].efl = efl;

    currentTask++;
    if (currentTask > 10) currentTask = 1;

//    itoa(task[currentTask].eip, s, 16);
//    logSubItem("TO", s);

    eax = task[currentTask].eax;
    ebx = task[currentTask].ebx;
    ecx = task[currentTask].ecx;
    edx = task[currentTask].edx;
    edi = task[currentTask].edi;
    esi = task[currentTask].esi;
    ebp = task[currentTask].ebp;
    esp = task[currentTask].esp;
    eip = task[currentTask].eip;
    efl = task[currentTask].efl;

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void task1(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(2, 4, s);
    }
}

void task2(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(3, 4, s);
    }
}

void task3(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(4, 4, s);
    }
}

void task4(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(5, 4, s);
    }
}

void task5(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(6, 4, s);
    }
}

void task6(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(7, 4, s);
    }
}

void task7(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(8, 4, s);
    }
}

void task8(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(9, 4, s);
    }
}

void task9(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(10, 4, s);
    }
}

void task10(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(11, 4, s);
    }
}
/* :: TEMOPRARY ::  END  :: */
