/********************************************************************
	created:	2011/03/23
	created:	23:3:2011   11:06
	filename: 	C:\tuango\trunk\mtk\vre\Tuangou\vaf\common\CVXmlConfig.h
	file path:	C:\tuango\trunk\mtk\vre\Tuangou\vaf\common
	file base:	CVXmlConfig
	file ext:	h
	author:		jack
	
	purpose:	
*********************************************************************/
#ifndef __CVXmlConfig_h__
#define __CVXmlConfig_h__

#include "CVFile.h"

class CVXmlConfig
{
public:
	CVXmlConfig();
	~CVXmlConfig();

	//return a new CVString, you must delete by yourself;
	CVString* readValue(char* label);
	BOOL writeValue(char* label, char* value);
	BOOL modifyValue(char* label, char* value);

private:
	CVString* xml_parser_data(char* data, char* label);
	char* read(void);
	BOOL write(char* data);
protected:
	CVFile* f;
};

#endif // __CVXmlConfig_h__