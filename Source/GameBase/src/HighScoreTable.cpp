// *****************************************************************************
//  HighScoreTable   version:  1.0   Ankur Sheel  date: 2013/03/14
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "HighScoreTable.h"
#include "Score.h"
#include "XMLFileio.hxx"
#include "optional.h"

using namespace GameBase;
using namespace Utilities;
using namespace Base;

// *****************************************************************************
cHighScoreTable::cHighScoreTable(const Base::cString & strPath, const int iNumberOfRecords)
: m_strScoreFile(strPath + ".xml")
, m_uiNumScores(iNumberOfRecords)
{

}

// *****************************************************************************
cHighScoreTable::~cHighScoreTable()
{
}

// *****************************************************************************
void cHighScoreTable::VAddNewScore(shared_ptr<cScore> pScore)
{
	m_Scores.insert(pScore);
	if(m_Scores.size() > m_uiNumScores)
	{
		ScoreSet::iterator iter = m_Scores.end();
		iter--;
		m_Scores.erase(iter);
	}
}

// *****************************************************************************
void cHighScoreTable::Initialize()
{
	// Make a default score table if none exists
	DWORD attr = GetFileAttributes(m_strScoreFile.GetData());
    if (attr == INVALID_FILE_ATTRIBUTES)
    {
		int iStep = (1000/m_uiNumScores);
		for (unsigned int i = 0, iScore = 1000; i < m_uiNumScores; i++, iScore -= iStep)
		{
			shared_ptr<cScore> pScore(DEBUG_NEW cScore());
			pScore->SetPlayerName("Speedrun");
			pScore->SetScore(iScore);
			VAddNewScore(pScore);
		}
        VSave();
		m_Scores.clear();
    }
}

// *****************************************************************************
void cHighScoreTable::VSave()
{
	IXMLFileIO * pXml = IXMLFileIO::CreateXMLFile();

	pXml->VInitializeForSave("HighScores", "");
	int id = 0;
	cString strElementName;
	for(ScoreSet::iterator iter = m_Scores.begin(); iter != m_Scores.end(); iter++)
	{
		strElementName = pXml->VAddElement("HighScores", "HighScore", cString(20, "%d",id), "");
		pXml->VAddAttribute(strElementName, "name", (*iter)->GetPlayerName());
		pXml->VAddAttribute(strElementName, "score", (*iter)->GetScore());
		id++;
	}
	pXml->VSave(m_strScoreFile);
	SafeDelete(&pXml);
}

// *****************************************************************************
void cHighScoreTable::VLoad()
{
	IXMLFileIO	* pXml = IXMLFileIO::CreateXMLFile();
	if(pXml->VLoad(m_strScoreFile))
	{
		m_Scores.clear();
		cString strPlayerName;
		int iScore;
		cString strElementName;
		for(unsigned int i=0; i<=m_uiNumScores; i++)
		{
			shared_ptr<cScore> pScore(DEBUG_NEW cScore());
			strElementName = cString(100, "HighScore%d",i);
			strPlayerName = pXml->VGetNodeAttribute(strElementName, "name");
			iScore = pXml->VGetNodeAttributeAsInt(strElementName, "score");
			pScore->SetPlayerName(strPlayerName);
			pScore->SetScore(iScore);
			VAddNewScore(pScore);
		}
	}
	SafeDelete(&pXml);
}

// *****************************************************************************
cHighScoreTable::ScoreSet cHighScoreTable::GetScores()
{
	if(m_Scores.empty())
	{
		VLoad();
	}
	return m_Scores;
}

// *****************************************************************************
tOptional<int> cHighScoreTable::IsHighScore(const int iScore)
{
	if(m_Scores.empty())
	{
		VLoad();
	}
	int iPos = 0;
	for(ScoreSet::iterator iter = m_Scores.begin(); iter != m_Scores.end(); iter++)
	{
		if(iScore > (*iter)->GetScore())
		{
			return iPos;
		}
		iPos++;
	}
	return tOptional<int>();
}