// *****************************************************************************
//  PhysicsSystem version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "PhysicsSystem.h"
#include "EntityManager.hxx"
#include "PhysicsComponent.h"
#include "TransformComponent.h"

using namespace GameBase;
using namespace Utilities;
using namespace Base;

// *****************************************************************************
cPhysicsSystem::cPhysicsSystem()
	:cProcess("PhysicsSystem")
{

}

// *****************************************************************************
cPhysicsSystem::~cPhysicsSystem()
{

}

// *****************************************************************************
void cPhysicsSystem::VUpdate(const float DeltaTime)
{
	cProcess::VUpdate(DeltaTime);

	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cPhysicsComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransformComponent * pTransform = dynamic_cast<cTransformComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransformComponent::GetName()));
		cPhysicsComponent * pPhysics = dynamic_cast<cPhysicsComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cPhysicsComponent::GetName()));
		if(!pPhysics->m_CurrentAcceleration.IsZero())
		{
			if(pTransform != NULL)
			{
				cVector3 Force;
				if(pPhysics->m_ApplyGravity)
				{
					//fy += m * 9.81;
					Force.y += 981; // cm/s
				}
				
				//fy += -1 * 0.5 * rho * C_d * A * vy * vy;
				cVector3 Distance = (pPhysics->m_CurrentVelocity * DeltaTime) + (0.5f * pPhysics->m_CurrentAcceleration * DeltaTime * DeltaTime);
				// new_ay = fy / m;
				cVector3 newAcceleration = Force;
				cVector3 avgAcceleration = 0.5f * (newAcceleration + pPhysics->m_CurrentAcceleration);
				pPhysics->m_CurrentVelocity += avgAcceleration;
				Clamp<float>(pPhysics->m_CurrentVelocity.x, -pPhysics->m_TopSpeed, pPhysics->m_TopSpeed);
				Clamp<float>(pPhysics->m_CurrentVelocity.y, -pPhysics->m_TopSpeed, pPhysics->m_TopSpeed);
				pPhysics->m_CurrentAcceleration = cVector3::Zero();
				pTransform->m_Position += Distance;
			}
		}
		if(!pPhysics->m_CurrentVelocity.IsZero())
		{
			pPhysics->m_CurrentVelocity -= pPhysics->m_CurrentVelocity * pPhysics->m_DragFactor;
		}
	}
}
