// *****************************************************************************
//  XMLNode   version:  1.0   Ankur Sheel  date: 2013/05/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef XMLNode_hxx__
#define XMLNode_hxx__

namespace Utilities
{
	////////////////////////////////////////////////////////////////////////////
	/// @brief XML parser Interface
	/// 
	///
	////////////////////////////////////////////////////////////////////////////
	class IXMLNode
	{
	public:
		typedef std::list<const shared_ptr<IXMLNode> > XMLNodeList;

		virtual ~IXMLNode(){};
		////////////////////////////////////////////////////////////////////////
		/// @brief Creates the header XML and adds the root element so that the 
		/// file is well formed on Save.
		/// @param[in] RootName The name of the root element.
		/// @param[in] StyleSheetPath The stylesheet associated with this xml. 
		/// Can be NULL.
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API static const shared_ptr<IXMLNode> InitializeForSave(const Base::cString & RootName,
			const Base::cString & StyleSheetPath);
		////////////////////////////////////////////////////////////////////////
		/// @brief Loads the XML file
		///
		/// @param[in] FilePath The path for the XML file to be loaded.
		/// @return Pointer to the root Node if file is successfully loaded.
		/// NULL otherwise.
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API static const shared_ptr<IXMLNode> Load(const Base::cString & FilePath);
		////////////////////////////////////////////////////////////////////////
		/// @brief Parses an XML file from a character string.
		///
		/// @param[in] XML The string containing the XML content.
		/// @param[in] Size the size of the the string.
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API static const shared_ptr<IXMLNode> Parse(const Base::cString & XML,
			const unsigned int Size);
		////////////////////////////////////////////////////////////////////////
		/// @brief Saves the XML file.
		///
		/// @param[in] FilePath The path at which the XML file should be be saved.
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VSave(const Base::cString & FilePath) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Adds a child element.
		///
		/// @param[in] ElementName The name of the child element.
		/// @param[in] ElementValue The value associated with the child element.
		/// @return Pointer to the added Node.
		///
		////////////////////////////////////////////////////////////////////////
		virtual const weak_ptr<IXMLNode> VAddElement(const Base::cString & ElementName
			, const Base::cString & ElementValue) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Adds a comment.
		///
		/// @param[in] Comment The comment text.
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VAddComment(const Base::cString & Comment) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Adds an attribute.
		///
		/// @param[in] AttributeName The attribute name.
		/// @param[in] AttributeValue The value of the attribute.
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VAddAttribute(const Base::cString & AttributeName, 
			const Base::cString & AttributeValue) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Adds an integer attribute.
		///
		/// @param[in] AttributeName The attribute name.
		/// @param[in] AttributeValue The integer value of the attribute.
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VAddAttribute(const Base::cString & AttributeName,
			const int AttributeValue) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Adds a bool attribute.
		///
		/// @param[in] AttributeName The attribute name.
		/// @param[in] AttributeValue The bool value of the attribute.
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VAddAttribute(const Base::cString & AttributeName,
			const bool AttributeValue) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Returns the name of the element.
		///
		/// @return The name of the element.
		///
		////////////////////////////////////////////////////////////////////////
		virtual Base::cString VGetName() = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Returns the value of the element.
		///
		/// @return The value associated with the element.
		///
		////////////////////////////////////////////////////////////////////////
		virtual Base::cString VGetNodeValue() = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Returns The value of the attribute.
		/// 
		/// @param[in] AttributeName The attribute name.
		/// @return The value of the attribute.
		///
		////////////////////////////////////////////////////////////////////////
		virtual Base::cString VGetNodeAttribute(const Base::cString & AttributeName) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Returns The value of the attribute as an Int. If the attribute
		/// is not found returns 0.
		/// 
		/// @param[in] AttributeName The attribute name.
		/// @return The value of the attribute as an int.
		///
		////////////////////////////////////////////////////////////////////////
		virtual int VGetNodeAttributeAsInt(const Base::cString & AttributeName) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Returns The value of the attribute as an Int. If the attribute
		/// is not found returns false.
		/// 
		/// @param[in] AttributeName The attribute name.
		/// @return The value of the attribute as an int.
		///
		////////////////////////////////////////////////////////////////////////
		virtual bool VGetNodeAttributeAsBool(const Base::cString & AttributeName) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Stores all the child nodes in ChildrenList
		/// 
		/// @param[out] ChildrenList The list of all the children
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VGetChildren(XMLNodeList & ChildrenList) = 0;
		////////////////////////////////////////////////////////////////////////
		/// @brief Get the first child element with the specified name.If no child
		/// with the specified name exists, returns NULL
		/// 
		/// @param[in] Name The name of the child element.
		/// @return The first child element with the specified name. If no child
		/// with the specified name exists, returns NULL
		///
		////////////////////////////////////////////////////////////////////////
		virtual const shared_ptr<IXMLNode> VGetChild(const Base::cString & Name) const = 0;
	};
}
#endif // XMLNode_h__