#include "stdafx.h"
#include "QuadTree.h"
#include "RigidBody.h"
#include "QTNode.h"
#include "collisionInfo.h"

using namespace Physics;
using namespace Base;
using namespace std;

unsigned int cQuadTree::m_sMaxObjects = 8;

// *****************************************************************************
cQuadTree::cQuadTree(const cVector3 & maxBound)
	: m_MaxDepth(6)
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
	if(pNode->IsLeaf())
	{
		// if the quad is full
		if(!pNode->AddObject(pBody, false))
		{
			if(pNode->CanSplit(m_MaxDepth))
			{
				pNode->Split();
				return RInsert(pBody, pNode);
			}
			else // force add
			{
				pNode->AddObject(pBody, true);
				pRigidBody->SetNode(pNode);
				return true;
			}
		}
		pRigidBody->SetNode(pNode);
		return true;
	}
	else // already has children
	{
		for(unsigned int i = 0; i < cQTNode::GetSplitSize(); i++)
		{
			cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(pBody);
			if(pNode->GetChild(i)->CheckCollision(pRigidBody))
			{
				return RInsert(pBody, pNode->GetChild(i));
			}
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

	if(pNode->IsLeaf())
	{
		return pNode->RemoveObject(pBody);
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
const cRigidBody * const cQuadTree::CheckLeaf(cRigidBody * const pBody, 
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
		for(unsigned int i = 0; i < cQTNode::GetSplitSize(); i++)
		{
			const cRigidBody * const pResult = CheckLeaf(pBody, pNode->GetChild(i), collisions);
			if(pResult != NULL)
			{
				return pResult;
			}
		}
	}

	return NULL;
}
