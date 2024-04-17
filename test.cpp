#include<graphics.h>
char board_data[3][3] =
{
	{'_','_','_'},
	{'_','_','_'},
	{'_','_','_'},

};

char current_piece = 'o';

//���ָ�����ӵ�����Ƿ��ʤ
bool CheckWin(char c)
{
	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c)
		return true;
	if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c)
		return true;
	if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][1] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c)
	    return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c)
		return true;

	return false;
}
//��⵱ǰ�Ƿ����ƽ��
bool CheckDraw()
{
	int count=0;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (board_data[i][j] == 'o' || board_data[i][j] == 'x')
				count++;
		}
	}
	if (count == 9)
		return true;
	else
		return false;
}
//������������
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);

}
//��������
void DrawPiece()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			switch (board_data[i][j])
			{
			case 'o':
					circle(200 * j + 100, 200 * i + 100, 100);
				break;
			case'x':
				line(200 * j, 200 * i, 200 * (j + 1), 200 * (i + 1));
				line(200 * (j+1), 200 * i, 200 * j , 200 * (i + 1));
				break;
			case'_':
				break;
			default:
				break;
			}
		}
	}
}
//������ʾ��Ϣ
void DrawTipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("��ǰ�������ͣ�%c"), current_piece);

	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}


int main()
{
	initgraph(600, 600);
	 
	bool running = true;

	ExMessage msg;

	BeginBatchDraw();

	while (running)
	{
		while (peekmessage(&msg))
		{
			//���������������Ϣ
			if (msg.message == WM_LBUTTONDOWN)
			{
				//������λ��
				int x = msg.x;
				int y = msg.y;

				int index_x = x / 200;
				int index_y = y / 200;

				//��������
				if (board_data[index_y][index_x]=='_')
				{
					board_data[index_y][index_x] = current_piece;
					
					//�л���������
					if (current_piece == 'o')
					{
						current_piece = 'x';
					}
					else
					{
						current_piece = 'o';
					}
				}
			}

		}


		cleardevice();
		DrawBoard();
		DrawPiece();
		DrawTipText();

		FlushBatchDraw();
		if (CheckWin('x'))
		{
			MessageBox(GetHWnd(), _T("x ��һ�ʤ"), _T("��Ϸ����"), MB_OK);
			running = false;
		}
		else if (CheckWin('o'))
		{
			MessageBox(GetHWnd(), _T("o ��һ�ʤ"), _T("��Ϸ����"), MB_OK);
			running = false;
		}
		else if (CheckDraw())
		{
			MessageBox(GetHWnd(), _T("ƽ�֣�"), _T("��Ϸ����"), MB_OK);
			running = false;
		}

	}
	EndBatchDraw();

	return 0;
}