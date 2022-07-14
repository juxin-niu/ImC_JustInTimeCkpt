#include <app/app_api.h>
#include <app/app_global.h>

__nv uint16_t SW_Results;
__nv uint16_t cnt;

void CRC_main()
{

    cnt = 0;
    SW_Results = CRC_INIT;

    run:
    SW_Results = CRCheck_CCITT_Update(SW_Results, CRC_Input[cnt] & 0xFF);
    SW_Results = CRCheck_CCITT_Update(SW_Results, (CRC_Input[cnt] >> 8) & 0xFF);
    ++cnt;

    if(cnt < CRC_LENGTH)
        goto run;

    return;
}
