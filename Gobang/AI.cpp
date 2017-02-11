/***************************************************************************

    file				: AI.cpp
    modified			: 2012-07-12 22:38:23
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#include "AI.h"

extern bool black_ai, white_ai;
extern MyButton *player_ai[2];
extern Gobang *game;
extern MyWindow *window;

void black_ai_cb(Fl_Widget* buttonptr) {
	if(black_ai) {
		black_ai = false;
		player_ai[0]->box(FL_NO_BOX);
		player_ai[0]->refresh();
	}
	else {
		white_ai = false;
		player_ai[1]->box(FL_NO_BOX);
		player_ai[1]->refresh();
		black_ai = true;
		player_ai[0]->box(FL_DOWN_BOX);
		player_ai[0]->color(window->color());
		player_ai[0]->refresh();
	}
}

void white_ai_cb(Fl_Widget* buttonptr) {
	if(white_ai) {
		white_ai = false;
		player_ai[1]->box(FL_NO_BOX);
		player_ai[1]->refresh();
	}
	else {
		black_ai = false;
		player_ai[0]->box(FL_NO_BOX);
		player_ai[0]->refresh();
		white_ai = true;
		player_ai[1]->box(FL_DOWN_BOX);
		player_ai[1]->color(window->color());
		player_ai[1]->refresh();
	}
}

Point ai() {
	if (game->step == 0)
		return Point(9, 9);
	
	// ��ӿ������ӵĵ�
	int p_num = 0;
	Point p_list[50];
	Point p_cur = game->pos[game->step - 1];
		// 0)
	for(int i=1; i<6 && VALID(p_cur.y - i); i++)
		if (game->map[p_cur.x][p_cur.y - i] == 0)
			p_list[p_num ++] = Point(p_cur.x, p_cur.y - i);
		// 1)
	for(int i=1; i<6 && VALID(p_cur.y + i); i++)
		if (game->map[p_cur.x][p_cur.y + i] == 0)
			p_list[p_num ++] = Point(p_cur.x, p_cur.y + i);
		// 2)
	for(int i=1; i<6 && VALID(p_cur.x + i) && VALID(p_cur.y - i); i++)
		if (game->map[p_cur.x + i][p_cur.y - i] == 0)
			p_list[p_num ++] = Point(p_cur.x + i, p_cur.y - i);
		// 3)
	for(int i=1; i<6 && VALID(p_cur.x - i) && VALID(p_cur.y + i); i++)
		if (game->map[p_cur.x - i][p_cur.y + i] == 0)
			p_list[p_num ++] = Point(p_cur.x - i, p_cur.y + i);
		// 4)
	for(int i=1; i<6 && VALID(p_cur.x + i); i++)
		if (game->map[p_cur.x + i][p_cur.y] == 0)
			p_list[p_num ++] = Point(p_cur.x + i, p_cur.y);
		// 5)
	for(int i=1; i<6 && VALID(p_cur.x - i); i++)
		if (game->map[p_cur.x - i][p_cur.y] == 0)
			p_list[p_num ++] = Point(p_cur.x - i, p_cur.y);
		// 6)
	for(int i=1; i<6 && VALID(p_cur.x + i) && VALID(p_cur.y + i); i++)
		if (game->map[p_cur.x + i][p_cur.y + i] == 0)
			p_list[p_num ++] = Point(p_cur.x + i, p_cur.y + i);
		// 7)
	for(int i=1; i<6 && VALID(p_cur.x - i) && VALID(p_cur.y - i); i++)
		if (game->map[p_cur.x - i][p_cur.y - i] == 0)
			p_list[p_num ++] = Point(p_cur.x - i, p_cur.y - i);
	
	// ����ÿ����Ĺ���ֵ��ȡ�÷���ߵĵ���Ϊ���ӵ�
	int score[8][4];
	int max_score = -1;
	int cur_score = 0;
	Point best_point(-1, -1);
	for(int i=0; i<p_num; i++)
	{
		p_cur = p_list[i];
		memset(score, 0, sizeof(score));
		cur_score = 0;
		for(int j=0; j<8; j++)
		{
			int x_c, y_c;
			x_c = xChange(j);
			y_c = yChange(j);
			if(VALID(p_cur.x + x_c) && VALID(p_cur.y + y_c))
			{
				if(game->map[p_cur.x + x_c][p_cur.y + y_c] == 0)
				{
					score[j][0] = 0;
					score[j][1] = 0;
					score[j][2] = 1;
					score[j][3] = 1;
					if(VALID(p_cur.x + (2*x_c)) && VALID(p_cur.y + (2*y_c)) && game->map[p_cur.x + (2*x_c)][p_cur.y + (2*y_c)] != 0)
					{
						int color = 3;
						if(game->map[p_cur.x + (2*x_c)][p_cur.y + (2*y_c)] == 1)
							color = 2;
						for(int k=2; k<6 && VALID(p_cur.x + (k*x_c)) && VALID(p_cur.y + (k*y_c)); k++) {
							if(game->map[p_cur.x + (k*x_c)][p_cur.y + (k*y_c)] == color -1)
								score[j][color]++;
							else break;
						}
					}
				}
				if(game->map[p_cur.x + x_c][p_cur.y + y_c] == 1)
				{
					score[j][1] = 0;
					score[j][3] = 0;
					int k, l;
					for(k=1, l=1; k<6 && VALID(p_cur.x + (k*x_c)) && VALID(p_cur.y + (k*y_c)); k++)
					{
						if(l == game->map[p_cur.x + (k*x_c)][p_cur.y + (k*y_c)])
							score[j][0]++;
						else break;
					}
					score[j][2] = score[j][0];
					if(VALID(p_cur.x + (k*x_c)) && VALID(p_cur.y + (k*y_c)) && game->map[p_cur.x + (k*x_c)][p_cur.y + (k*y_c)] == 0)
					{
						score[j][2] ++;
						for(k++; VALID(p_cur.x + (k*x_c)) && VALID(p_cur.y + (k*y_c)) && game->map[p_cur.x + (k*x_c)][p_cur.y + (k*y_c)] == l; k++)
							score[j][2] ++;
					}
				}
				else
				{
					score[j][0] = 0;
					score[j][2] = 0;
					int k, l;
					for(k=1, l=2; k<6 && VALID(p_cur.x + (k*x_c)) && VALID(p_cur.y + (k*y_c)); k++)
					{
						if(l == game->map[p_cur.x + (k*x_c)][p_cur.y + (k*y_c)])
							score[j][1]++;
						else break;
					}
					score[j][3] = score[j][1];
					if(VALID(p_cur.x + (k*x_c)) && VALID(p_cur.y + (k*y_c)) && game->map[p_cur.x + (k*x_c)][p_cur.y + (k*y_c)] == 0)
					{
						score[j][3] ++;
						for(k++; VALID(p_cur.x + (k*x_c)) && VALID(p_cur.y + (k*y_c)) && game->map[p_cur.x + (k*x_c)][p_cur.y + (k*y_c)] == l; k++)
							score[j][3] ++;
					}
				}
			}
		}
		// �ж��Ƿ��ܳ�5, ����ǵĻ�����100000�֣�
		for(int j=0; j<8; j+=2)
		{
			if((score[j][0] + score[j+1][0]) > 3)
				cur_score += 100000;
			else if((score[j][1] + score[j+1][1]) > 3)
				cur_score += 100000;
		}
		// �ж��Ƿ��ܳɻ�4������˫��4��������4��3������ǵĻ�����20000��;
			// ��4 and ˫��4
		for(int j=0, k=0; j<8; j++) {
			if((score[j][2] + score[j+1][0]) > 3) {
				k ++;
				if(k > 1) {
					cur_score += 20000;
					break;
				}
			}
		}
		for(int j=0, k=0; j<8; j++) {
			if((score[j][3] + score[j+1][1]) > 3) {
				k ++;
				if(k > 1) {
					cur_score += 20000;
					break;
				}
			}
		}
			// ��4��3
		for(int j=0, l=1; j<8; j++)
			if((score[j][2] + score[j+1][0]) > 3) {
				for(int k=0; k<j; k++)
					if((score[k][2] + score[k+1][2]) > 3)
						{l=0;cur_score += 10000;break;}
				for(int k=j+1; k<8 && l; k++)
					if((score[k][2] + score[k+1][2]) > 3)
						{cur_score += 10000;break;}
				break;
			}
		for(int j=0, l=1; j<8; j++)
			if((score[j][3] + score[j+1][1]) > 3) {
				for(int k=0; k<j; k++)
					if((score[k][3] + score[k+1][3]) > 3)
						{l=0;cur_score += 10000;break;}
				for(int k=j+1; k<8 && l; k++)
					if((score[k][3] + score[k+1][3]) > 3)
						{l=0;cur_score += 10000;break;}
				break;
			}
		// �ж��Ƿ��ѳ�˫��3������ǵĻ�����5000�֣�
		for(int j=0, k=0; j<8; j+=2)
			if((score[j][2] + score[j+1][2]) > 3) {
				k ++;
				if(k>1)
					{cur_score += 5000;break;}
			}
		for(int j=0, k=0; j<8; j+=2)
			if((score[j][3] + score[j+1][3]) > 3) {
				k ++;
				if(k>1)
					{cur_score += 5000;break;}
			}
		// �ж��Ƿ����3��3������ǵĻ�����1000�֣�
		bool l_3 = false, d_3 = false;
		for(int j=0; j<8; j++)
		{
			if((score[j][2] + score[j+1][2]) > 3)
				l_3 = true;
			else if((score[j][2] + score[j+1][0]) > 2)
				d_3 = true;
		}
		if(l_3 && d_3)
			cur_score += 1000;
		l_3 = false; d_3 = false;
		for(int j=0; j<8; j++)
		{
			if((score[j][3] + score[j+1][3]) > 3)
				l_3 = true;
			else if((score[j][3] + score[j+1][1]) > 2)
				d_3 = true;
		}
		if(l_3 && d_3)
			cur_score += 1000;
		// �ж��Ƿ��ܳ���4������ǵĻ�����500�֣�
		for(int j=0; j<8; j++)
			if((score[j][2] + score[j+1][0]) > 3)
				{cur_score += 500;break;}
		for(int j=0; j<8; j++)
			if((score[j][3] + score[j+1][1]) > 3)
				{cur_score += 500;break;}
		// �ж��Ƿ��ܳɵ���3������ǵĻ�����200�֣�
		for(int j=0; j<8; j+=2)
			if((score[j][2] + score[j+1][2]) > 3)
				{cur_score += 200;break;}
		for(int j=0; j<8; j+=2)
			if((score[j][3] + score[j+1][3]) > 3)
				{cur_score += 200;break;}
		// �ж��Ƿ��ܳ���3������ǵĻ�����100�֣�
		for(int j=0; j<8; j++)
			if((score[j][2] + score[j+1][0]) > 2)
				{cur_score += 100;break;}
		for(int j=0; j<8; j++)
			if((score[j][3] + score[j+1][1]) > 2)
				{cur_score += 100;break;}
		// �ж��Ƿ��ܳɻ�2������ǵĻ�����5�֣�
		for(int j=0; j<8; j++)
			if((score[j][2] + score[j+1][2]) > 2)
				{cur_score += 5;break;}
		for(int j=0; j<8; j++)
			if((score[j][3] + score[j+1][3]) > 2)
				{cur_score += 5;break;}
		// �ж��Ƿ��ܳ���2������ǵĻ�����3�֡� 
		for(int j=0; j<8; j++)
			if((score[j][2] + score[j+1][0]) > 1)
				{cur_score += 3;break;}
		for(int j=0; j<8; j++)
			if((score[j][3] + score[j+1][1]) > 1)
				{cur_score += 3;break;}
		if(max_score < cur_score)
		{
			max_score = cur_score;
			best_point = p_cur;
		}
	}
	// default measure
	if(best_point == Point(-1, -1))
	{
		for(int i=0; i<MAX_NUM; i++)
			for(int j=0; j<MAX_NUM; j++)
				if(game->map[i][j] == 0)
					return Point(i, j);
	}
	return best_point;
}

int xChange(int mode)
{
	switch(mode)
	{
		case 0:return 0;
		case 1:return 0;
		case 2:return 1;
		case 3:return -1;
		case 4:return 1;
		case 5:return -1;
		case 6:return 1;
		case 7:return -1;
		default :return 0;
	}
}

int yChange(int mode)
{
	switch(mode)
	{
		case 0:return -1;
		case 1:return 1;
		case 2:return -1;
		case 3:return 1;
		case 4:return 0;
		case 5:return 0;
		case 6:return 1;
		case 7:return -1;
		default :return 0;
	}
}