#ifndef __vaf_include_h__
#define __vaf_include_h__

//you can choose your platform, but only can choose one
#define __FOR_MRE__
//#define __FOR_VRE__
#define __FOR_FACEBOOK__


#if defined(__FOR_MRE__) && defined(__FOR_VRE__)
#error	"Please turn off one"
#elif !defined(__FOR_MRE__) && !defined(__FOR_VRE__)
#error	"Please turn on one"
#endif
//#define APP_RELEASE

#define VAF_VERSION		"V0.2.2_2011.03.31"

#include "vmsys.h"
#include "vmio.h"
#include "vmgraph.h"
#include "vmchset.h"
#include "vmstdlib.h"
#include "vmlog.h"
#include "vmres.h"
#include "vmmm.h"
#include "vmhttp.h"
#include "vmtimer.h"
#include "vmtel.h"

#include "vaf_typedef.h"
#include "vaf_msgdef.h"
#include "vaf_usefulapi.h"
#include "vaf_graphicdef.h"
#include "vaf_packageapi.h"
#include "vaf_keydef.h"
#include "vaf_layer.h"
#include "vaf_core.h"
#include "vaf_font.h" 

#define VAF_API
#define V_IN
#define V_OUT

#define SIZEOFCHAR		1
#define SIZEOFWCHAR		2

#define ENABLE_LOG		1
#define UNABLE_LOG		0

#define ENABLE_MEM		1
#define UNABLE_MEM		0

#endif
