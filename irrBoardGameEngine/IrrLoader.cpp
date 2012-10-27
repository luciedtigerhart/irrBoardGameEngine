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
	int tilesI, tilesJ, larg, alt, prof, tile_atual;

	std::string tile_num;
	std::string nome_arq;
	tile_num = "*";

	//
	// CARREGA ARQUIVO
	//
	ifstream arq(src.c_str());
	if(!arq.is_open()) return false;

	//
	// QUANTIDADE DE TILES i ~ j, para criar a matriz
	//
	arq >> tilesI >> tilesJ;

	if( (tilesI < 1) || (tilesJ < 1)) return false;

	//
	// DIMENSÕES DO TILE
	//
	arq >> larg >> alt >> prof;

	if( (larg < 1) || (alt < 1)  || (prof < 1)) return false;

	//
	// CARREGA AS IMAGENS PARA A TEXTURA DO TILE
	//
	arq >> tile_num;
	while(arq >> nome_arq)
	{
		board->objs->push_back(nome_arq);
		arq >> tile_num;
		if(tile_num == "*") break;
	}

	//
	// CRIA O BOARD
	//
	board->width = tilesI*larg;
	board->length = tilesJ*prof;

	board->tile_i = tilesI;
	board->tile_j = tilesJ;

	board->tile_width = larg;
	board->tile_height = alt;
	board->tile_length = prof;

	board->board.resize(tilesJ);
	for(int j = 0; j < tilesJ; j++)
		board->board[j].resize(tilesI);

	//
	// POPULA O BOARD
	//
	for(int j = 0; j < tilesJ; j++)
	{
		for(int i = 0; i < tilesI; i++)
		{
			arq >> tile_atual;
			board->board[j][i] = new IrrTile();
			board->board[j][i]->posi = i;
			board->board[j][i]->posj = j;
			board->board[j][i]->idx = tile_atual;
			//std::cout << tile_atual << " ";
		}
		//std::cout << endl;
	}

	//
	// INFORMAÇÕES
	//
	std::string sep;
	arq >> sep;
	if(sep != "*") return false;

	for(int j = 0; j < tilesJ; j++)
	{
		for(int i = 0; i < tilesI; i++)
		{
			arq >> tile_atual;
			board->board[j][i]->inf = tile_atual;
		}
	}

	//
	// PEÇA INICIAL dos JOGADORES
	//
	arq >> sep;
	if(sep != "*") return false;
	
	for(int j = 0; j < tilesJ; j++)
	{
		for(int i = 0; i < tilesI; i++)
		{
			arq >> tile_atual;
			if(tile_atual != 0) board->board[j][i]->start = tile_atual;
		}
	}

	return true;
}