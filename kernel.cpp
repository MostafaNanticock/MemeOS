#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "io.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "speaker.h"
#include "string.h"
#include "panic.h"

extern "C" // Use C link for kernel_main

void kernel_main(void) 
{
    Terminal.Init(80, 25);
    Terminal.setColor(0x0E);
    Terminal.clear();
    Terminal.hideCursor();
    Terminal.println("Welcome to MemeOS ! (DEBUG)");
    Terminal.setColor(0x07);

    Terminal.print("Loading GDT...     ");
    GDT.load();
    Terminal.OK();

    Terminal.print("Remapping PIC...   ");
    PIC.Init();
    Terminal.OK();

    Terminal.print("Loading IDT...     ");
    IDT.load();
    Terminal.OK();

    Terminal.print("Configuring PIT... ");
    PIT.Init();
    Terminal.OK();

    asm("sti");

    Terminal.println("\n\nMemeOS> ");

    for (int i = 0; i < 3; i++) {
        PIT.delay(1000);
        Terminal.println("Delay Timeout !");
    }

    kernel_panic(0x0420, "OOPS, You just got bamboozled by the allmighty\n  R.S.O.D lmao ! ERROR: Insert stupid crash message here...");

    for (;;) {
        asm("hlt");
    }
}