#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class game_board
{
private:
	char** board_data;
	int cols;
	int rows;
	char base_tile;
public:
	char last_used_char;
	game_board() {};
	game_board(int r, int c, char bt)
	{
		board_data = new char* [r];

		for (int i = 0; i < r; i++)
		{
			board_data[i] = new char[c];
		}
		rows = r;
		cols = c;
		base_tile = bt;

		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				board_data[i][j] = bt;
			}
		}
	}

	void add_element(char element, int r, int c)
	{
		board_data[r][c] = element;
	}

	void display_board()
	{
		for (int i = 0; i < rows; i++)
		{
			cout << i << ": ";
			for (int j = 0; j < cols; j++)
			{
				cout << board_data[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "   ";
		for (int i = 0; i < cols; i++)
		{
			cout << i << " ";
		}
		cout << "\n";
	}

	int drop_tile(int col_index, char tile)
	{
		for (int i = 0; i < rows - 1; i++)
		{
			if (board_data[i][col_index] == base_tile && board_data[i + 1][col_index] != base_tile)
			{
				board_data[i][col_index] = tile;
				return i;
			}
			if (board_data[i][col_index] == base_tile && i == rows - 2)
			{
				board_data[i + 1][col_index] = tile;
				return i + 1;
			}
		}
		return -1;
	}

	int get_num_rows()
	{
		return rows;
	}

	int get_num_cols()
	{
		return cols;
	}

	void set_element(char element, int r, int c)
	{
		board_data[r][c] = element;
	}

	char game_is_over(int lastc, int lastr)
	{
		string temp_key;
		char game_over = base_tile;
		temp_key.push_back(horizontal_four(lastc, lastr));
		temp_key.push_back(vertical_four(lastc, lastr));
		temp_key.push_back(diagonal_top_left_four(lastc, lastr));
		temp_key.push_back(diagonal_top_right_four(lastc, lastr));
		for (int i = 0; i < temp_key.length(); i++)
		{
			if (temp_key[i] != base_tile)
			{
				game_over = temp_key[i];
			}
		}
		return game_over;
	}

	char horizontal_four(int lastc, int lastr)
	{
		int in_a_row_count = 1;
		char current_tile = board_data[lastr][lastc];
		for (int i = lastc - 1; i >= 0 && i > lastc - 4; i--)
		{
			if (board_data[lastr][i] == current_tile)
			{
				in_a_row_count++;
			}
			else
			{
				break;
			}
		}
		for (int i = lastc + 1; i < cols && i < lastc + 4; i++)
		{
			if (board_data[lastr][i] == current_tile)
			{
				in_a_row_count++;
			}
			else
			{
				break;
			}
		}
		if (in_a_row_count >= 4)
		{
			return current_tile;
		}
		else
		{
			return base_tile;
		}
	}

	char vertical_four(int lastc, int lastr)
	{
		int in_a_row_count = 1;
		char current_tile = board_data[lastr][lastc];
		for (int i = lastr - 1; i >= 0 && i > lastr - 4; i--)
		{
			if (board_data[i][lastc] == current_tile)
			{
				in_a_row_count++;
			}
			else
			{
				break;
			}
		}
		for (int i = lastr + 1; i < rows && i < lastr + 4; i++)
		{
			if (board_data[i][lastc] == current_tile)
			{
				in_a_row_count++;
			}
			else
			{
				break;
			}
		}
		if (in_a_row_count >= 4)
		{
			return current_tile;
		}
		else
		{
			return base_tile;
		}
	}

	char diagonal_top_left_four(int lastc, int lastr)
	{
		int in_a_row_count = 1;
		char current_tile = board_data[lastr][lastc];

		int i = lastc - 1;
		int j = lastr - 1;
		while (j >= 0 && j > lastr - 4 && i >= 0 && i > lastc - 4)
		{
			if (board_data[j][i] == current_tile)
			{
				in_a_row_count++;
			}
			else
			{
				break;
			}
			i--;
			j--;
		}

		i = lastc + 1;
		j = lastr + 1;
		while (j < rows && j < lastr + 4 && i < cols && i < lastc + 4)
		{
			if (board_data[j][i] == current_tile)
			{
				in_a_row_count++;
			}
			else
			{
				break;
			}
			i++;
			j++;
		}

		if (in_a_row_count >= 4)
		{
			return current_tile;
		}
		else
		{
			return base_tile;
		}
	}

	char diagonal_top_right_four(int lastc, int lastr)
	{
		int in_a_row_count = 1;
		char current_tile = board_data[lastr][lastc];
		int i = lastc - 1;
		int j = lastr + 1;
		while (i >= 0 && i > lastc - 4 && j < rows && j < lastr + 4)
		{
			if (board_data[j][i] == current_tile)
			{
				in_a_row_count++;
			}
			else
			{
				break;
			}
			i--;
			j++;
		}
		i = lastc + 1;
		j = lastr - 1;
		while (i < cols && i < lastc + 4 && j >= 0 && j > lastr - 4)
		{
			if (board_data[j][i] == current_tile)
			{
				in_a_row_count++;
			}
			else
			{
				break;
			}
			i++;
			j--;
		}
		if (in_a_row_count >= 4)
		{
			return current_tile;
		}
		else
		{
			return base_tile;
		}
	}

	char get_base_tile()
	{
		return base_tile;
	}
};

class player
{
private:
	char player_initial;
public:
	player() {};
	virtual int get_next_move(int* col_index) = 0;

	bool operator == (player& p2)
	{
		if (player_initial == p2.player_initial)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	char get_player_initial()
	{
		return player_initial;
	}

	void set_player_initial(char c)
	{
		player_initial = c;
	}
};

class human_player : public player, public game_board
{
private:
	string player_name;
	game_board* active_board;
public:
	human_player(game_board* g)
	{
		active_board = g;
		cout << "Please enter your first name: ";
		cin >> player_name;
		player::set_player_initial(player_name[0]);
		while (active_board->last_used_char == player::get_player_initial() || player::get_player_initial() == active_board->get_base_tile())
		{
			char c;
			cout << "Sorry, your initial was already in use, your name started with a space or your name started with the background character, please enter a different initial than the other player to get started: ";
			cin >> c;
			player::set_player_initial(c);
		}
		active_board->last_used_char = player::get_player_initial();
		cout << "Hello " << player_name << ", this game you will be represented by the initial " << get_player_initial() << "\n";
	}

	int get_next_move(int* col_index)
	{
		int placed_row;
		cout << player_name << ": What column number between 0 and " << active_board->get_num_cols() - 1 << " do you want to enter a tile into: ";
		cin >> *col_index;
		while (!cin || *col_index > active_board->get_num_cols() - 1 || col_index < 0)
		{
			cout << "Please enter a valid integer between 0 and " << active_board->get_num_cols() - 1 << ": ";
			cin >> *col_index;
		}
		placed_row = active_board->drop_tile(*col_index, player::get_player_initial());

		while (placed_row == -1)
		{
			cout << "That column is full, try again: ";
			cin >> *col_index;
			placed_row = active_board->drop_tile(*col_index, player::get_player_initial());
		}
		active_board->display_board();
		return placed_row;
	}
};

int main()
{
	int lastc, lastr;
	char winner;
	game_board g1(6, 7, '-');
	human_player p1 = human_player(&g1);
	human_player p2 = human_player(&g1);

	auto last_move = p2;
	do {
		if (last_move == p2)
		{
			lastr = p1.get_next_move(&lastc);
			last_move = p1;
		}
		else
		{
			lastr = p2.get_next_move(&lastc);
			last_move = p2;
		}
		winner = g1.game_is_over(lastc, lastr);
	} while (winner == g1.get_base_tile());

	cout << "\nPlayer " << winner << " wins!\n";
}