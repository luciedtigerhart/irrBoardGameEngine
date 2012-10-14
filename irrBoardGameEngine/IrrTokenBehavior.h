#pragma once

#include "IrrBehavior.h"
#include "IrrToken.h"

namespace IrrBoardGameEngine {

	class IrrTokenBehavior : public IrrBehavior
	{
		public:
			void setToken(IrrToken *o) {token=o;}
		protected:
			//!<O objeto que o comportamento está relacionado
			IrrToken *token;
	};
};