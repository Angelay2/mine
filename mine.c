#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//ɨ����Ϸ

#define MAX_ROW 9
#define MAX_COL 9
#define MINE_MAX_COUNT 10

int Menu(){
	printf("=================\n");
	printf("��ӭ����ɨ����Ϸ!\n");
	printf("1. ��ʼ��Ϸ\n");
	printf("0. ������Ϸ\n");
	printf("=================\n");
	printf("����������ѡ��: ");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

void Init(char showMap[MAX_ROW][MAX_COL],
	char mineMap[MAX_ROW][MAX_COL]){
	// 1.��ʼ�� showMap, ��ÿ��λ�ö���Ϊ *
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			showMap[row][col] = '*';
		}
	}
	// 2.��ʼ�� mineMap, �Ȱ�����λ�ö���Ϊ '0',
	//   ������������ɸ�'1'
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			mineMap[row][col] = '0';
		}
	}
	srand((unsigned int)time(0));
	int count = 10;
	while(count > 0){
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (mineMap[row][col] == '1'){
			continue;
		}
		mineMap[row][col] = '1';
		count--;

	}
}

void Print(char showMap[MAX_ROW][MAX_COL]){
	printf("  | ");
	for (int col = 0; col < MAX_COL; col++){
		printf("%d ", col);
	}
	printf("\n");
	printf("--+------------------\n");
	for (int row = 0; row < MAX_ROW; row++){
		printf(" %d| ", row);
		for (int col = 0; col < MAX_COL; col++){
			printf("%c ", showMap[row][col]);
		}
		printf("\n");
	}
}

void Input(char showMap[MAX_ROW][MAX_COL],int* row, int* col){
	while(1){
		printf("��������Ҫ������λ��: ");
		scanf("%d%d", row, col);
		if(row < 0 || *row >= MAX_ROW
			|| col < 0 || *col >= MAX_COL){
			printf("������������!\n");
			continue;
		}
		if(showMap[*row][*col] != '*'){
			printf("��λ���Ѿ�������!\n");
			continue;
		}
		break;
	}
}

void Update(char showMap[MAX_ROW][MAX_COL],
	char mineMap[MAX_ROW][MAX_COL],
	int row, int col){
	int count = 0;
	for (int r = row - 1; r <= row + 1; r++){
		for (int c = col - 1; c <= col + 1; c++){
			if (row < 0 || row >= MAX_ROW
				|| col < 0 || col >= MAX_COL){
				continue;
			}
			if (mineMap[r][c] == '1'){
				count++;
			}
		}
	}
	//�� ���� count ת��Ϊ �ַ����� ������
	showMap[row][col] = count + '0';
	// �����Ҫʵ�����������Ļ�, ���������ж��Ƿ��� 0
	// �ݹ���õ�ǰ�� Update ����, 
	// �ݹ��ʱ����� row �� col ���ǵ�ǰλ�õ�����λ��
}


void Game(){
	// 1. ������ͼ����ʼ��
	char showMap[MAX_ROW][MAX_COL];
	char mineMap[MAX_ROW][MAX_COL];
	Init(showMap, mineMap);
	int notMineCount = 0;
	while(1){
		// 2. ��ӡ��ͼ
		// TODO ������������ڲ��Խ׶�ʹ��, ���򷢲���ʱ��Ӧ��Ҫȥ��
		Print(mineMap);
		printf("\n");
		Print(showMap);
		// 3. ��ҷ���ָ��λ��(��������)
		// 4. ����ҵ��������У��
		int row = 0;
		int col = 0;
		Input(showMap, &row, &col);
		// 5. �Ƿ������, �������, ֱ����Ϸʧ��
		if (mineMap[row][col] == '1'){
			Print(showMap);
			printf("��Ϸʧ��!\n");
			break;
		}
		// 6. ��������������һ��λ��, ��Ϸʤ��
		notMineCount++;
		if(notMineCount == MAX_ROW * MAX_COL - MINE_MAX_COUNT){
			Print(showMap);
			printf("��Ϸʤ��!\n");
			break;
		}
		// 7. ��Ϸ��Ҫ����, �����ĸ��ӻ���һ������.
		Update(showMap, mineMap, row, col);
	}
	
}
int main(){
	while (1){
		int choice = Menu();
		if (choice == 1){
			Game();
		}
		else if (choice == 0){
			printf("goodbye!\n");
			break;
		}
		else{
			printf("������������!\n");
		}
	}
	system("pause");
	return 0;
}


