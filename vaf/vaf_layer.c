#include "vaf_layer.h"

int vaf_layer[2] = {-1, -1};

int vaf_create_layers(void)
{
	int lcd_width = vaf_get_lcd_width();
	int lcd_height = vaf_get_lcd_height();
	
	if(vaf_layer[0] == -1)
	{
		vaf_layer[0] = vaf_create_layer(0, 0, lcd_width, lcd_height,-1);// V_COLOR_TRANS);
		vaf_clear_layer_bg(vaf_layer[0]);
	}
	
	if(vaf_layer[1] == -1)
	{
		vaf_layer[1] = vaf_create_layer(0, 0, lcd_width, lcd_height, V_COLOR_TRANS);
		vaf_clear_layer_bg(vaf_layer[1]);
	}
	
	return 0;
}

int vaf_delete_layers(void)
{
	VMINT ret;
	
	vaf_debug("v_graphic_delete_layer entry");
	if(vaf_layer[1] != -1)
	{
		ret = vaf_delete_layer(vaf_layer[1]);
		vaf_debug("v_graphic_delete_layer1: %d", ret);
		vaf_layer[1] = -1;
		if(ret != VM_GDI_SUCCEED)
		{
			return -1;
		}
	}
	
	if(vaf_layer[0] != -1)
	{
		ret = vaf_delete_layer(vaf_layer[0]);
		vaf_debug("v_graphic_delete_layer0: %d", ret);
		vaf_layer[0] = -1;
		if(ret != VM_GDI_SUCCEED)
		{
			return -1;
		}
	}
	
	vaf_debug("v_graphic_delete_layer end");
	return 0;
}

int* vaf_get_layers_handle(void)
{
	return vaf_layer;
}

int vaf_get_layer0_handle(void)
{
	return vaf_layer[0];
}

int vaf_get_layer1_handle(void)
{
	return vaf_layer[1];
}

unsigned char* vaf_get_layer0_buffer(void)
{
	return vaf_get_layer_buf(vaf_layer[0]);
}

unsigned char* vaf_get_layer1_buffer(void)
{
	return vaf_get_layer_buf(vaf_layer[1]);
}

