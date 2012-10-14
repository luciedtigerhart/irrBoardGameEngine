#pragma once
#include "IrrBehavior.h"
#include "IrrTile.h"

namespace IrrBoardGameEngine {

	class IrrTileBehavior : public IrrBehavior
	{
		public:
			void setTile(IrrTile *o) {tile=o;}
		protected:
			//!<O objeto que o comportamento está relacionado
			IrrTile *tile;
	};
};