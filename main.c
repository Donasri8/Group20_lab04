#include <stdint.h>
#define SYSCTL_RCGCGPIO_R   (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_PRGPIO_R     (*((volatile uint32_t *)0x400FEA08))
#define GPIO_PORTF_LOCK_R   (*((volatile uint32_t *)0x40025520))
#define GPIO_PORTF_CR_R     (*((volatile uint32_t *)0x40025524))
#define GPIO_PORTF_DIR_R    (*((volatile uint32_t *)0x40025400))
#define GPIO_PORTF_DEN_R    (*((volatile uint32_t *)0x4002551C))
#define GPIO_PORTF_PUR_R    (*((volatile uint32_t *)0x40025510))
#define GPIO_PORTF_DATA_R   (*((volatile uint32_t *)0x400253FC))
#define RED_LED (1U << 1)
#define SW2 (1U << 0)
#define PORTF_CLK 0x20
#define GPIO_LOCK_KEY 0x4C4F434B

int main(void)
{
    SYSCTL_RCGCGPIO_R |= PORTF_CLK;
    while ((SYSCTL_PRGPIO_R & PORTF_CLK) == 0);
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R |= (RED_LED | SW2);
    GPIO_PORTF_DIR_R |= RED_LED;
    GPIO_PORTF_DIR_R &= ~SW2;
    GPIO_PORTF_DEN_R |= (RED_LED | SW2);
    GPIO_PORTF_PUR_R |= SW2;

    while (1) {
        if ((GPIO_PORTF_DATA_R & SW2) == 0) {
            GPIO_PORTF_DATA_R |= RED_LED;
        } else {
            GPIO_PORTF_DATA_R &= ~RED_LED;
        }
    }
}
