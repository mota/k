#include "isr.h"
#include "video.h"
#include "kheap.h"
#include "allocator.h"

#include "c/string.h"

/*
 * This is the entry point of the kernel
 * we must never return from this function
 */
extern "C"
void
_cppstart(void)
{
    video               screen;
    memory::info        info(AVAILABLE_MEMORY MEGABYTES, 2 MEGABYTES, memory::pml4, memory::pdp, memory::pd);

    screen << "Initializing kernel heap ...";
    kheap::brk          brk(info);
    screen << " ok" << std::endl;

    screen << "Initializing allocator ...";
    allocator           kmemalloc(brk);
    screen << " ok" << std::endl;

    screen << "Loading IDT ...";
    _isr.setup();
    screen << " ok" << std::endl;

    for(;;);
}
