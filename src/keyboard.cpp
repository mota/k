#include "ioapic.h"
#include "keyboard.h"
#include "isr.h"
#include "exceptions.h"
#include "video.h"

keyboard *_keyboard;

EXC_FUNC(exc_keyboard, 33)(struct exception_frame *frame)
{
    _keyboard->interrupt();
}

keyboard::keyboard(ioapic & ioapic): _ioapic(ioapic)
{
}

keyboard::~keyboard()
{
}

void
keyboard::interrupt()
{
    handle_key();
    _ioapic.get_cpu_for_irq(0).get_local_apic().send_eoi();
}

void
keyboard::handle_key()
{
    uint8_t data;
    char key;
    video screen;

    while (is_buffer_ready())
    {
        data = read_data();
        if (data < 0x80) /* Keypress */
        {
            key = keymap[data];
            if (key)
                screen << key;
            else
                screen << std::endl << (int)data;
        }
    }
}

uint8_t
keyboard::read_data()
{
    char data;

    __asm__ ("inb $0x60, %0" : "=a"(data));
    return data;
}

bool
keyboard::is_buffer_ready()
{
    char status;

    __asm__ ("inb $0x64, %0" : "=a"(status));
    return status & 0x1;
}

void
keyboard::setup()
{
    _isr.set_interrupt_gate(33, &exc_keyboard);
    _ioapic.default_redirect_irq(0, 33);
}
