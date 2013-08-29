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
	cQTNode * pParent = pBody->GetNode();
	if(pBody->GetNode()->GetParent() != NULL)
	{
		pParent = pBody->GetNode()->GetParent();
	}
	Remove(pBody);
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

	// if part of the body is on screen or if the body is completley contained by a child node add it
	if((pNode->GetParent() == NULL && pNode->CheckCollision(pBody))
		|| pNode->Contains(pBody))
	{
		pNode->AddObject(pBody);
		return true;
	}

	if(pNode->GetParent() == NULL)
	{
		return false;
	}

	return RInsert(pBody, pNode->GetParent());
}

// *****************************************************************************
bool cQuadTree::Remove(IRigidBody * const pBody)
{
	const cRigidBody * const pRigidBody = dynamic_cast<const cRigidBody * const>(pBody);
	cQTNode * pNode = pRigidBody->GetNode();
	
	if(pNode == NULL)
	{
		return false;
	}

	return pNode->RemoveObject(pBody);
}

// *****************************************************************************
void cQuadTree::RCollides(cRigidBody * const pBody, const cQTNode * const pNode,
	std::vector<cCollisionInfo> & collisions)
{
	if(pNode == NULL)
	{
		return;
	}

	if(pNode->CheckCollision(pBody))
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
		if(pNode->HasChildren())
		{
			for(unsigned int i = 0; i < cQTNode::GetSplitSize(); i++)
			{
				RCollides(pBody, pNode->GetChild(i), collisions);
			}
		}
	}
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
