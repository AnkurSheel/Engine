#include "stdafx.h"
#include "QuadTree.h"
#include "RigidBody.h"
#include "QTNode.h"

using namespace Physics;
using namespace Base;
using namespace std;
using namespace Utilities;

unsigned int cQuadTree::m_sMaxObjects = 8;
unsigned int cQuadTree::m_sMaxDepth= 6;

// *****************************************************************************
cQuadTree::cQuadTree(const cVector3 & maxBound)
	: m_NoOfItems(0)
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
bool cQuadTree::Insert(cRigidBody * const pBody)
{
	m_NoOfItems++;
	return RInsert(pBody, m_pRoot);
}

// *****************************************************************************
void cQuadTree::OnBodyMoved(cRigidBody * const pBody)
{
	cQTNode * pParent = pBody->GetNode();
	if (pParent == NULL)
	{
		pParent = m_pRoot;
	}
	if(pParent->GetParent() != NULL)
	{
		pParent = pParent->GetParent();
	}
	Remove(pBody);
	RInsert(pBody, pParent);
}

// *****************************************************************************
bool cQuadTree::RInsert(cRigidBody * const pBody,
	cQTNode * const pNode)
{
	if(pNode == NULL)
	{
		return false;
	}
	// if part of the body is on screen or if the body is completely contained by a child node add it
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
bool cQuadTree::Remove(cRigidBody * const pBody)
{
	cQTNode * pNode = pBody->GetNode();
	if(pNode == NULL)
	{
		return false;
	}
	return pNode->RemoveObject(pBody);
}

// *****************************************************************************
void cQuadTree::CreateCollisionPairs(cRigidBody * const pBody,
	std::vector<cCollisionInfo> & collisions)
{
	if(m_pRoot == NULL)
	{
		return;
	}
	m_pRoot->CreateCollisionPairs(pBody, collisions);
}

// *****************************************************************************
void cQuadTree::Print() const
{
#ifdef _DEBUG
	Log_Write(ILogger::LT_COMMENT, 2, cString(40, "Printing QuadTree with %u objects", m_NoOfItems));
	m_pRoot->Print();
#endif
}