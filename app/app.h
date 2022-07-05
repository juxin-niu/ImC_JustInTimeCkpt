

#ifndef APPS_APP_H_
#define APPS_APP_H_

#include <ImC/nv.h>
#include <stdint.h>

void AR_main();
void BC_main();
void CEM_main();
void CRC_main();
void CUCKOO_main();
void DIJKSTRA_main();
void RSA_main();
void SORT_main();

typedef void (*TASKMAIN)();

extern __nv uint8_t data_consistency_error_flag;

#endif /* APPS_APP_H_ */
