// *****************************************************************************
//  Physics version:  1.0   Ankur Sheel  date: 2013/06/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef Physics_h
#define Physics_h

#include "Physics.hxx"

namespace Utilities
{
	class IXMLNode;
}

namespace Physics
{
	struct stMaterialData;
	class cQuadTree;
	class cRigidBody;
}

namespace Physics
{
	class cPhysics
		: public IPhysics
	{
	public:
		cPhysics();
		~cPhysics();
		static stMaterialData LookUpMaterialData(const Base::cString & materialName);
		static float GetGravity();

	private:
		void VInitialize(const Base::cString & FileName);
		void VUpdate(const float DeltaTime);
		IRigidBody * const VAddRigidBody(const int ID, shared_ptr<const stRigidBodyDef> pDef);
		void VRemoveRigidBody(const int ID);
		void VOnRigidBodyAdded(const int ID);
		cRigidBody* FindRigidBody(const int ID) const;
		void InternalStep();
		void LoadMaterialData(shared_ptr<Utilities::IXMLNode> pParentNode);
		void CreateQuadTree(shared_ptr<Utilities::IXMLNode> pParentNode);
		const CollisionPairs & VGetCollsionPairs() const { return m_CollisionPairs; }

	private:
		typedef std::map<int, cRigidBody * const > RigidBodyMap;
		typedef std::map<unsigned long, stMaterialData> MaterialMap;
		
		static cPhysics *	s_pPhysics;	/*!< static object of this class */
		float				m_Gravity;
		float				m_TimeStep;
		float				m_Accumalator;
		cQuadTree *			m_pQuadTree;		
		RigidBodyMap		m_RigidBodyMap;
		MaterialMap			m_MaterialMap;
		CollisionPairs		m_CollisionPairs;
		bool				m_UseQuadTree;

	private:
		friend static IPhysics * IPhysics::GetInstance();
		friend static void IPhysics::Destroy();
	};
}
#endif //Physics_hxx