/***************************************************************************

    file				: Gobang.h
    modified			: 2012-07-13 20:43:34
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#ifndef GOBANG
#define GOBANG

#include "Data.h"
#include "Fltk.h"
#include <string>
using namespace std;

class Gobang
{
private:
	Point pos[400];					// the position of chess
	int step;						// The current number of steps
	char map[MAX_NUM][MAX_NUM];		// chessboard
	Player player;					// current player.
	bool over;						// is game over
	bool reply;						// is reply mode
public:
	// �����Ԫ
	friend class MyWindow;
	friend class MyBoard;
	friend Point ai();
	// ���캯��
	Gobang();
	// ���ܺ���
	bool add_step(Point point);		// �������
	void del_step();				// ɾ������
	int get_step();					// ��õ�ǰ�ܲ���
	Point get_step(int s);			// ���ָ���������ӵ�λ��
	Player get_player();			// ��õ�ǰ���
	int get_x_pos(int p);			// �����غ�����ת��������λ��
	int get_y_pos(int p);			// ������������ת��������λ��
	bool is_win();					// �����Ϸ�Ƿ����
	bool is_rep();					// ����Ƿ���¼��ģʽ
	string player_msg();			// ������ʾ��Ϣ
	bool save(string f);			// ������Ϸ��Ϣ
	bool load(string f);			// ������Ϸ��Ϣ
};

#endif