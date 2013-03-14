// *****************************************************************************
//  Score   version:  1.0   Ankur Sheel  date: 2013/03/14
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Score_h__
#define Score_h__

#include "GameBaseDefines.h"

namespace GameBase
{
	////////////////////////////////////////////////////////////////////////////
	/// @brief Base class to hold scores. This class should be derived to hold
	/// game specific scores
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class cScore
		: public Base::cNonCopyable
	{
	public:
		////////////////////////////////////////////////////////////////////////
		/// Increments the score with /ciDeltaValue. If /ciDeltaValue is negative
		/// decrements the score
		///
		/// @param[in] iDeltaValue The value by which the score needs to be 
		/// modified. Can be negative.
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API void UpdateScore(const int iDeltaValue);
		////////////////////////////////////////////////////////////////////////
		/// Returns the current score
		///
		/// @return The current score
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API int GetScore() const;

	protected:
		GAMEBASE_API cScore();
		GAMEBASE_API ~cScore();
		GAMEBASE_API bool operator>(cScore const &s) const;

	protected:
		Base::cString	m_strPlayerName;	///< The name of the player
		int				m_iScore;	///< The score of the player
	};
}
#endif