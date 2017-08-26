#pragma once


#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include <unordered_map>

#include "side.h"
#include "pieces.h"


using namespace std;


class Board {
    private:
        const int width;
        const int height;

        std::vector<Piece*> piece_list;
        Side side_to_move;
        unordered_map<char, bool> castling;
        /**
         * The en passant target square is specified after a double push of a 
         * pawn, no matter whether an en passant capture is really possible or 
         * not.
         */
        Square * en_passant_sqr;
        /**
         * The halfmove clock specifies a decimal number of half moves with 
         * respect to the 50 move draw rule. It is reset to zero after a 
         * capture or a pawn move and incremented otherwise.
         */
        int half_move_counter;
        /**
         * The number of the full moves in a game. It starts at 1, and is 
         * incremented after each Black's move.
         */
        int full_move_counter;
    
    public:
        Board();
        Board(int, int);
        bool place_piece(char, int, int);
        std::string to_string();
        Piece* get(int, int);
        string to_fen();
        
        // Setters

        void set_side_to_move(Side);
        void set_castling(char, bool);
        void set_side_has_castled(Side);
        void set_en_passant_target_square(string);
        void set_half_move_counter(int);
        void set_full_move_counter(int);
};
