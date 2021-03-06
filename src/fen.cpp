#include "fen.hpp"
#include "split.hpp"

#include <cstring>


using namespace std;


FENParser::FENParser(string fen) : original_fen(fen) {};

void FENParser::parse_piece_placement(vector<string> ranks, Board* board) {
    // TODO: remove this hard coded dependancy on these strings? But is part of FEN...?
    static const char white[] = "KQBNRP";
    static const char black[] = "kqbnrp";

    int current_rank = 7;  // start at the 8th rank
    int current_file = 0;
    for(auto rank : ranks) {
        for (char p : rank) {
            if ('0' <= p && p <= '8') {
                current_file += p - '0';
            }
            else if (strchr(white, p) != NULL || strchr(black, p) != NULL) {
                board->place_piece(p, current_file, current_rank);
                current_file++;
            }
            else {
                throw range_error(string("Not a number or a known piece type: ") + p);
            }
        }
        current_file = 0;
        current_rank--;
    }
}

void FENParser::parse_side_to_move(string stm, Board* board) {
    if (stm == "w") {
        board->set_side_to_move(Side::WHITE);
    }
    else if (stm == "b") {
        board->set_side_to_move(Side::BLACK);
    }
    else {
        throw range_error(string("Unknown side-to-move: ") + stm);
    }
}

void FENParser::parse_castling_ability(string castling, Board* board) {
    if (castling == "-") return;
    for(char& c : castling) {
        board->set_castling(c, true);
    }
}

void FENParser::parse_en_passant_target_square(string ep_squre, Board* board) {
    if (ep_squre.length() == 2) {
        board->set_en_passant_target_square(ep_squre);
    }
}

void FENParser::parse_halfmove_clock(string hlfmv, Board* board) {
    board->set_half_move_counter(stoi(hlfmv));
}

void FENParser::parse_fullmove_counter(string fllmvc, Board* board) {
    board->set_full_move_counter(stoi(fllmvc));
}

string FENParser::getOriginalFEN() const {
    return original_fen;
}

Board* FENParser::parse() {
    // Can't get these working :(
    // shared_ptr<Board> board = make_shared<Board>();
    // std::shared_ptr<Board> board(new Board());
    Board * board = new Board();

    auto tokens = split(original_fen, ' ');
    auto ranks = split(tokens[0], '/');  // Piece Placement

    parse_piece_placement(ranks, board);
    parse_side_to_move(tokens[1], board);
    parse_castling_ability(tokens[2], board);
    parse_en_passant_target_square(tokens[3], board);
    parse_halfmove_clock(tokens[4], board);
    parse_fullmove_counter(tokens[5], board);

    return board;
}
