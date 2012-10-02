#include "IrrLoader.h"

using namespace IrrBoardGameEngine;

IrrLoader::IrrLoader(void)
{
}


IrrLoader::~IrrLoader(void)
{
}

bool IrrLoader::loadBoard(std::string src, IrrBoard * board)
{
	int tilesX, tilesY;
	int larg, alt;
	int tile_atual;
	std::string tile_num;
	std::string nome_arq;
	tile_num = "*";

	//
	// CARREGA ARQUIVO
	//
	ifstream arq(src.c_str());
	if(!arq.is_open()) return false;

	//
	// QUANTIDADE DE TILES X ~ Y
	//
	arq >> tilesX >> tilesY;

	if( (tilesX < 1) || (tilesY < 1)) return false;

	//
	// DIMENSÕES DO TILE
	//
	arq >> larg >> alt;

	if( (larg < 1) || (alt < 1)) return false;

	//delta = iSC->getNumTiles();

	//
	// CARREGA AS IMAGENS PARA A TEXTURA DO TILE
	//
	arq >> tile_num;
	while(arq >> nome_arq)
	{
		//iSC->carregar(nome_arq);
		board->objs->push_back(nome_arq);
		arq >> tile_num;
		if(tile_num == "*") break;
	}

	//
	// CRIA O BOARD
	//
	board->width = tilesX*larg;
	board->height = tilesY*alt;
	board->tile_x = tilesX;
	board->tile_y = tilesY;
	board->tile_width = larg;
	board->tile_height = alt;

	board->board.resize(tilesX);
	for(int i = 0; i < tilesX; i++)
		board->board[i].resize(tilesY);


	//
	// POPULA O BOARD
	//
	for(int y = 0; y < tilesY; y++)
	{
		for(int x = 0; x < tilesX; x++)
		{
			arq >> tile_atual;
			board->board[x][y] = new IrrTile();
			board->board[x][y]->posx = x;
			board->board[x][y]->posy = y;
			board->board[x][y]->idx = tile_atual;
		}
	}

	//
	// INFORMAÇÕES
	//
	std::string sep;
	arq >> sep;
	if(sep != "*") return false;

	for(int y = 0; y < tilesY; y++)
	{
		for(int x = 0; x < tilesX; x++)
		{
			arq >> tile_atual;
			board->board[x][y]->inf = tile_atual;
		}
	}

	arq >> sep;
	if(sep != "*") return false;

	//
	// ARMAZENA A LISTA DE PEÇAS
	//

	arq >> tile_num;
	while(arq >> nome_arq)
	{
		board->tokens->push_back(nome_arq);
		arq >> tile_num;
		if(tile_num == "*") break;
	}


	//
	// FORMATOS DAS PEÇAS
	//	
	for(int y = 0; y < tilesY; y++)
	{
		for(int x = 0; x < tilesX; x++)
		{
			arq >> tile_atual;
			board->board[x][y]->token->idx = tile_atual;
		}
	}

	//
	// PEÇA INICIAL dos JOGADORES
	//
	arq >> sep;
	if(sep != "*") return false;
	
	for(int y = 0; y < tilesY; y++)
	{
		for(int x = 0; x < tilesX; x++)
		{
			arq >> tile_atual;
			board->board[x][y]->token->player = tile_atual;
		}
	}

	return true;
}