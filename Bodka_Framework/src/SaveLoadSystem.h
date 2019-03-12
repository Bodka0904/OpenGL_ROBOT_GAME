#pragma once
#include "Transform.h"
#include <string>
#include <fstream>


class Save
{
public:
	Save(std::string filename);
	~Save();
	void FreeMemory();
	void UpdateObjects(Transform& transform);
	void SaveAll();
	

	

private:
	static constexpr int numOfObjects = 2;
	int numSavedObjects = 0;
	std::string filename;
	Transform* objects[numOfObjects];
	

	
	
	
	float x[numOfObjects];
	float y[numOfObjects];
	float z[numOfObjects];
	
	float rx[numOfObjects];
	float ry[numOfObjects];
	float rz[numOfObjects];
		
};


class Load
{
public:
	Load(std::string filename);
	void LoadLastGame();
	void UpdateObjects(Transform& transform);

private:
	static constexpr int numOfObjects = 5;
	int numOfLoadedObjects = 0;
	
	std::string filename;
	float x[numOfObjects];
	float y[numOfObjects];
	float z[numOfObjects];

	float rx[numOfObjects];
	float ry[numOfObjects];
	float rz[numOfObjects];

};

