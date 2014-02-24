//  *******************************************************************************************************************
//  XMLNode   version:  1.0   Ankur Sheel  date: 2013/05/02
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#include "stdafx.h"
#include "XMLNode.h"
#include "TinyXml\tinyxml2.h"

using namespace tinyxml2;
using namespace Base;
using namespace Utilities;

//  *******************************************************************************************************************
cXMLNode::cXMLNode()
: m_pDoc(NULL)
, m_pElement(NULL)
{
}

//  *******************************************************************************************************************
cXMLNode::~cXMLNode()
{
	m_ChildNodes.clear();
	SafeDelete(&m_pDoc);
	m_pElement = NULL;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> cXMLNode::InitializeForSave(const cString & RootName,
	const cString & StyleSheetPath)
{
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());
	pNode->m_pDoc = DEBUG_NEW XMLDocument();

	pNode->m_pDoc->InsertEndChild(pNode->m_pDoc->NewDeclaration(NULL));
	
	if (!StyleSheetPath.IsEmpty())
	{
		cString str = "xml-stylesheet type=\"text/xsl\" href=\"" + StyleSheetPath + "\"";
		pNode->m_pDoc->InsertEndChild(pNode->m_pDoc->NewDeclaration(str.GetData()));
	}
	pNode->m_pElement = pNode->m_pDoc->NewElement(RootName.GetData());  
	pNode->m_pDoc->InsertEndChild(pNode->m_pElement);

	return pNode;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> cXMLNode::Load(const cString & FilePath)
{
	Log_Write(ILogger::LT_DEBUG, 3, "loading XML file " + FilePath);
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());

	pNode->m_pDoc = DEBUG_NEW XMLDocument();
	if (pNode->m_pDoc->LoadFile(FilePath.GetData()) != XML_NO_ERROR)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not load XML file " + FilePath);
		return NULL;
	}

	pNode->m_pElement = pNode->m_pDoc->FirstChildElement();

	pNode->AddChildElements();
	return pNode;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> cXMLNode::Parse(const cString & XML,
	const unsigned int Size)
{
	Log_Write(ILogger::LT_DEBUG, 3, "Parsing XML file ");
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());

	pNode->m_pDoc = DEBUG_NEW XMLDocument();
	if (pNode->m_pDoc->Parse(XML.GetData(), Size) != XML_NO_ERROR)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not parse XML file: " + 
			cString(pNode->m_pDoc->GetErrorStr1()) + ": " + 
			cString(pNode->m_pDoc->GetErrorStr2()));
		return NULL;
	}

	pNode->m_pElement = pNode->m_pDoc->FirstChildElement();

	pNode->AddChildElements();
	return pNode;
}

//  *******************************************************************************************************************
void cXMLNode::VSave(const cString & FilePath)
{
	m_pDoc->SaveFile(FilePath.GetData());
}

//  *******************************************************************************************************************
const weak_ptr<IXMLNode> cXMLNode::VAddElement(const cString & ElementName,
	const cString & ElementValue)
{
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());
	pNode->m_pElement = m_pDoc->NewElement(ElementName.GetData());
	
	if (!ElementValue.IsEmpty())
	{
		XMLText * pText = m_pDoc->NewText(ElementValue.GetData());
		pNode->m_pElement->InsertEndChild(pText);
	}

	m_pElement->LinkEndChild(pNode->m_pElement);
	m_ChildNodes.push_back(pNode);
	return pNode;
}

//  *******************************************************************************************************************
void cXMLNode::VAddComment(const cString & Comment)
{
	m_pElement->InsertEndChild(m_pDoc->NewComment(Comment.GetData()));
}

//  *******************************************************************************************************************
void cXMLNode::VAddAttribute(const cString & AttributeName, 
	const cString & AttributeValue)
{
	m_pElement->SetAttribute(AttributeName.GetData(), AttributeValue.GetData());
}

//  *******************************************************************************************************************
void cXMLNode::VAddAttribute(const cString & AttributeName,
	const int AttributeValue)
{
	m_pElement->SetAttribute(AttributeName.GetData(), AttributeValue);
}

//  *******************************************************************************************************************
void cXMLNode::VAddAttribute(const cString & AttributeName, 
	const bool AttributeValue)
{
	m_pElement->SetAttribute(AttributeName.GetData(), AttributeValue);
}

//  *******************************************************************************************************************
cString cXMLNode::VGetName() const
{
	return m_pElement->Name();
}

//  *******************************************************************************************************************
cString cXMLNode::VGetNodeValue() const
{
	return (m_pElement->GetText());
}

//  *******************************************************************************************************************
cString cXMLNode::VGetNodeAttribute(const cString & AttributeName) const
{
	return m_pElement->Attribute(AttributeName.GetData());
}

//  *******************************************************************************************************************
int cXMLNode::VGetNodeAttributeAsInt(const cString & AttributeName) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<int> val = AttributeValue.ToInt();
	if(val.IsInvalid())
	{
		Log_Write(ILogger::LT_WARNING, 2, "Error in getting " + AttributeName + " attribute as int in " + m_pElement->Name());
		return 0;
	}
	return *val;
}

