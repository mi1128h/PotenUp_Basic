#pragma once

/*
	파일 관리
	파일의 내용을 읽어서 데이터로 저장(Load)
	파일에 데이터를 저장(Save)
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

	// 생성자: 리턴 타입이 없고 클래스명과 이름이 같은 함수
	FileManager();	// 인스턴스가 만들어질 때 자동으로 호출되는 함수
	// 소멸자: 앞에 ~가 붙는다
	~FileManager();	// 인스턴스가 없어질 때(메모리 해제) 자동으로 호출되는 함수
};

