// *****************************************************************************
//  QuadTree version:  1.0   Ankur Sheel  date: 2013/08/21
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef QuadTree_h
#define QuadTree_h

namespace Base
{
	class cVector3;
}

namespace Physics
{
	class cRigidBody;
	class cQTNode;
	class cCollisionInfo;
}

namespace Physics
{
	class cQuadTree
		: public Base::cNonCopyable
	{
	public:
		cQuadTree(const Base::cVector3 & maxBound);
		~cQuadTree();
		bool Insert(cRigidBody * const pBody);
		void OnBodyMoved(cRigidBody * const pBody);
		bool Remove(cRigidBody * const pBody);
		void CreateCollisionPairs(cRigidBody * const pBody,
			std::vector<cCollisionInfo> & collisions);
		void Print() const;
		static unsigned int GetMaxObjects() { return m_sMaxObjects; }
		static unsigned int GetMaxDepth() { return m_sMaxDepth; }

	private:
		bool RInsert(cRigidBody * const pBody, cQTNode * const pNode);

	private:
		static unsigned int m_sMaxObjects;
		static unsigned int m_sMaxDepth;
		unsigned int		m_NoOfItems;
		cQTNode	*			m_pRoot;
	};
}
#endif //QuadTree_h
