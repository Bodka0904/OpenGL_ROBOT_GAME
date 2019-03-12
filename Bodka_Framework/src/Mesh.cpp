#include "Mesh.h"



Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices)
{
	IndexedModel model;
	std::string filename;
	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GettexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}


	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	InitMesh(model,filename);
	

}
Mesh::Mesh(const std::string & filename)
{
	

	IndexedModel model = OBJModel(filename).ToIndexedModel();
	InitMesh(model,filename);
}

void Mesh::Init(const std::string & filename)
{
	
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	
	InitMesh(model,filename);
	
}

void Mesh::InitNew(Vertex * vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices)
{

	IndexedModel model;
	std::string filename;
	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GettexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}


	InitMesh(model, filename);
}

float Mesh::GetWidthX()
{
	return widthX;
}

float Mesh::GetWidthZ()
{
	return widthZ;
}

float Mesh::GetHeight()
{
	return height;
}

glm::vec3 Mesh::GetCenter()
{
	return center;
}



Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT,0);

	glBindVertexArray(0);
	
}

void Mesh::InitMesh(const IndexedModel & model, std::string filename)
{
	for (int i = 0; i < model.positions.size(); ++i)
	{
		positions.push_back(model.positions[i]);
	}
	float tempBig = positions[0].x;

	for (int i = 0; i < positions.size(); ++i)
	{
		if (positions[i].x > tempBig)
		{
			tempBig = positions[i].x;
		}
	}
	
	float tempLow = tempBig;

	for (int i = 0; i < positions.size(); ++i)
	{
		if (positions[i].x < tempLow)
		{
			tempLow = positions[i].x;
		}
	}

	center.x = (tempLow + tempBig) / 2;
	widthX = abs(tempLow) + abs(tempBig);

	tempBig = positions[0].y;

	for (int i = 0; i < positions.size(); ++i)
	{
		if (positions[i].x > tempBig)
		{
			tempBig = positions[i].y;
		}
	}


	tempLow = tempBig;

	for (int i = 0; i < positions.size(); ++i)
	{
		if (positions[i].y < tempLow)
		{
			tempLow = positions[i].y;
		}
	}

	center.y = (tempLow + tempBig) / 2;
	height = abs(tempLow) + abs(tempBig);

	tempBig = positions[0].z;

	for (int i = 0; i < positions.size(); ++i)
	{
		if (positions[i].z > tempBig)
		{
			tempBig = positions[i].z;
		}
	}


	tempLow = tempBig;

	for (int i = 0; i < positions.size(); ++i)
	{
		if (positions[i].z < tempLow)
		{
			tempLow = positions[i].z;
		}
	}

	center.z = (tempLow + tempBig) / 2;
	widthZ = abs(tempLow) + abs(tempBig);


	

	m_drawCount = model.indices.size();
	
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);


	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//It tells how to read our attributes.

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);//It tells how to read our attributes.

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	

	glBindVertexArray(0); //we unbind it;
}





