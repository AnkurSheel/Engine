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

		bool Remove(const IRigidBody * const pBody) { return RRemove(pBody, m_pRoot); }
		const cRigidBody * const Collides(cRigidBody * const pBody, std::vector<cCollisionInfo> & collisions) { return CheckLeaf(pBody, m_pRoot, collisions); }
		static unsigned int GetMaxObjects() { return m_sMaxObjects; }
		void Print() const;

	private:
		bool RInsert(IRigidBody * const pBody, cQTNode * const pNode);
		bool RRemove(const IRigidBody * const pBody, cQTNode * const pNode);
		const cRigidBody * const CheckLeaf(cRigidBody * const pBody,
			const cQTNode * const pNode, std::vector<cCollisionInfo> & collisions);
		void RPrintNode(const cQTNode * const  pNode) const;

	private:
		static unsigned int m_sMaxObjects;
		const unsigned int m_MaxDepth;
		cQTNode	*	m_pRoot;
		std::vector<const IRigidBody * const> m_Items; ;
	};
}
#endif //QuadTree_h
