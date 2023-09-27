"""
file: py_match.py
author: Umair Khan
date: 04/29/22
section: 33
email: ukhan5@umbc.edu
description: matching game with letters

"""


import random


def load_file(file_name):
    # loads in user inputted file
    symbols = []
    symbol_num = {}
    with open(file_name) as file:
        file_input = file.read().split()
        for i in file_input:
            symbols.append(i)
            symbol_num[i] = 0
        file.close()
    return symbols, symbol_num


def make_game(row, col, symbols, symbol_sym):
    # makes game board used in user guess function
    game_board_2 = []
    play_board_2 = []
    symbols_val = symbol_sym
    for i in range(row):
        game_list = []
        per_list = []
        for j in range(col):

            game_list.append(random.choice(symbols))
            per_list.append('.')
            symbols_val[random.choice(symbols)] += 1

        game_board_2.append(game_list)
        play_board_2.append(per_list)

    return symbols_val, game_board_2, play_board_2


def user_guess(row, col, symbol_list, symbol_sym):
    letter_find = ''
    value_find = 0
    finished = []
    end = 0
    board_lists = make_game(row, col, symbol_list, symbol_sym)
    symbol_count = board_lists[0]
    answer_board = board_lists[1]
    play_board = board_lists[2]
    # reset board is used to reset game without losing progress on number of symbols left
    reset_board = board_lists[2]
    for i in range(row):
        print(play_board[i])
    while end == 0:
        if value_find >= 1:
            guess = input(f'Enter position to guess that matches {letter_find}, there are {(symbol_count[letter_find] - value_find)} remaining: ')
        else:
            guess = input("Enter position to guess: ")
        guess_list = guess.split()
        # account for index
        pos_y = int(guess_list[0]) - 1
        pos_x = int(guess_list[1]) - 1
        if 0 <= pos_y <= (row - 1) and 0 <= pos_x <= (col - 1):
            if play_board[pos_y][pos_x] == '.' and answer_board[pos_y][pos_x] not in finished:
                # starts game
                if letter_find == '':
                    letter_find = answer_board[pos_y][pos_x]
                # add count if guess is correct
                if letter_find == answer_board[pos_y][pos_x]:
                    value_find += 1
                    play_board[pos_y][pos_x] = letter_find
                # reset is guess is wrong
                else:
                    for i in range(row):
                        for j in range(col):
                            if reset_board[i][j] == '.':
                                play_board[i][j] = '.'
                for i in range(row):
                    print(play_board[i])
                if letter_find != '':
                # check to see if all letters found
                    if symbol_count[letter_find] == value_find:
                        for i in range(row):
                            for j in range(col):
                                if answer_board[i][j] == letter_find:
                                    play_board[i][j] = letter_find
                        print(f"You have found all the {letter_find}s")
                        letter_find = ''
                        value_find = 0
                        finished.append(answer_board[pos_y][pos_x])
        end += 1
        for y in range(row):
            for x in range(col):
                if play_board[y][x] == '.':
                    end = 0


def play_game(row, col, file_name):
    file_list = load_file(file_name)
    row = int(row)
    col = int(col)
    symbols = file_list[0]
    symbol_2 = file_list[1]
    user_guess(row, col, symbols, symbol_2)
    print("Congrats, you won!")


if __name__ == "__main__":
    user_input = input("Enter Row, Col, Seed: ").split(', ')
    symbol_file = input("What is the symbol file name? ")
    random.seed(user_input[2])
    play_game(user_input[0], user_input[1], symbol_file)
