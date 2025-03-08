#pragma once

/*
	���� ����
	������ ������ �о �����ͷ� ����(Load)
	���Ͽ� �����͸� ����(Save)
*/

#include "CommonDataType.h"
#include <string>

class FileManager
{
public:
	void WriteFile(const std::string& fileName, const GameData& gameData);
	void ReadFile(const std::string& fileName, GameData& gameData);
	
	void WriteFile(const std::string& fileName, const GameData& gameData, bool isBinary);
	void ReadFile(const std::string& fileName, GameData& gameData, bool isBinary);

	// ������: ���� Ÿ���� ���� Ŭ������� �̸��� ���� �Լ�
	FileManager();	// �ν��Ͻ��� ������� �� �ڵ����� ȣ��Ǵ� �Լ�
	// �Ҹ���: �տ� ~�� �ٴ´�
	~FileManager();	// �ν��Ͻ��� ������ ��(�޸� ����) �ڵ����� ȣ��Ǵ� �Լ�
};

