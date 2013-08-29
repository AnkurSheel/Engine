#include "stdafx.h"
#include "QTNode.h"
#include "QuadTree.h"
#include "vector3.h"
#include "Shape.hxx"
#include "RigidBody.h"
#include "collisionInfo.h"

using namespace Physics;
using namespace Base;
using namespace Utilities;

const unsigned int cQTNode::m_sSplitSize = 4;

// *****************************************************************************
cQTNode::cQTNode()
	: m_pParent(NULL)
	, m_pRect(NULL)
	, m_Depth(0)
	, m_Full(false)
{
	m_Children.reserve(m_sSplitSize);
	m_Items.clear();
}

// *****************************************************************************
cQTNode::cQTNode(const unsigned int depth)
	: m_pParent(NULL)
	, m_pRect(NULL)
	, m_Depth(depth)
	, m_Full(false)
{
	if(HasChildren())
	{
		KillChildren();
	}
	m_Items.clear();
}

// *****************************************************************************
cQTNode::~cQTNode()
{
	SafeDelete(&m_pRect);
	if(HasChildren())
	{
		for(unsigned int i = 0; i < m_sSplitSize; i++)
		{
			SafeDelete(&(m_Children[i]));
		}
	}
	m_Items.clear();
}

// *****************************************************************************
cQTNode * const cQTNode::GetChild(unsigned int index)
{
	if(IsLeaf())
	{
		return NULL;
	}
	Clamp<unsigned int>(index, 0, m_sSplitSize - 1);
	return m_Children[index];
}

// *****************************************************************************
const cQTNode * const cQTNode::GetChild(unsigned int index) const
{
	if(IsLeaf())
	{
		return NULL;
	}
	Clamp<unsigned int>(index, 0, m_sSplitSize - 1);
	return m_Children[index];
}

