// *****************************************************************************
//  XMLNode   version:  1.0   Ankur Sheel  date: 2013/05/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef XMLNode_h__
#define XMLNode_h__

#include "XMLNode.hxx"

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
}

namespace Utilities
{
	////////////////////////////////////////////////////////////////////////////
	/// @brief XML parser Implementation
	/// 
	///
	////////////////////////////////////////////////////////////////////////////
	class cXMLNode
		: public IXMLNode
		, public Base::cNonCopyable
	{
	public:
		~cXMLNode();
		static const shared_ptr<IXMLNode> InitializeForSave(const Base::cString & RootName,
			const Base::cString & StyleSheetPath);
		static const shared_ptr<IXMLNode> Load(const Base::cString & FilePath);
		static const shared_ptr<IXMLNode> Parse(const Base::cString & XML,
			const unsigned int Size);

	private:
		cXMLNode();
		void VSave(const Base::cString & FilePath);
		const weak_ptr<IXMLNode> VAddElement(const Base::cString & ElementName,
			const Base::cString & ElementValue);
		void VAddComment(const Base::cString & Comment);
		void VAddAttribute(const Base::cString & AttributeName, 
			const Base::cString & AttributeValue);
		void VAddAttribute(const Base::cString & AttributeName,
			const int AttributeValue);
		void VAddAttribute(const Base::cString & AttributeName,
			const bool AttributeValue);
		Base::cString VGetName() const;
		Base::cString VGetNodeValue() const;
		Base::cString VGetNodeAttribute(const Base::cString & AttributeName) const;
		int VGetNodeAttributeAsInt(const Base::cString & AttributeName) const;
		bool VGetNodeAttributeAsBool(const Base::cString & AttributeName) const;
		void VGetChildren(XMLNodeList & ChildrenList) const;
		const shared_ptr<IXMLNode> VGetChild(const Base::cString & Name) const;
		////////////////////////////////////////////////////////////////////////
		/// @brief Adds all the child elements for the parent element to the
		/// child list
		/// 
		///
		////////////////////////////////////////////////////////////////////////
		void AddChildElements();
	
	private:
		tinyxml2::XMLDocument*	m_pDoc;	///< Pointer to the tinyxml2 Document. Will be NULL except for the root element.
		XMLNodeList				m_ChildNodes;	///< The list of the child elements.
		tinyxml2::XMLElement *  m_pElement;	///< The tinyxml2 element.
	};
}
#endif // XMLNode_h__