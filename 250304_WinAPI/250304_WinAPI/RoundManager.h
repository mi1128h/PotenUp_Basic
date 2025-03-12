#pragma once
class RoundManager
{
	int currentRound;//���������
	int enemyCnt;//���庰 �ִ� ������
	bool isClear; //���� Ŭ���� �ߴ���
	bool gameOver; //������ ��������
	
public:

	void Init();
	void setIsClear(bool clear) { isClear = clear; }
	void IncEnemyCnt() { enemyCnt++; }
	bool getEnemy();//�� ���� ����  ,������ ��ȯ
	int getCurrentEnemyCnt() { return enemyCnt; }
	int getCurrentRound();// ���� �� ���� ��ȯ
	void GameOver(int hp); //�÷��̾� hp�� 0�̸� gameOver = true;
	bool NextTurn();
	//�� ����
    float getEnemySpeed();//�� �̵��ӵ� ���� 
	int getEnemySize();//�� ũ�� ����
	float getEnemyHp(); //�� hp ����
	bool GameClear();
};