// *****************************************************************************
void cQTNode::AddObject(cRigidBody * const pBody)
{
	m_Items.push_back(pBody);

	pBody->SetNode(this);

	if(HasChildren())
	{
		cQTNode * pChildNode = GetChildQuadrant(pBody);
		if(pChildNode != NULL)
		{
			RemoveObject(pBody);
			pChildNode->AddObject(pBody);
		}
	}

	if(m_Full)
	{
		if(CanSplit(cQuadTree::GetMaxDepth()))
		{
			Split();

			for(auto iter = m_Items.begin(); iter != m_Items.end();)
			{
				cQTNode * pChildNode = GetChildQuadrant(*iter);
				if(pChildNode != NULL)
				{
					pChildNode->AddObject(*iter);
					iter = m_Items.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
	}
	m_Full = m_Items.size() >= cQuadTree::GetMaxObjects();
}

// *****************************************************************************
bool cQTNode::RemoveObject(cRigidBody * const pBody)
{
	for(auto iter = m_Items.begin(); iter != m_Items.end(); iter++)
	{
		if(*iter == pBody)
		{
			pBody->SetNode(NULL);
			m_Items.erase(iter);
			return true;
		}
	}
	return false;
}

// *****************************************************************************
void cQTNode::Split()
{
	if(!IsLeaf())
	{
		return;
	}

	m_Children.resize(m_sSplitSize);
	cVector3 start = m_pRect->VGetMinBound();
	cVector3 end = start + m_pRect->VGetHalfExtents();

	int depth = m_Depth + 1;

	for(unsigned int i = 0; i< m_sSplitSize; i++)
	{
		cQTNode * pCurrent = DEBUG_NEW cQTNode(depth);
		pCurrent->m_pParent = this;

		// node becomes half the size
		pCurrent->CreateRect(start, end);

		m_Children[i] = pCurrent;
		start.x += m_pRect->VGetHalfExtents().x;
		end.x += m_pRect->VGetHalfExtents().x;

		if(start.x >= m_pRect->VGetMaxBound().x)
		{
			start.x = m_pRect->VGetMinBound().x;
			end.x = start.x + m_pRect->VGetHalfExtents().x;
			start.y += m_pRect->VGetHalfExtents().y;
			end.y += m_pRect->VGetHalfExtents().y;
		}
	}
}

// *****************************************************************************
bool cQTNode::CheckCollision(cRigidBody * const pBody) const
{
	// use existing function
	cVector3 centerDelta = pBody->GetCollisionShape()->VGetCenter() - m_pRect->VGetCenter();
	cVector3 overlap = centerDelta;
	overlap.AbsTo();

	cVector3 halfExtentSum = pBody->GetCollisionShape()->VGetHalfExtents() + m_pRect->VGetHalfExtents();
	overlap = halfExtentSum - overlap;

	return (overlap.x > 0 && overlap.y > 0);
}

// *****************************************************************************
bool cQTNode::Contains(cRigidBody * const pBody)
{
	cVector3 NodeMinBounds = m_pRect->VGetMinBound();
	cVector3 NodeMaxBounds = m_pRect->VGetMaxBound();
	cVector3 BodyMinBounds = pBody->GetCollisionShape()->VGetMinBound();
	cVector3 BodyMaxBounds = pBody->GetCollisionShape()->VGetMaxBound();

	return (NodeMinBounds.x <= BodyMinBounds .x && NodeMinBounds.y <= BodyMinBounds.y
		&& NodeMaxBounds.x >= BodyMaxBounds.x && NodeMaxBounds.y >= BodyMaxBounds.y);
}

// *****************************************************************************
void cQTNode::KillChildren()
{
	for(unsigned int i = 0; i < m_sSplitSize; i++)
	{
		for(auto iter = m_Children[i]->m_Items.begin();	iter != m_Children[i]->m_Items.end(); iter++)
		{
			m_Items.push_back(*iter);
		}
		SafeDelete(&(m_Children[i]));
	}
	m_Children.clear();
}

// *****************************************************************************
void cQTNode::CreateRect(const cVector3 & minBound, const cVector3 & maxBound)
{
	m_pRect = IShape::CreateRectangleShape();
	m_pRect->VInitialize(minBound, maxBound);
}

// *****************************************************************************
void cQTNode::Print() const
{
	cString str(30, "QTNode %u ", this);
	str += cString(30, "parent (%u) ", m_pParent);
	str += cString(30, "Depth (%d) ", m_Depth);
	int children = 0;
	if(HasChildren())
	{
		children = m_Children.size();
	}
	str += cString(30, "Children (%d) ", children);
	str += cString(30, "objCount (%u) ", m_Items.size());
	str += cString(100, "rect (left: %f, right: %f, top: %f bottom: %f)", m_pRect->VGetMinBound().x, m_pRect->VGetMaxBound().x, m_pRect->VGetMinBound().y, m_pRect->VGetMaxBound().y);
	Log_Write(ILogger::LT_DEBUG, 2, str);
}

// *****************************************************************************
cQTNode * const cQTNode::GetChildQuadrant(cRigidBody * const pBody)
{
	for(unsigned int i = 0; i < cQTNode::GetSplitSize(); i++)
	{
		cQTNode * pChildNode = GetChild(i);
		if(pChildNode->Contains(pBody))
		{
			return pChildNode;
		}
	}
	return NULL;
}

// *****************************************************************************
void cQTNode::CreateCollisionPairs(cRigidBody * const pBody,
	std::vector<cCollisionInfo> & collisions)
{
	if(CheckCollision(pBody))
	{
		for(auto iter = m_Items.cbegin(); 	iter != m_Items.cend(); iter++)
		{
			cRigidBody * const pOtherRigidBody = (*iter);
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
		if(HasChildren())
		{
			for(unsigned int i = 0; i < m_sSplitSize; i++)
			{
				cQTNode * pChildNode = GetChild(i);
				pChildNode->CreateCollisionPairs(pBody, collisions);
			}
		}
	}
}
