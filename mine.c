#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//扫雷游戏

#define MAX_ROW 9
#define MAX_COL 9
#define MINE_MAX_COUNT 10

int Menu(){
	printf("=================\n");
	printf("欢迎来到扫雷游戏!\n");
	printf("1. 开始游戏\n");
	printf("0. 结束游戏\n");
	printf("=================\n");
	printf("请输入您的选择: ");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

void Init(char showMap[MAX_ROW][MAX_COL],
	char mineMap[MAX_ROW][MAX_COL]){
	// 1.初始化 showMap, 把每个位置都设为 *
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			showMap[row][col] = '*';
		}
	}
	// 2.初始化 mineMap, 先把所有位置都设为 '0',
	//   再随机产生若干个'1'
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
		printf("请输入您要翻开的位置: ");
		scanf("%d%d", row, col);
		if(row < 0 || *row >= MAX_ROW
			|| col < 0 || *col >= MAX_COL){
			printf("您的输入有误!\n");
			continue;
		}
		if(showMap[*row][*col] != '*'){
			printf("此位置已经翻开了!\n");
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
	//把 整数 count 转换为 字符类型 的数字
	showMap[row][col] = count + '0';
	// 如果需要实现连续翻开的话, 就在这里判定是否是 0
	// 递归调用当前的 Update 函数, 
	// 递归的时候传入的 row 和 col 就是当前位置的相邻位置
}


void Game(){
	// 1. 创建地图并初始化
	char showMap[MAX_ROW][MAX_COL];
	char mineMap[MAX_ROW][MAX_COL];
	Init(showMap, mineMap);
	int notMineCount = 0;
	while(1){
		// 2. 打印地图
		// TODO 这个操作仅限于测试阶段使用, 程序发布的时候应该要去掉
		Print(mineMap);
		printf("\n");
		Print(showMap);
		// 3. 玩家翻开指定位置(输入坐标)
		// 4. 对玩家的输入进行校验
		int row = 0;
		int col = 0;
		Input(showMap, &row, &col);
		// 5. 是否踩雷了, 如果踩雷, 直接游戏失败
		if (mineMap[row][col] == '1'){
			Print(showMap);
			printf("游戏失败!\n");
			break;
		}
		// 6. 如果翻开的是最后一个位置, 游戏胜利
		notMineCount++;
		if(notMineCount == MAX_ROW * MAX_COL - MINE_MAX_COUNT){
			Print(showMap);
			printf("游戏胜利!\n");
			break;
		}
		// 7. 游戏需要继续, 翻开的格子会变成一个数字.
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
			printf("您的输入有误!\n");
		}
	}
	system("pause");
	return 0;
}


