#include <gameObjects/TrackMapInput.h>


void CmdUnFillMap_c::redo()
{
	m_map->unfillMap();
}

void CmdUnFillMap_c::undo()
{
	m_map->fillMap();
}


void CmdFillMap_c::redo()
{
	m_map->fillMap();
}

void CmdFillMap_c::undo()
{
	m_map->unfillMap();
}

void CmdAddTile_c::redo()
{
	m_map->addTile( getTileX(), getTileY(), getTileType() );
}

void CmdAddTile_c::undo()
{
	m_map->removeTile( getTileX(), getTileY() );
}


void CmdRemoveTile_c::redo()
{
	m_map->removeTile( getTileX(), getTileY() );
}


void CmdRemoveTile_c::undo()
{
	m_map->addTile( getTileX(), getTileY(), getTileType() );
}


CmdBase_c* TrackMapInput_c::createNewObject( CmdBase_c* cmd )
{
	CmdBase_c *ret = 0;
	switch( cmd->getEveType() )
	{
	case CmdBase_c::ADD_TILE:
		ret = new CmdAddTile_c(*(dynamic_cast< CmdAddTile_c* > (cmd)));
	break;
	case CmdBase_c::REMOVE_TILE:
		ret = new CmdRemoveTile_c(*(dynamic_cast< CmdRemoveTile_c* > (cmd)));
	break;
	case CmdBase_c::FILL_MAP:
		ret = new CmdFillMap_c(*(dynamic_cast< CmdFillMap_c* > (cmd)));
	break;
	case CmdBase_c::UNFILL_MAP:
	default:
		ret = new CmdUnFillMap_c(*(dynamic_cast< CmdUnFillMap_c* > (cmd)));
	break;
	}

	return ret;
}

void TrackMapInput_c::redo( )
{
	if( redoEventStack.size() > 0 )
	{
		redoEventStack.top()->redo();
		undoEventStack.push( createNewObject( redoEventStack.top() ) );
		redoEventStack.pop();
	}
	else
	{
		std::cout << "Redo stack is Empty " << std::endl;
	}
}

void TrackMapInput_c::undo( )
{
	if( undoEventStack.size() > 0 )
	{
		undoEventStack.top()->undo();
		redoEventStack.push( createNewObject( undoEventStack.top() ) );
		undoEventStack.pop();
	}
	else
	{
		std::cout << "Undo stack is Empty " << std::endl;
	}
}

void TrackMapInput_c::recordAddTile( int tileX, int tileY, Tile::TYPE tileType )
{
	std::cout << "Record Add Tile " << tileX << " " << tileY << " " << tileType << std::endl;
	undoEventStack.push( new CmdAddTile_c( tileX, tileY, tileType, *m_map ) );
}

void TrackMapInput_c::recordRemoveTile( int tileX, int tileY )
{
	std::cout << "Record Remove Tile " << tileX << " " << tileY << std::endl;
	undoEventStack.push( new CmdRemoveTile_c( tileX, tileY, *m_map ) );
}


void TrackMapInput_c::recordResetMap(  )
{
	std::cout << "Record Reset Map" << std::endl;
	while(!undoEventStack.empty())
	{
		undoEventStack.pop();
	}

	while(!redoEventStack.empty())
	{
		redoEventStack.pop();
	}

}


void TrackMapInput_c::recordFillMap(  )
{
	std::cout << "Record Fill Map" << std::endl;
	undoEventStack.push( new CmdFillMap_c( *m_map) );
}

void TrackMapInput_c::recordUnFillMap(  )
{
	std::cout << "Record UnFill Map" << std::endl;
	undoEventStack.push( new CmdFillMap_c( *m_map ) );
}

