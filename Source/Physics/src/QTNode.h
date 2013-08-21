// *****************************************************************************
//  QTNode version:  1.0   Ankur Sheel  date: 2013/08/21
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef QTNode_h
#define QTNode_h

namespace Base
{
	class cVector3;
}

namespace Physics
{
	class IRigidBody;
	class IShape;
}

namespace Physics
{
	class cQTNode
		: public Base::cNonCopyable
	{
	public:
		cQTNode();
		cQTNode(const unsigned int depth);
		~cQTNode();
		bool AddObject(IRigidBody * const pBody, const bool force);
		bool RemoveObject(const IRigidBody * const pBody);
		void Split();
		bool CheckCollision(IRigidBody * const pBody);
		bool CheckCollisionWithChildren(IRigidBody * const pBody);
		void KillChildren();
		cQTNode * const GetChild(unsigned int index);
        const cQTNode * const GetChild(unsigned int index) const;
		void CreateRect(const Base::cVector3 & minBound, const Base::cVector3 & maxBound);
		bool HasChildren() const { return !m_Children.empty(); }
		bool IsLeaf() const{ return m_Children.empty(); }
		bool IsFull(){ return m_Full; }
		bool CanSplit(const unsigned int maxDepth) { return m_Depth < maxDepth; }
		cQTNode * const GetParent() const { return m_pParent; }
		const std::list<IRigidBody * const> & GetObjects() const { return m_Items; }
		static unsigned int	GetSplitSize() { return m_sSplitSize; }

	private:
		cQTNode	*				m_pParent;
		IShape *				m_pRect;
		unsigned int			m_Depth;
		static const unsigned int		m_sSplitSize;
		std::vector<cQTNode*>	m_Children;
		std::list<IRigidBody * const>	m_Items;
		bool					m_Full;
	};
}
#endif //QTNode_h