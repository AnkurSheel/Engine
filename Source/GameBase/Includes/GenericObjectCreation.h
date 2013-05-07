// *****************************************************************************
//  GenericObjectCreation version:  1.0   Ankur Sheel  date: 2013/05/07
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef GenericObjectCreation_h__
#define GenericObjectCreation_h__

namespace GameBase
{
	template <class BaseType, class SubType>
	BaseType * GenericObjectCreationFunction() 
	{ 
		return DEBUG_NEW SubType; 
	}

	template <class BaseClass, class IdType>
	class GenericObjectFactory
	{
		typedef BaseClass* (*ObjectCreationFunction)(void);
		std::map<IdType, ObjectCreationFunction> m_creationFunctions;

	public:
		template <class SubClass>
		bool Register(IdType id)
		{
			auto findIt = m_creationFunctions.find(id);
			if (findIt == m_creationFunctions.end())
			{
				m_creationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>; 
				return true;
			}
			return false;
		}

		BaseClass * Create(IdType id)
		{
			auto findIt = m_creationFunctions.find(id);
			if (findIt != m_creationFunctions.end())
			{
				ObjectCreationFunction pFunc = findIt->second;
				return pFunc();
			}

			return NULL;
		}
	};
}
#endif // GenericObjectCreation
