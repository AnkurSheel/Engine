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

using namespace GameBase;
using namespace Utilities;
using namespace Base;

// *****************************************************************************
cHighScoreTable::cHighScoreTable(const Base::cString & strPath, const int iNumberOfRecords)
: m_strScoreFile(strPath + ".xml")
, m_iNumScores(iNumberOfRecords)
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
	if(m_Scores.size() > m_iNumScores)
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
		int iStep = (1000/m_iNumScores);
		for (int i = 0, iScore = 1000; i < m_iNumScores; i++, iScore -= iStep)
		{
			shared_ptr<cScore> pScore(DEBUG_NEW cScore());
			pScore->SetPlayerName("Speedrun");
			pScore->SetScore(iScore);
			VAddNewScore(pScore);
		}
        VSave();
    }
 
    // Load high score table
    VLoad();
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
		id++;
		strElementName = pXml->VAddElement("HighScores", "HighScore", cString(20, "%d",id), "");
		pXml->VAddAttribute(strElementName, "name", (*iter)->GetPlayerName());
		pXml->VAddAttribute(strElementName, "score", (*iter)->GetScore());
	}
	pXml->VSave(m_strScoreFile);
	SAFE_DELETE(pXml);
}

// *****************************************************************************
void cHighScoreTable::VLoad()
{
	IXMLFileIO	* pXml = IXMLFileIO::CreateXMLFile();
	if(pXml->VLoad(m_strScoreFile))
	{
		cString strPlayerName;
		int iScore;
		cString strElementName;
		for(int i=1; i<=m_iNumScores;i++)
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
	SAFE_DELETE(pXml);
}