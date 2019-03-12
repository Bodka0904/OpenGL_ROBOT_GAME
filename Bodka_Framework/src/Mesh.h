#pragma once
#include <string>
#include <iostream>
#include "obj_loader.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <GL/glew.h>


class Vertex
{
public:
	Vertex() = default;
	
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& model = glm::vec3(0,0,0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
		
	}
	

	inline glm::vec3 * GetPos() { return &pos; }
	inline glm::vec2 * GettexCoord() {return &texCoord;}
	inline glm::vec3 * GetNormal() { return &normal; }
	inline void SetTexCoord(const glm::vec2& tex) { texCoord = tex; }
	
	


private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	
};



class Mesh
{
public:
	Mesh() = default;
	Mesh(Vertex* vertices,unsigned int numVertices,unsigned int * indices,unsigned int numIndices);
	Mesh(const std::string& filename);
	void Init(const std::string& filename);
	void InitNew(Vertex* vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices);
	float GetWidthX();
	float GetWidthZ();
	float GetHeight();

	glm::vec3 GetCenter();

	
	
	
	virtual~Mesh();
	void Draw();
	void InitMesh(const IndexedModel& model,std::string filename);
	
	

	
private:
	enum
	{
		POSITION_VB,
		
		TEXCOORD_VB,

		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned long long int m_drawCount;
	Vertex * vertices;

	float widthX;
	float widthZ;
	float height;
	glm::vec3 center;
public:
	std::vector <glm::vec3> positions;
	Transform transform;
	
	
	
	
	
};

