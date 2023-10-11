#include<iostream>
#include<cmath>
#include<ctime>
using namespace std;
int depth =3;
int bm = 2;
bool check(char board[8][8], char move[],bool turn) {
	char t = board[move[2]][move[3]];
	board[move[2]][move[3]] = board[move[0]][move[1]];
	board[move[0]][move[1]] = ' ';

	int k;
	int l;
	for (k = 0; k < 8; k++) {
		for (l = 0; l < 8; l++) {
			if (board[k][l] == 'k'-turn*('k'-'K'))break;
		}
		if (board[k][l] == 'k' - turn * ('k' - 'K'))break;
	}
	int temp[2] = { k,l };
	bool p;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			p = true;
			if (!j && !i)continue;
			temp[0] += i;
			temp[1] += j;

			while (temp[0] >= 0 && temp[0] < 8 && temp[1] >= 0 && temp[1] < 8) {
					if (((board[temp[0]][temp[1]] == 'K' - turn * ('K' - 'k') && p) || board[temp[0]][temp[1]] == 'Q'-turn*('Q'-'q') || board[temp[0]][temp[1]] == 'B'-turn*('B'-'b') || (board[temp[0]][temp[1]] == 'P'-turn*('P'-'p') && p && (i == 1-turn*2))) && (j && i)) {
						board[move[0]][move[1]] = board[move[2]][move[3]];
						board[move[2]][move[3]] = t;
						return true;
					}
					if (((board[temp[0]][temp[1]] == 'K' - turn * ('K' - 'k') && p) || board[temp[0]][temp[1]] == 'Q' - turn * ('Q' - 'q') || board[temp[0]][temp[1]] == 'R' - turn * ('R' - 'r')) && (j&&!i || !j&&i)) {
						board[move[0]][move[1]] = board[move[2]][move[3]];
						board[move[2]][move[3]] = t;
						return true;
					}
					if (board[temp[0]][temp[1]] != ' ')break;
				
				temp[0] += i;
				temp[1] += j;
				p = false;
			}
			temp[0] = k;
			temp[1] = l;
		}
	}
	for (int i = -2; i < 3; i++) {
		if (!i)continue;
		for (int j = abs(i) - 3; j < 3; j += 2 * abs(j)) {
			if (i + k >= 0 && i + k < 8 && j + l >= 0 && j + l < 8) {
				if (board[i + k][j + l] == 'H'-turn*('H'-'h'))
				{
					board[move[0]][move[1]] = board[move[2]][move[3]];
					board[move[2]][move[3]] = t;
					return true;
				}
			}
		}
	}
	board[move[0]][move[1]] = board[move[2]][move[3]];
	board[move[2]][move[3]] = t;
	return false;
}
int eval(char board[8][8]) {
	static bool  turn = 1;
	static int  level = 1;
	int ev = 0;
	int best = -100;
	char move[4] = { 0 };
	char best_m[4] = {0};
	if ((level == depth+1) && turn) {
		best = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				switch (board[i][j]) {
				case 'p':
					best++;
					break;
				case 'h':
					best += 3;
					break;
				case 'b':
					best += 3;
					break;
				case 'r':
					best += 5;
					break;
				case 'q':
					best += 9;
					break;
				case 'P':
					best -= 1;
					break;
				case 'H':
					best -= 3;
					break;
				case 'B':
					best -= 3;
					break;
				case 'R':
					best -= 5;
					break;
				case 'Q':
					best -= 9;
					break;
				}
			}
		}
		return best;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((board[i][j] == 'r' - turn * ('r' - 'R'))||(board[i][j] == 'b' - turn * ('b' - 'B')) || (board[i][j] == 'q' - turn * ('q' - 'Q'))) {
				for (int k = -1; k < 2; k += 1) {
					for (int l = -1; l < 2; l += 1) {
						if (board[i][j] == 'r' - turn * ('r' - 'R') && k  && l )continue;
						if (board[i][j] == 'b' - turn * ('b' - 'B') && (!k || !l))continue;
						if (!k && !l)continue;
						int t1 = i+k, t2 = j+l;
						while (t1>=0&&t1<=7&&t2>=0&&t2<=7) {
							if (board[t1][t2] == ' ' || (board[t1][t2] >= 'a' - !turn * ('a' - 'A') && (board[t1][t2] <= 'z' - !turn * ('z' - 'Z')))) {
								move[0] = i;
								move[1] = j;
								move[2] = t1;
								move[3] = t2;
								if (!check(board, move,turn)) {
									char t = board[t1][t2];
									board[t1][t2] = board[i][j];
									board[i][j] = ' ';
									if (!turn)level++;
									turn = !turn;
									ev = eval(board);
									turn = !turn;
									if (!turn) level--;

									if (((ev > best)&&!turn)||((ev<best)&&turn)||best==-100) {
										best = ev;
										if (level == 1 && turn == 1) {
											best_m[0] = move[0];
											best_m[1] = move[1];
											best_m[2] = move[2];
											best_m[3] = move[3];
										}
									}
									board[i][j] = board[t1][t2];
									board[t1][t2] = t;
								}
							}
							if (board[t1][t2] != ' ')break;
							t1 += k;
							t2 += l;
						}
					}
			 }
			}
			
			else if (board[i][j] == 'h' - turn * ('h' - 'H')) {
				for (int k = -2; k < 3; k++) {
					for (int l = abs(k) - 3; l < 3; l += 2 * abs(l)) {
						if (!k)break;
						if (k + i >= 0 && k + i < 8 && l + j >= 0 && l + j < 8) {
							if (board[k + i][j + l] == ' ' || board[k + i][j + l] >= 'a' - !turn * ('a' - 'A') && board[k + i][j + l] <= 'z' - !turn * ('z' - 'Z')) {
								move[0] = i;
								move[1] = j;
								move[2] = i+k;
								move[3] = j+l;
								if (!check(board, move,turn)) {
									char t = board[i+k][j+l];
									board[i+k][j+l] = board[i][j];
									board[i][j] = ' ';
									if (!turn)level++;
									turn = !turn;
									ev = eval(board);
									turn = !turn;
									if (!turn) level--;

									if (((ev > best) && !turn) || ((ev < best) && turn)||best==-100||(ev == best && !(rand() % bm)) ){
										best = ev;
										if (level == 1 && turn == 1) {
											bm++;
											best_m[0] = move[0];
											best_m[1] = move[1];
											best_m[2] = move[2];
											best_m[3] = move[3];
										}
									}
									board[i][j] = board[i+k][j+l];
									board[i+k][j+l] = t;
								}
							}
						}
					}
				}
			}
			else if (board[i][j] == 'p' - turn * ('p' - 'P')) {
				for (int k = -1; k < 2; k++) {
					if (j+k>=0&&j+k<=7&&( i + turn - (!turn)>=0)&&( i + turn - (!turn)<=7)&&((!k && board[i + turn - (!turn)][j] == ' ') || (k &&( (board[i + turn - (!turn)][j+k] >= 'a' - (!turn) * ('a' - 'A')) && (board[i + turn - (!turn)][j+k] <= 'z' - (!turn) * ('z' - 'Z')))))) {
						move[0] = i;
						move[1] = j;
						move[2] = i +turn-!turn;
						move[3] = j + k;
						if (!check(board, move,turn)) {
							char t = board[i + turn - (!turn)][j + k];
							board[i + turn - (!turn)][j + k] = board[i][j];
							board[i][j] = ' ';
							if (!turn)level++;
							turn = !turn;
							ev = eval(board);
							turn = !turn;
							if (!turn) level--;

							if (((ev > best) && !turn) ||( (ev < best) && turn)||best==-100||( ev == best && !(rand() % bm))) {
								best = ev;
								if (level == 1 && turn == 1) {
									bm++;
									best_m[0] = move[0];
									best_m[1] = move[1];
									best_m[2] = move[2];
									best_m[3] = move[3];
								}
							}
							board[i][j] = board[i + turn - !turn][j + k];
							board[i + turn - !(turn)][j + k] = t;
						}
					}
				}
			}
			else if (board[i][j] == 'k' - turn * ('k' - 'K')) {
				for (int k = -1; k < 2; k++) {
					for (int l = -1; l < 2; l++) {
						if ((!k && !l) || i + k < 0 || i + k>7 || j + l < 0 || j + l>7 || (board[i + k][j + l] >= 'a' - turn * ('a' - 'A') && board[i + k][j + l] <= 'z' - turn * ('z' - 'Z')))continue;
						move[0] = i;
						move[1] = j;
						move[2] = i + k;
						move[3] = j + l;
						if (!check(board, move,turn)) {
							char t = board[i + k][j + l];
							board[i + k][j + l] = board[i][j];
							board[i][j] = ' ';
							if (!turn)level++;
							turn = !turn;
							ev = eval(board);
							turn = !turn;
							if (!turn) level--;

							if (((ev > best) && !turn) || ((ev < best) && turn)||(best==-100)||(ev==best&&!(rand()%bm))) {
								best = ev;
								if (level == 1 && turn == 1) {
									bm++;
									best_m[0] = move[0];
									best_m[1] = move[1];
									best_m[2] = move[2];
									best_m[3] = move[3];
								}
							}
							board[i][j] = board[i + k][j + l];
							board[i + k][j + l] = t;
						}
					}
				}
			}
		}
	}
	if (level == 1 && turn) {
		board[best_m[2]][best_m[3]] = board[best_m[0]][best_m[1]];
		board[best_m[0]][best_m[1]] = ' ';
	}
	if (best == -100)return -100 + 200 * turn;
	return best;
}
void print_b(char board[8][8],int evalu) {
	system("cls");
	cout << endl<<evalu<<endl;
	for(int i = 0; i < 8; i++) {
		cout << 8 - i << "    ";
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == ' ')cout << ".    ";
			else cout << board[i][j] << "    ";
		}
		cout << endl;
		cout << "   ";
		for (int k = 0; k < 8; k++) {
			//if (k%2 && i%2 || !(k%2) && !(i%2))cout << "    ";
			//else 
			cout << "     ";
		}
		cout<< endl;
	}
	cout << "     " ;
	for (int i = 0; i < 8; i++)cout << char(i + 'A') << "    ";
	cout << endl;
}
bool b(char board[8][8], char move[]) {
	if (move[0] != move[2] && move[1] != move[3]) {


		int temp[2] = { move[0],move[1] };

		while (temp[0]>=0&&temp[0]<8&&temp[1]>=0&&temp[1]<8) {
			if (temp[0] < move[2])temp[0]++;
			else temp[0]--;
			if (temp[1] < move[3])temp[1]++;
			else temp[1]--;
			if (temp[0] == move[2] && temp[1] == move[3] && board[temp[0]][temp[1]] < 'a') {
				return true;
			}
			if (temp[0] == move[2] || temp[1] == move[3] || board[temp[0]][temp[1]] != ' ')
				break;
		}
	}
	return false;
}
bool r(char board[8][8], char move[]) {
	if (!(move[0] != move[2] && move[1] != move[3])) {


		int temp[2] = { move[0],move[1] };

		while (temp[0] >= 0 && temp[0] < 8 && temp[1] >= 0 && temp[1] < 8) {
			if (temp[0] < move[2])temp[0]++;
			else if((temp[0] > move[2]))temp[0]--;
			if (temp[1] < move[3])temp[1]++;
			else if(temp[1] > move[3])temp[1]--;
			if (temp[0] == move[2] && temp[1] == move[3] && board[temp[0]][temp[1]] < 'a') {
				return true;
			}
			if ( board[temp[0]][temp[1]] != ' ')
				break;
		}
	}
	return false;
}

