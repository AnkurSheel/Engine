// *****************************************************************************
//  HighScoreTable   version:  1.0   Ankur Sheel  date: 2013/03/14
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef HighScoreTable_h__
#define HighScoreTable_h__

#include "GameBaseDefines.h"

namespace GameBase
{
	class cScore;
}

namespace GameBase
{
	////////////////////////////////////////////////////////////////////////////
	/// @brief Base class to hold HighScoreTables. This class should be derived to hold
	/// game specific HighScoreTables
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class cHighScoreTable
		: public Base::cNonCopyable
	{
	public:
	typedef std::multiset<shared_ptr<cScore>, Base::sharedptr_compare<cScore, std::greater<cScore> > > ScoreSet;

	public:
		GAMEBASE_API cHighScoreTable(const Base::cString & strPath, const int iNumberOfRecords);
		GAMEBASE_API ~cHighScoreTable();
		GAMEBASE_API virtual void VSave();
		GAMEBASE_API virtual void VLoad();
		GAMEBASE_API virtual void VAddNewScore(shared_ptr<cScore> pScore);
		GAMEBASE_API void Initialize();
		GAMEBASE_API ScoreSet GetScores();
		GAMEBASE_API Base::tOptional<int> IsHighScore(const int iScore);

	protected:
		Base::cString	m_strScoreFile;	///< The path for the score file
		int				m_iNumScores;	///< The number of Scores to store
		ScoreSet		m_Scores;
	};
}
#endif