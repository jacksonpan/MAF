/********************************************************************
	created:	2011/03/23
	created:	23:3:2011   11:07
	filename: 	C:\tuango\trunk\mtk\vre\Tuangou\vaf\common\CVXmlConfig.cpp
	file path:	C:\tuango\trunk\mtk\vre\Tuangou\vaf\common
	file base:	CVXmlConfig
	file ext:	cpp
	author:		jack
	
	purpose:	
*********************************************************************/
#include "CVXmlConfig.h"
#include "CVPath.h"
#include "../../Common/exml.h"

#define XML_CONFIG_HEADER "<?xml version=\"1.0\" encoding=\"UTF-8\"?><top></top>"
#define XML_CONFIG_FILE_NAME	"CVXmlConfig.cache"
#define XML_CONFIG_TOP_VALUE		"<top>%s</top>"
#define XML_CONFIG_LABEL_VALUE		"<%s>%s</%s>"

CVXmlConfig::CVXmlConfig()
{
	CVPath* path = new CVPath();
	CVString p = path->getCurrentVRESavePath();
	p += XML_CONFIG_FILE_NAME;
	f = new CVFile();
	f->SetPath(p.C_Str());
	if(f->CheckFileExist() == false)
	{
		f->Create();
		f->SetType(FILE_WRITE);
		CVString data = XML_CONFIG_HEADER;
		f->WriteFast(data.C_Str());
	}

	if(path)
	{
		delete path;
		path = NULL;
	}
}

CVXmlConfig::~CVXmlConfig()
{
	if(f)
	{
		f->Close();
		delete f;
		f = NULL;
	}
}

CVString* CVXmlConfig::readValue( char* label )
{
	char* s = read();
	if(s == NULL)
	{
		return NULL;
	}
	CVString* ret = xml_parser_data(s, label);
	delete s;
	s = NULL;
	return ret;
}

BOOL CVXmlConfig::writeValue( char* label, char* value )
{
	CVString t(255);
	sprintf(t.C_Str(), XML_CONFIG_LABEL_VALUE, label, value, label);
	return write(t.C_Str());
}

char* CVXmlConfig::read( void )
{
	return f->ReadFast();
}

BOOL CVXmlConfig::write( char* data )
{
	char* dd = read();
	if(dd == NULL)
	{
		return FALSE;
	}
	CVString t = dd;
	t += data;
	delete dd;
	dd = NULL;
	f->SetType(FILE_WRITE);
	if(f->WriteFast(t.C_Str()) == true)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CVString* CVXmlConfig::xml_parser_data( char* data, char* label )
{
	struct exml_node *node_top = NULL;
	struct exml_node *start = NULL;
	node_top = exml_load_string(data);
	start = node_top->child;
	while(start)
	{
		if(strcmp(start->name, label) == 0)
		{
			CVString* t = new CVString();
			*t = start->value;
			exml_delete(node_top);
			return t;
		}
		start = start->next;
	}
	exml_delete(node_top);
	return NULL;
}

BOOL CVXmlConfig::modifyValue( char* label, char* value )
{
	return TRUE;
}
