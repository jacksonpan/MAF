#ifndef __vaf_layer_h__
#define __vaf_layer_h__

#include "vaf_include.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define VAF_LAYER0		0x0000
#define VAF_LAYER1		0x0001

extern int vaf_create_layers(void);
extern int vaf_delete_layers(void);

extern int vaf_get_layer0_handle(void);
extern int vaf_get_layer1_handle(void);

extern unsigned char* vaf_get_layer0_buffer(void);
extern unsigned char* vaf_get_layer1_buffer(void);
extern int* vaf_get_layers_handle(void);



#ifdef  __cplusplus
}
#endif

#endif
