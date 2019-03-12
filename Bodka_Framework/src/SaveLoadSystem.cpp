#include "SaveLoadSystem.h"



Save::Save(std::string filename)
{
	this->filename = filename;
	
}


Save::~Save()
{
}

void Save::FreeMemory()
{
	for (int i = 0; i < numOfObjects; ++i)
	{
		objects[i] = NULL;
	}
	numSavedObjects = 0;
}

void Save::UpdateObjects(Transform& transform)
{
	objects[numSavedObjects] = &transform;
	
	if (numSavedObjects < numOfObjects)
	{
		numSavedObjects++;
	}

	

}

void Save::SaveAll()
{
	
	std::ofstream data(filename.c_str(),	std::ios_base::binary);
	
	data << "POSITIONS AND ROTATIONS: \n";
	
	for (int i = 0; i < numSavedObjects; ++i)
	{
		x[i] = objects[i]->GetPos().x;
		y[i] = objects[i]->GetPos().y;
		z[i] = objects[i]->GetPos().z;
	
		rx[i] = objects[i]->GetRot().x;
		ry[i] = objects[i]->GetRot().y;
		rz[i] = objects[i]->GetRot().z;
	
		
		data << x[i];
		data << "\n";
		data << y[i];
		data << "\n";
		data << z[i];
		data << "\n";
		data << rx[i];
		data << "\n";
		data << ry[i];
		data << "\n";
		data << rz[i];
		data << "\n";
	
	
	}
	data.close();
}

Load::Load(std::string filename)
{
	this->filename = filename;
}

void Load::LoadLastGame()
{
	std::ifstream infile("data.txt",std::ios_base::binary);

	std::string file;
	while (std::getline(infile, file))
	{
		for (int i = 0; i < numOfObjects; ++i)
		{
			infile >> x[i];
			infile >> y[i];
			infile >> z[i];
			
			infile >> rx[i];
			infile >> ry[i];
			infile >> rz[i];
		}
	}
	infile.close();
	numOfLoadedObjects = 0;
}

void Load::UpdateObjects(Transform & transform)
{
	transform.SetPos(glm::vec3(x[numOfLoadedObjects], y[numOfLoadedObjects], z[numOfLoadedObjects]));
	transform.SetRot(glm::vec3(rx[numOfLoadedObjects], ry[numOfLoadedObjects], rz[numOfLoadedObjects]));
	
	numOfLoadedObjects++;
}
