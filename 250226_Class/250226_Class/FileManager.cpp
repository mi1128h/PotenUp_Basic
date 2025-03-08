#include "FileManager.h"
#include <fstream>
#include <iostream>

void FileManager::WriteFile(const std::string& fileName, const GameData& gameData)
{
	// fileName: save_data.txt
	std::ofstream outFile(fileName);
	if (!outFile) {
		std::cerr << "파일을 열 수 없습니다." << fileName << std::endl;
		return;
	}

	// TODO: logic
	outFile << "difficulty: " << gameData.difficulty << '\n'
		<< "playerPosX: " << gameData.playerPosX << '\n'
		<< "playerPosY: " << gameData.playerPosY << '\n'
		<< "playerGold: " << gameData.playerGold << '\n'
		<< "exitPosX: " << gameData.exitPosX << '\n'
		<< "exitPosY: " << gameData.exitPosY << '\n';

	// 안하면 메모리 누수
	outFile.close();
}

void FileManager::ReadFile(const std::string& fileName, GameData& gameData)
{
	std::ifstream inFile(fileName);
	if (!inFile) {
		std::cerr << "파일을 열 수 없습니다." << fileName << std::endl;
	}

	// 줄 바꿈, 띄어쓰기 기준으로 읽어옴
	std::string temp;
	inFile >> temp >> gameData.difficulty
		>> temp >> gameData.playerPosX
		>> temp >> gameData.playerPosY
		>> temp >> gameData.playerGold
		>> temp >> gameData.exitPosX
		>> temp >> gameData.exitPosY;

	inFile.close();
}

void FileManager::WriteFile(const std::string& fileName, const GameData& gameData, bool isBinary)
{
	if (!isBinary) WriteFile(fileName, gameData);
	else {
		std::ofstream outFile(fileName, std::ios::binary);

		if (!outFile) {
			std::cerr << "파일을 열 수 없습니다." << fileName << std::endl;
			return;
		}

		outFile.write(reinterpret_cast<const char*>(&gameData.difficulty), sizeof(gameData.difficulty));
		outFile.write(reinterpret_cast<const char*>(&gameData.playerPosX), sizeof(gameData.playerPosX));
		outFile.write(reinterpret_cast<const char*>(&gameData.playerPosY), sizeof(gameData.playerPosY));
		outFile.write(reinterpret_cast<const char*>(&gameData.playerGold), sizeof(gameData.playerGold));
		outFile.write(reinterpret_cast<const char*>(&gameData.exitPosX), sizeof(gameData.exitPosX));
		outFile.write(reinterpret_cast<const char*>(&gameData.exitPosY), sizeof(gameData.exitPosY));

		outFile.close();
	}
}

void FileManager::ReadFile(const std::string& fileName, GameData& gameData, bool isBinary)
{
	if (!isBinary) ReadFile(fileName, gameData);
	else {
		std::ifstream inFile(fileName, std::ios::binary);

		if (!inFile) {
			std::cerr << "파일을 열 수 없습니다." << fileName << std::endl;
			return;
		}

		inFile.read(reinterpret_cast<char*>(&gameData.difficulty), sizeof(gameData.difficulty));
		inFile.read(reinterpret_cast<char*>(&gameData.playerPosX), sizeof(gameData.playerPosX));
		inFile.read(reinterpret_cast<char*>(&gameData.playerPosY), sizeof(gameData.playerPosY));
		inFile.read(reinterpret_cast<char*>(&gameData.playerGold), sizeof(gameData.playerGold));
		inFile.read(reinterpret_cast<char*>(&gameData.exitPosX), sizeof(gameData.exitPosX));
		inFile.read(reinterpret_cast<char*>(&gameData.exitPosY), sizeof(gameData.exitPosY));

		inFile.close();
	}
}

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}