////��������Ϸ
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define MAX_ROW 5
//#define MAX_COL 5
//
////���̳�ʼ��
//void Init(char chessBoard[MAX_ROW][MAX_COL]){
//	for (int row = 0; row < MAX_ROW; row++){
//		for (int col = 0; col < MAX_COL; col++){
//			chessBoard[row][col] = ' ';
//		}
//	}
//	srand((unsigned int)time(0));
//}
////��ӡ����
//void Print(char chessBoard[MAX_ROW][MAX_COL]){
//	printf("+---+---+---+---+---+\n");
//	for (int row = 0; row < MAX_ROW; row++){
//		for (int col = 0; col < MAX_COL; col++){
//			// %c ��ʾ��ӡһ���ַ�
//			printf("| %c ", chessBoard[row][col]);
//		}
//		printf("|\n+---+---+---+---+---+\n");
//	}
//}
//
//void PlayerMove(char chessBoard[MAX_ROW][MAX_COL]){
//	//�������
//	printf("������� !\n");
//	while (1){
//		printf("��������Ҫ���ӵ�λ��(�ÿո����): \n");
//		int row = 0;
//		int col = 0;
//		// scanf �ĸ�ʽ���ַ���Ҫ����ϸ�, ���в����ͻ�д��
//		scanf("%d %d", &row, &col);
//		if (row < 0 || row >= MAX_ROW
//			|| col < 0 || col >= MAX_COL){
//			//�û�����������
//			printf("������������!\n");
//			continue;
//		}
//		if (chessBoard[row][col] != ' '){
//			printf("��λ���Ѿ�������!\n");
//			continue;
//		}
//		chessBoard[row][col] = 'X';
//		break;
//	}
//}
//
//void ComputerMove(char chessBoard[MAX_ROW][MAX_COL]){
//	printf("��������!\n");
//	//����һ�������,����0,1,2 ��%3,����0,1,2,3,��%4.
//	while (1){
//		int row = rand() % MAX_ROW;
//		int col = rand() % MAX_COL;
//		if (chessBoard[row][col] != ' '){
//			//�˴��Ѿ�������,��Ҫ�������
//			continue;
//		}
//		chessBoard[row][col] = '0';
//		break;
//	}
//}
//
//// ��������, ���� 1, ���򷵻� 0
//int IsFull(char chessBoard[MAX_ROW][MAX_COL]){
//	// �����¿����Ƿ����ҵ��ո�, ������ڿո�, ˵��û��
//	// ��������ڿո�, ������
//	for (int row = 0; row < MAX_ROW; row++){
//		for (int col = 0; col < MAX_COL; col++){
//			if (chessBoard[row][col] == ' '){
//				return 0;
//			}
//		}
//	}
//	return 1;
//}
//// �����������Ҫ����������Ϸ�Ƿ����, ҲҪ����˭Ӯ��
//// X ��ʾ���Ӯ��
//// 0 ��ʾ����Ӯ��
//// ' ' ��ʾʤ��δ��
//// Q ��ʾ����
//char Check(char chessBoard[MAX_ROW][MAX_COL]){
//	// 1. �ȼ��������
//	for (int row = 0; row < MAX_ROW; row++){
//		if (chessBoard[row][0] != ' '
//			&& chessBoard[row][0] == chessBoard[row][1]
//			&& chessBoard[row][0] == chessBoard[row][2]
//			&& chessBoard[row][0] == chessBoard[row][3]
//			&& chessBoard[row][0] == chessBoard[row][4]){
//			return chessBoard[row][0];
//		}
//	}
//	// 2. �ټ��������
//	for (int col = 0; col < MAX_COL; col++){
//		if (chessBoard[0][col] != ' '
//			&& chessBoard[0][col] == chessBoard[1][col]
//			&& chessBoard[0][col] == chessBoard[2][col]
//			&& chessBoard[0][col] == chessBoard[3][col]
//			&& chessBoard[0][col] == chessBoard[4][col]){
//			return chessBoard[0][col];
//		}
//	}
//	// 3. �ټ��Խ���
//	if (chessBoard[0][0] != ' '
//		&& chessBoard[0][0] == chessBoard[1][1]
//		&& chessBoard[0][0] == chessBoard[2][2]
//		&& chessBoard[0][0] == chessBoard[3][3]
//		&& chessBoard[0][0] == chessBoard[4][4]){
//		return chessBoard[0][0];
//	}
//	if (chessBoard[0][4] != ' '
//		&& chessBoard[0][4] == chessBoard[1][3]
//		&& chessBoard[0][4] == chessBoard[2][2]
//		&& chessBoard[0][4] == chessBoard[3][1]
//		&& chessBoard[0][4] == chessBoard[4][0]){
//		return chessBoard[0][4];
//	}
//	if (IsFull(chessBoard) == ' '){
//		return 'Q';
//	}
//	return ' ';
//}
//
//
////ִ���������, �ͽ�����һ����Ϸ.
//void Game(){
//	// 1. ��������,����ʼ������(ÿ��λ�ö���Ϊ�ո�)
//	char chessBoard[MAX_ROW][MAX_COL];
//	Init(chessBoard);
//	char winner = ' ';
//	while (1){
//		// 2. ��ӡ����(��һ�δ�ӡ���ǿհ�����)
//		Print(chessBoard);
//		// 3. �������(ͨ����������ķ�ʽ�ƶ�λ��)
//		PlayerMove(chessBoard);
//		// 4. �ж�һ����Ϸ�Ƿ����
//		winner = Check(chessBoard);
//		if (winner != ' '){
//			break;
//		}
//		// 5. ��������(�������)
//		ComputerMove(chessBoard);
//		// 6. �ٴ��ж���Ϸ�Ƿ����
//		winner = Check(chessBoard);
//		if (winner != ' '){
//			break;
//		}
//	}
//	Print(chessBoard);
//	if (winner == 'X'){
//		printf("��ϲ��,��Ӯ��!\n");
//	}
//	else if (winner == '0'){
//		printf("�����, �����㶼�²���!\n");
//	}
//	else{
//		printf("ѽ, ��͵������忪!\n");
//	}
//}
//
////��дһ�������Ľ����˵�
//
//int Menu(){
//	printf("===================\n");
//	printf("��ӭ������������Ϸ!\n");
//	printf("1. ��ʼ��Ϸ\n");
//	printf("0. ������Ϸ\n");
//	printf("===================\n");
//	printf("����������ѡ��: \n");
//	int choice = 0;
//	scanf("%d", &choice);
//	return choice;
//}
//
//int main(){
//	while (1){
//		int choice = Menu();
//		if (choice == 1){
//			Game();
//		}
//		else if (choice == 0){
//			printf("goodbye!\n");
//		}
//		else{
//			printf("������������,����������!\n");
//			Menu();
//		}
//	}
//	system("pause");
//	return 0;
//
//}