bool l_m(char board[8][8],char move[]) {
	if ((move[0] == move[2] && move[1] == move[3])|| move[2] < 0 || move[2]>7 || move[3] < 0 || move[3] > 7)return false;
	char piece = board[move[0]][move[1]];
	switch (piece) {
	case 'r':
		if (!r(board, move))return false;
		break;
	case 'b':
		if(!b(board, move))return false;
		break;
	case'p':
		if (move[1]-move[3]==0&&move[0] == 6 &&move[2]==4&& board[move[2]][move[3]]==' '&& board[move[2]+1][move[3]]==' ')break;
		if (move[0] - move[2] !=1 || abs(move[1] - move[3]) > 1)return false;
		if (move[1] - move[3] == 0 && board[move[2]][move[3]] != ' ')return false;
		if (abs(move[1] - move[3]) && (board[move[2]][move[3]] >= 'a'|| board[move[2]][move[3]]==' '))return false;
		break;
	case 'h':
		if (!(abs(move[0] - move[2]) == 2 && abs(move[1] - move[3]) == 1 || abs(move[1] - move[3]) == 2 && abs(move[0] - move[2]) == 1))
			return false;
		break;
	case 'q':
		if (!r(board, move) && !b(board, move))return false;
		break;
	case 'k':
		if (abs(move[0] - move[2]) > 1 || abs(move[1] - move[3]) > 1||board[move[2]][move[3]]>='a')return false;
		break;
	default: return false;
	}
	return !check(board, move,0);
}
int main() {
	srand(time(nullptr));
	char board[8][8] = { { 'R','H','B','Q','K','B','H','R' },
	 { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
	{ 'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r' }, };
	char move[4];
	int evalu = 0;
	while (true) {

		print_b(board,evalu);
		cin >> move[0]>>move[1]>>move[2]>>move[3];
		char temp = move[0] - 'a';
		move[0] =7-( move[1] - '1');
		move[1] = temp;
		temp = move[2] - 'a';
		move[2] = 7-(move[3] - '1');
		move[3] = temp;
		if (!l_m(board, move))continue;
		board[move[2]][move[3]] = board[move[0]][move[1]];
		board[move[0]] [move[1]] = ' ';
		evalu=eval(board);
		bm = 2;

	}
}
