#include "stdafx.h"
#include "QuadTree.h"
#include "RigidBody.h"
#include "QTNode.h"
#include "collisionInfo.h"

using namespace Physics;
using namespace Base;
using namespace std;
using namespace Utilities;

unsigned int cQuadTree::m_sMaxObjects = 8;
unsigned int cQuadTree::m_sMaxDepth= 6;

// *****************************************************************************
cQuadTree::cQuadTree(const cVector3 & maxBound)
{
	m_pRoot = DEBUG_NEW cQTNode();
	m_pRoot->CreateRect(cVector3::Zero(), maxBound);
}

// *****************************************************************************
cQuadTree::~cQuadTree()
{
	SafeDelete(&m_pRoot);
}

// *****************************************************************************
bool cQuadTree::Insert(IRigidBody * const pBody)
{
	if(RInsert(pBody, m_pRoot))
	{
		m_Items.push_back(pBody);
		return true;
	}
	return false;
}

// *****************************************************************************
void cQuadTree::OnBodyMoved(cRigidBody * const pBody)
{
	RRemove(pBody, pBody->GetNode());
	cQTNode * pParent = pBody->GetNode();
	if(pBody->GetNode()->GetParent() != NULL)
	{
		pParent = pBody->GetNode()->GetParent();
	}
	RInsert(pBody, pParent);
}

// *****************************************************************************
bool cQuadTree::RInsert(IRigidBody * const pBody,
	cQTNode * const pNode)
{
	if(pNode == NULL)
	{
		return false;
	}

	cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(pBody);
	
	if(pNode->HasChildren())
	{
		bool inserted = false;
		for(unsigned int i = 0; i < cQTNode::GetSplitSize(); i++)
		{
			cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(pBody);
			cQTNode * pChildNode = pNode->GetChild(i);
			inserted = RInsert(pBody, pChildNode);
			if(inserted)
			{
				return true;
			}
		}
		if(!inserted)
		{
			pNode->AddObject(pBody);
			return true;
		}
	}
	else
	{
		// if part of the body is on screen or if the body is completley contained by a child node add it
		if((pNode->GetParent() == NULL && pNode->CheckCollision(pRigidBody))
			|| pNode->Contains(pRigidBody))
		{
			pNode->AddObject(pBody);
			return true;
		}
		else
		{
			return false;
		}
	}

	if(pNode->GetParent() == NULL)
	{
		return false;
	}

	return RInsert(pBody, pNode->GetParent());
}

// *****************************************************************************
bool cQuadTree::RRemove(const IRigidBody * const pBody,
	cQTNode * const pNode)
{
	if(pNode == NULL)
	{
		return false;
	}

	if(pNode->RemoveObject(pBody))
	{
		return true;
	}
	else // already has children
	{
		for(unsigned int i = 0; i < cQTNode::GetSplitSize(); i++)
		{
			if(RRemove(pBody, pNode->GetChild(i)))
			{
				return true;
			}
		}
	}
	return false;
}

// *****************************************************************************
const cRigidBody * const cQuadTree::RCollides(cRigidBody * const pBody, 
	const cQTNode * const pNode, std::vector<cCollisionInfo> & collisions)
{
	if(pNode == NULL)
	{
		return false;
	}

	if(pNode->IsLeaf())
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(pBody);
		for(auto iter = pNode->GetObjects().cbegin(); 	iter != pNode->GetObjects().cend(); iter++)
		{
			cRigidBody * const pOtherRigidBody = dynamic_cast<cRigidBody * const >(*iter);
			if(pOtherRigidBody->GetInitialized())
			{
				cCollisionInfo c(pBody, pOtherRigidBody);
				c.Solve();
				if(c.GetCollided())
				{
					collisions.emplace_back(c);
				}
			}
		}
	}
	else
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(pBody);
		for(auto iter = pNode->GetObjects().cbegin(); 	iter != pNode->GetObjects().cend(); iter++)
		{
			cRigidBody * const pOtherRigidBody = dynamic_cast<cRigidBody * const >(*iter);
			if(pOtherRigidBody->GetInitialized())
			{
				cCollisionInfo c(pBody, pOtherRigidBody);
				c.Solve();
				if(c.GetCollided())
				{
					collisions.emplace_back(c);
				}
			}
		}

		for(unsigned int i = 0; i < cQTNode::GetSplitSize(); i++)
		{
			const cRigidBody * const pResult = RCollides(pBody, pNode->GetChild(i), collisions);
			if(pResult != NULL)
			{
				return pResult;
			}
		}
	}

	return NULL;
}

// *****************************************************************************
void cQuadTree::Print() const
{
	Log_Write(ILogger::LT_COMMENT, 2, cString(40, "Printing QuadTree with %d objects", m_Items.size()));
	RPrintNode(m_pRoot);
}

// *****************************************************************************
void cQuadTree::RPrintNode(const cQTNode * const  pNode) const
{
#ifdef _DEBUG
	if(pNode == NULL) 
	{
		return;
	}

	pNode->Print();

	if(pNode->HasChildren())
	{
		for(size_t i = 0; i < cQTNode::GetSplitSize(); i++)
		{
			RPrintNode(pNode->GetChild(i));
		}
	}
#endif
}
