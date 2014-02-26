//  *******************************************************************************************************************
//  ButtonControl   version:  1.0   Ankur Sheel  date: 2011/11/23
//  *******************************************************************************************************************
//  purpose:
//  *******************************************************************************************************************
#ifndef ButtonControl_h__
#define ButtonControl_h__

#include "BaseControl.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace Graphics
{
	class IMyFont;
	class cLabelControl;
	class ITexture;
}

namespace Graphics
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Class Declaration for \c Button UI Control
	///
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cButtonControl
		: public cBaseControl
	{
	public:
	public:
		static Base::cHashedString	GetName()  {return m_Name; }

	private:
		cButtonControl();
		~cButtonControl();
		void VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Initializes the button control as per the parameters
		///
		/// @param[in] def The parameter definition to create a button control
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void Initialize(const cButtonControlDef & def);
		void VRender(const ICamera * const pCamera);
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VSetAbsolutePosition();
		void VSetText(const Base::cString & strText);

	private:
		shared_ptr<ITexture>	m_pDefaultTexture;	/// The texture to be used when the button is in default state.
		shared_ptr<ITexture>	m_pPressedTexture;	/// The texture to be used when the button is in pressed state.
		shared_ptr<IBaseControl>	m_pLabel;	/// The label/text associated with this button.
		bool	m_Pressed;	/// True if the button is in pressed state. False otherwise.
		static Base::cHashedString	m_Name;	///< The control name

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();

		friend class IBaseControl;

	};
}
#endif // ButtonControl_h__
