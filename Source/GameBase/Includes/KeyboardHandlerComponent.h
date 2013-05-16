// *****************************************************************************
//  KeyboardHandlerComponent version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef KeyboardHandlerComponent_h__
#define KeyboardHandlerComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"

namespace GameBase
{
	class cKeyboardHandlerComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API cKeyboardHandlerComponent();
		GAMEBASE_API ~cKeyboardHandlerComponent();
		GAMEBASE_API void VInitialize(const Utilities::IXMLNode * const pXMLNode);
		GAMEBASE_API void VCleanup();
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }
		void Update();

	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		static Base::cHashedString	m_Name;	///< The component name
	};
}
#endif // KeyboardHandlerComponent_h__
