//  *******************************************************************************************************************
//  LabelControl   version:  1.0   Ankur Sheel  date: 2011/11/22
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef LabelControl_h__
#define LabelControl_h__

#include "BaseControl.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace Graphics
{
	class IMyFont;
	class ISentence;
}

namespace Graphics
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Class Declaration for a Label UI Control
	///
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cLabelControl
		: public cBaseControl
	{
	public:
		static Base::cHashedString	GetName()  {return m_Name; }

	private:
		cLabelControl();
		~cLabelControl();
		void VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Initializes the label control as per the parameters
		///
		/// @param[in] def The parameter definition to create a label control
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void Initialize(const cLabelControlDef & def);
		void VRender(const ICamera * const pCamera);
		void VSetAbsolutePosition();
		void VSetText(const Base::cString & strText);
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		void VCleanup();

	private:
		ISentence *		m_pSentence;	/// The text/sentence of the label.
		static Base::cHashedString	m_Name;	/// The control name

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();

		friend class IBaseControl;
	};
}
#endif // LabelControl_h__