// *****************************************************************************
//  Score   version:  1.0   Ankur Sheel  date: 2013/03/14
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Score.h"

using namespace GameBase;
using namespace Base;

// *****************************************************************************
cScore::cScore()
: m_iScore(0)
{
}

// *****************************************************************************
cScore::cScore(const cString & strPlayerName, const int iScore)
: m_strPlayerName(strPlayerName)
, m_iScore(iScore)
{
}

// *****************************************************************************
cScore::~cScore()
{
}

// *****************************************************************************
void cScore::UpdateScore(const int iDeltaValue)
{
	m_iScore += iDeltaValue;
}

// *****************************************************************************
void cScore::SetScore(const int iScore)
{
	m_iScore = iScore;
}

// *****************************************************************************
int cScore::GetScore() const
{
	return m_iScore;
}

// *****************************************************************************
Base::cString cScore::GetPlayerName() const
{
	return m_strPlayerName;
}

// *****************************************************************************
void cScore::SetPlayerName(const cString & strPlayerName)
{
	m_strPlayerName = strPlayerName;
}

// *****************************************************************************
bool cScore::operator> (cScore const &s) const 
{ 
	return m_iScore > s.m_iScore; 
}