////五子棋游戏
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define MAX_ROW 5
//#define MAX_COL 5
//
////棋盘初始化
//void Init(char chessBoard[MAX_ROW][MAX_COL]){
//	for (int row = 0; row < MAX_ROW; row++){
//		for (int col = 0; col < MAX_COL; col++){
//			chessBoard[row][col] = ' ';
//		}
//	}
//	srand((unsigned int)time(0));
//}
////打印棋盘
//void Print(char chessBoard[MAX_ROW][MAX_COL]){
//	printf("+---+---+---+---+---+\n");
//	for (int row = 0; row < MAX_ROW; row++){
//		for (int col = 0; col < MAX_COL; col++){
//			// %c 表示打印一个字符
//			printf("| %c ", chessBoard[row][col]);
//		}
//		printf("|\n+---+---+---+---+---+\n");
//	}
//}
//
//void PlayerMove(char chessBoard[MAX_ROW][MAX_COL]){
//	//玩家落子
//	printf("玩家落子 !\n");
//	while (1){
//		printf("请输入您要落子的位置(用空格隔开): \n");
//		int row = 0;
//		int col = 0;
//		// scanf 的格式化字符串要求更严格, 稍有不慎就会写错
//		scanf("%d %d", &row, &col);
//		if (row < 0 || row >= MAX_ROW
//			|| col < 0 || col >= MAX_COL){
//			//用户的输入有误
//			printf("您的输入有误!\n");
//			continue;
//		}
//		if (chessBoard[row][col] != ' '){
//			printf("该位置已经有子了!\n");
//			continue;
//		}
//		chessBoard[row][col] = 'X';
//		break;
//	}
//}
//
//void ComputerMove(char chessBoard[MAX_ROW][MAX_COL]){
//	printf("电脑落子!\n");
//	//产生一组随机数,产生0,1,2 需%3,产生0,1,2,3,需%4.
//	while (1){
//		int row = rand() % MAX_ROW;
//		int col = rand() % MAX_COL;
//		if (chessBoard[row][col] != ' '){
//			//此处已经有子了,需要重新随机
//			continue;
//		}
//		chessBoard[row][col] = '0';
//		break;
//	}
//}
//
//// 棋盘满了, 返回 1, 否则返回 0
//int IsFull(char chessBoard[MAX_ROW][MAX_COL]){
//	// 查找下看看是否能找到空格, 如果存在空格, 说明没满
//	// 如果不存在空格, 就满了
//	for (int row = 0; row < MAX_ROW; row++){
//		for (int col = 0; col < MAX_COL; col++){
//			if (chessBoard[row][col] == ' '){
//				return 0;
//			}
//		}
//	}
//	return 1;
//}
//// 这个函数不光要告诉我们游戏是否结束, 也要告诉谁赢了
//// X 表示玩家赢了
//// 0 表示电脑赢了
//// ' ' 表示胜负未分
//// Q 表示和棋
//char Check(char chessBoard[MAX_ROW][MAX_COL]){
//	// 1. 先检查所有行
//	for (int row = 0; row < MAX_ROW; row++){
//		if (chessBoard[row][0] != ' '
//			&& chessBoard[row][0] == chessBoard[row][1]
//			&& chessBoard[row][0] == chessBoard[row][2]
//			&& chessBoard[row][0] == chessBoard[row][3]
//			&& chessBoard[row][0] == chessBoard[row][4]){
//			return chessBoard[row][0];
//		}
//	}
//	// 2. 再检查所有列
//	for (int col = 0; col < MAX_COL; col++){
//		if (chessBoard[0][col] != ' '
//			&& chessBoard[0][col] == chessBoard[1][col]
//			&& chessBoard[0][col] == chessBoard[2][col]
//			&& chessBoard[0][col] == chessBoard[3][col]
//			&& chessBoard[0][col] == chessBoard[4][col]){
//			return chessBoard[0][col];
//		}
//	}
//	// 3. 再检查对角线
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
////执行这个函数, 就进行了一局游戏.
//void Game(){
//	// 1. 创建棋盘,并初始化棋盘(每个位置都设为空格)
//	char chessBoard[MAX_ROW][MAX_COL];
//	Init(chessBoard);
//	char winner = ' ';
//	while (1){
//		// 2. 打印棋盘(第一次打印的是空白棋盘)
//		Print(chessBoard);
//		// 3. 玩家落子(通过输入坐标的方式制定位置)
//		PlayerMove(chessBoard);
//		// 4. 判断一下游戏是否结束
//		winner = Check(chessBoard);
//		if (winner != ' '){
//			break;
//		}
//		// 5. 电脑落子(随机落子)
//		ComputerMove(chessBoard);
//		// 6. 再次判断游戏是否结束
//		winner = Check(chessBoard);
//		if (winner != ' '){
//			break;
//		}
//	}
//	Print(chessBoard);
//	if (winner == 'X'){
//		printf("恭喜你,你赢了!\n");
//	}
//	else if (winner == '0'){
//		printf("你真菜, 电脑你都下不过!\n");
//	}
//	else{
//		printf("呀, 你和电脑五五开!\n");
//	}
//}
//
////先写一个基本的交互菜单
//
//int Menu(){
//	printf("===================\n");
//	printf("欢迎来到五子棋游戏!\n");
//	printf("1. 开始游戏\n");
//	printf("0. 结束游戏\n");
//	printf("===================\n");
//	printf("请输入您的选择: \n");
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
//			printf("您的输入有误,请重新输入!\n");
//			Menu();
//		}
//	}
//	system("pause");
//	return 0;
//
//}