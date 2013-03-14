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

class cScore;

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
	protected:
		GAMEBASE_API cHighScoreTable();
		GAMEBASE_API ~cHighScoreTable();
		GAMEBASE_API virtual void VSave();
		GAMEBASE_API virtual void VLoad();

	protected:
		Base::cString	m_strScoreFile;	///< The path for the score file
		int				m_iNumScores;	///< The number of Scores to store
		std::multiset<shared_ptr<cScore>, std::greater<cScore> > m_Scores;

	};
}
#endif