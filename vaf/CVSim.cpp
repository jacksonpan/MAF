/********************************************************************
	created:	2011/04/01
	created:	1:4:2011   14:27
	filename: 	C:\tuango\trunk\mtk\vre\Tuangou\vaf\vaf\CVSim.cpp
	file path:	C:\tuango\trunk\mtk\vre\Tuangou\vaf\vaf
	file base:	CVSim
	file ext:	cpp
	author:		jack
	
	purpose:	
*********************************************************************/
#include "CVSim.h"

CVSim::CVSim()
{
	
}

CVSim::~CVSim()
{
	
}

BOOL CVSim::isHasSim( void )
{
	return vaf_has_sim_card();
}

BOOL CVSim::isFlyMode( void )
{
	if(vaf_sim_card_count() == 99)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int CVSim::getSimCount( void )
{
	switch(vaf_sim_card_count())
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 2;
	default:
		return -1;
	}
}

BOOL CVSim::setActiveSim( int sim )
{
	return vaf_set_active_sim_card(sim);
}

CVString CVSim::getActiveSimIMEI( void )
{
	CVString t = vaf_get_imei();
	return t;
}

CVString CVSim::getActiveSimIMSI( void )
{
	CVString t = vaf_get_imsi();
	return t;
}
