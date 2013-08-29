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
	class IRigidBody;
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
		bool Insert(IRigidBody * const pBody);
		void OnBodyMoved(cRigidBody * const pBody);

		bool Remove(IRigidBody * const pBody);
		void CreateCollisionPairs(IRigidBody * const pBody,
			std::vector<cCollisionInfo> & collisions);
		static unsigned int GetMaxObjects() { return m_sMaxObjects; }
		static unsigned int GetMaxDepth() { return m_sMaxDepth; }
		void Print() const;

	private:
		bool RInsert(IRigidBody * const pBody, cQTNode * const pNode);
		void RPrintNode(const cQTNode * const  pNode) const;

	private:
		static unsigned int m_sMaxObjects;
		static unsigned int m_sMaxDepth;
		cQTNode	*	m_pRoot;
		std::vector<const IRigidBody * const> m_Items; ;
	};
}
#endif //QuadTree_h
