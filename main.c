#include <ImC/nv.h>
#include <ImC/target_spec.h>
#include <ImC/target.h>
#include <ImC/analysis/hamming8.h>
#include <ImC/analysis/uart2target.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int main()
{
    power_on_init();
    clock_sys_init();
    dma_init();
    uart2target_init();


    while (1) {}
}
