#pragma once

#include <stack>

#include "Map.h"

class CmdBase_c
{

protected:

	Map *m_map;
	int event_type;

public:
	CmdBase_c( Map &map ) : m_map ( &map )
	{
	}

	~CmdBase_c(){ }

	virtual void undo() = 0;
	virtual void redo() = 0;

	virtual int getEveType() { return event_type; }

	enum{ ADD_TILE, REMOVE_TILE, LOAD_MAP, UNLOAD_MAP, FILL_MAP, UNFILL_MAP, RESET_MAP };
};


class CmdRemoveTile_c : public CmdBase_c
{

public:

	CmdRemoveTile_c( CmdRemoveTile_c &object ) 	:  
		CmdBase_c( *object.getMap())
	{
		this->tileX		= object.getTileX();
		this->tileY		= object.getTileY();
		this->tileType	= object.getTileType();
		event_type		= REMOVE_TILE;
	}

	CmdRemoveTile_c( int X, int Y, Map &map ) 
		:  CmdBase_c(map),
		   tileX (X),
		   tileY (Y)
	{
		event_type		= REMOVE_TILE;
	}

	~CmdRemoveTile_c();

	int			getTileX() { return tileX; }
	int			getTileY() { return tileY; }
	Tile::TYPE	getTileType() { return tileType; }
	Map*		getMap() { return m_map; }

	virtual void undo();
	virtual void redo();

private:
	int			tileX;
	int			tileY; 
	Tile::TYPE	tileType;
};

class CmdAddTile_c : public CmdBase_c
{

public:

	CmdAddTile_c( CmdAddTile_c &object ) 	:  
		CmdBase_c( *object.getMap())
	{
		this->tileX = object.getTileX();
		this->tileY = object.getTileY();
		this->tileType = object.getTileType();
		event_type		= ADD_TILE;
	}

	CmdAddTile_c( int X, int Y, Tile::TYPE type, Map &map ) 
		:  CmdBase_c(map),
		   tileX (X),
		   tileY (Y),
		   tileType (type)	
	{
		event_type		= ADD_TILE;
	}

	~CmdAddTile_c();

	int			getTileX() { return tileX; }
	int			getTileY() { return tileY; }
	Tile::TYPE	getTileType() { return tileType; }
	Map*		getMap() { return m_map; }

	virtual void undo();
	virtual void redo();

private:
	int			tileX;
	int			tileY; 
	Tile::TYPE	tileType;
};


class CmdFillMap_c : public CmdBase_c
{

public:

	CmdFillMap_c( Map &map ) 
		:  CmdBase_c(map)
	{ 
		event_type		= FILL_MAP;
    }

	CmdFillMap_c( CmdFillMap_c &object ) 		:  
		CmdBase_c( *object.getMap())
	{
		event_type		= FILL_MAP;
	}

	~CmdFillMap_c(){}
	Map*		getMap() { return m_map; }

	virtual void undo();
	virtual void redo();

};

class CmdUnFillMap_c : public CmdBase_c
{

public:

	CmdUnFillMap_c( Map &map ) 
		:  CmdBase_c(map)
	{ 
		event_type		= UNFILL_MAP;
	}

	CmdUnFillMap_c( CmdUnFillMap_c &object ) 		:  
		CmdBase_c( *object.getMap())
	{
		event_type		= UNFILL_MAP;
	}

	~CmdUnFillMap_c(){}
	Map*		getMap() { return m_map; }

	virtual void undo();
	virtual void redo();

};

class TrackMapInput_c
{
	
public:
	
	TrackMapInput_c( Map &map  ){ m_map = &map; }
	~TrackMapInput_c(){ }
	virtual void redo( );
	virtual void undo( );
	virtual void recordRemoveTile( int tileX, int tileY );
	virtual void recordAddTile( int tileX, int tileY, Tile::TYPE tileType );
	virtual void recordFillMap( );
	virtual void recordUnFillMap( );
	void recordResetMap( );
	CmdBase_c *createNewObject( CmdBase_c* cmd );
private:
	std::stack <CmdBase_c*> undoEventStack;
	std::stack <CmdBase_c*> redoEventStack;
	Map *m_map;
};
