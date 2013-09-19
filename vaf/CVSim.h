/********************************************************************
	created:	2011/04/01
	created:	1:4:2011   14:28
	filename: 	C:\tuango\trunk\mtk\vre\Tuangou\vaf\vaf\CVSim.h
	file path:	C:\tuango\trunk\mtk\vre\Tuangou\vaf\vaf
	file base:	CVSim
	file ext:	h
	author:		jack
	
	purpose:	
*********************************************************************/
#ifndef __CVSim_h__
#define __CVSim_h__
#include "vaf_include.h"
#include "CVString.h"

#define	CVSIM_NO			VM_SIM_NO		/*无SIM卡*/
#define CVSIM_SIM1			VM_SIM_SIM1		/*SIM1卡*/
#define CVSIM_SIM2			VM_SIM_SIM2		/*SIM2卡*/

class CVSim
{
public:
	CVSim();
	~CVSim();

	static BOOL isHasSim(void);
	static BOOL isFlyMode(void);
	//@return  当前卡的数量,0=无卡，1=有一张卡，2=有两张卡
	static int getSimCount(void);

	BOOL setActiveSim(int sim);
	CVString getActiveSimIMEI(void);
	CVString getActiveSimIMSI(void);
private:
protected:
};

#endif // __CVSim_h__