//  *******************************************************************************************************************
bool cXMLNode::VGetNodeAttributeAsBool(const cString & AttributeName) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<bool> val = AttributeValue.ToBool();
	if(val.IsInvalid())
	{
		Log_Write(ILogger::LT_WARNING, 2, "Error in getting " + AttributeName + " attribute as int in " + m_pElement->Name());
		return false;
	}
	return *val;
}


//  *******************************************************************************************************************
tOptional<float> cXMLNode::VGetNodeAttributeAsFloat(const cString & AttributeName) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<float> val = AttributeValue.ToFloat();
	if(val.IsInvalid())
	{
		Log_Write(ILogger::LT_WARNING, 2, "Error in getting " + AttributeName + " attribute as int in " + m_pElement->Name());
	}
	return val;
}

//  *******************************************************************************************************************
float cXMLNode::VGetNodeAttributeAsFloat(const cString & AttributeName,
	const float DefaultValue) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<float> val = AttributeValue.ToFloat();
	if(val.IsInvalid())
	{
		Log_Write(ILogger::LT_WARNING, 2, "Error in getting " + AttributeName + " attribute as int in " + m_pElement->Name());
		return DefaultValue;
	}
	return *val;
}

//  *******************************************************************************************************************
void cXMLNode::AddChildElements()
{
	XMLElement * pElement = m_pElement->FirstChildElement();

	while(pElement)
	{
		const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());
		pNode->m_pElement = pElement;

		m_ChildNodes.push_back(pNode);	
		pNode->AddChildElements();
		pElement = pElement->NextSiblingElement();
	}
}

//  *******************************************************************************************************************
void cXMLNode::VGetChildren(XMLNodeList & ChildrenList) const
{
	ChildrenList = m_ChildNodes;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> cXMLNode::VGetChild(const cString & Name) const
{
	shared_ptr<IXMLNode> pNode;
	XMLNodeList::const_iterator Iter;
	for(Iter = m_ChildNodes.begin(); Iter != m_ChildNodes.end(); Iter++)
	{
		pNode = (*Iter);
		if(Name.CompareInsensitive(pNode->VGetName()) == true)
		{
			return pNode;
		}
	}
	return NULL;
}

//  *******************************************************************************************************************
cString cXMLNode::VGetChildValue(const cString & Name) const
{
	cString value;
	shared_ptr<IXMLNode> pNode(VGetChild(Name));
	if(pNode != NULL)
	{
		value = pNode->VGetNodeValue();
	}
	return value;
}

//  *******************************************************************************************************************
Base::tOptional<int> cXMLNode::VGetChildValueAsInt(const Base::cString & Name) const
{
	cString Value = VGetChildValue(Name);
	tOptional<int> val = Value.ToInt();
	if(val.IsInvalid())
	{
		Log_Write(ILogger::LT_WARNING, 2, "Error in getting " + Name + " as int in " + m_pElement->Name());
	}
	return val;
}

//  *******************************************************************************************************************
int cXMLNode::VGetChildValueAsInt(const Base::cString & Name, const int DefaultValue) const
{
	cString Value = VGetChildValue(Name);
	tOptional<int> val = VGetChildValueAsInt(Name);
	if(val.IsInvalid())
	{
		return DefaultValue;
	}
	return *val;
}

//  *******************************************************************************************************************
tOptional<float> cXMLNode::VGetChildValueAsFloat(const Base::cString & Name) const 
{
	cString Value = VGetChildValue(Name);
	tOptional<float> val = Value.ToFloat();
	if(val.IsInvalid())
	{
		Log_Write(ILogger::LT_WARNING, 2, "Error in getting " + Name + " as float in " + m_pElement->Name());
	}
	return val;
}

//  *******************************************************************************************************************
float cXMLNode::VGetChildValueAsFloat(const Base::cString & Name, const float DefaultValue) const
{
	tOptional<float> val = VGetChildValueAsFloat(Name);
	if(val.IsInvalid())
	{
		return DefaultValue;
	}
	return *val;
}

//  *******************************************************************************************************************
Base::tOptional<bool> cXMLNode::VGetChildValueAsBool(const cString & Name) const
{
	cString Value = VGetChildValue(Name);
	tOptional<bool> val = Value.ToBool();
	if(val.IsInvalid())
	{
		Log_Write(ILogger::LT_WARNING, 2, "Error in getting " + Name + " as bool in " + m_pElement->Name());
	}
	return val;
}

//  *******************************************************************************************************************
bool cXMLNode::VGetChildValueAsBool(const cString & Name, const bool DefaultValue) const
{
	tOptional<bool> val = VGetChildValueAsBool(Name);
	if(val.IsInvalid())
	{
		return DefaultValue;
	}
	return *val;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> IXMLNode::InitializeForSave(const cString & RootName,
	const cString & StyleSheetPath)
{
	return cXMLNode::InitializeForSave(RootName, StyleSheetPath);
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> IXMLNode::Load(const cString & FilePath)
{
	return cXMLNode::Load(FilePath);
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> IXMLNode::Parse(const cString & XML,
	const unsigned int Size)
{
	return cXMLNode::Parse(XML, Size);
}

