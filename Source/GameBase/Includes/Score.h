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
	{
	public:
		GAMEBASE_API cScore();
		////////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] strPlayerName The name of the player.
		/// @param[in] iScore The score of the player.
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API cScore(const Base::cString	& strPlayerName, const int iScore);
		////////////////////////////////////////////////////////////////////////
		/// Destructor
		///
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API ~cScore();
		////////////////////////////////////////////////////////////////////////
		/// Returns the current score
		///
		/// @return The current score
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API int GetScore() const;
		////////////////////////////////////////////////////////////////////////
		/// Increments the score with /ciDeltaValue. If /ciDeltaValue is negative
		/// decrements the score
		///
		/// @param[in] iDeltaValue The name of the player
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API void UpdateScore(const int iDeltaValue);
		////////////////////////////////////////////////////////////////////////
		/// Sets the score to /ciScore
		///
		/// @param[in] iScore The new value of the score
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API void SetScore(const int iScore);
		////////////////////////////////////////////////////////////////////////
		/// Returns the player name
		///
		/// @return The player name
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API Base::cString GetPlayerName() const;
		////////////////////////////////////////////////////////////////////////
		/// Sets the player name to /cstrPlayerName
		///
		/// @param[in] strPlayerName The name of the player.
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API void SetPlayerName(const Base::cString	& strPlayerName);

	public:
		GAMEBASE_API bool operator > (cScore const &s) const;

	protected:
		Base::cString	m_strPlayerName;	///< The name of the player
		int				m_iScore;	///< The score of the player
	};
}
#endif