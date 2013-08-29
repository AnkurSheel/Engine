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
		void AddObject(IRigidBody * const pBody);
		bool RemoveObject(IRigidBody * const pBody);
		void CreateRect(const Base::cVector3 & minBound, const Base::cVector3 & maxBound);
		bool Contains(IRigidBody * const pBody);
		void Print() const;
		cQTNode * const GetChild(unsigned int index);
        const cQTNode * const GetChild(unsigned int index) const;
		bool HasChildren() const { return !m_Children.empty(); }
		cQTNode * const GetParent() const { return m_pParent; }
		bool CheckCollision(IRigidBody * const pBody) const;
		const std::list<IRigidBody * const> & GetObjects() const { return m_Items; }
		static unsigned int	GetSplitSize() { return m_sSplitSize; }

	private:
		bool IsLeaf() const{ return m_Children.empty(); }
		void KillChildren();
		cQTNode * const GetChildQuadrant(IRigidBody * const pBody);
		bool CanSplit(const unsigned int maxDepth) { return m_Depth < maxDepth; }
		void Split();

	private:
		static const unsigned int		m_sSplitSize;
		unsigned int					m_Depth;
		cQTNode	*						m_pParent;
		IShape *						m_pRect;
		std::vector<cQTNode*>			m_Children;
		std::list<IRigidBody * const>	m_Items;
		bool							m_Full;
	};
}
#endif //QTNode_h