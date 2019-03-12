#include "Terrain.h"



Terrain::Terrain(std::string filename,float size,float h,glm::vec3 color)
	:
	m_size(size),
	m_height(h),
	color(color)
{
	SDL_Surface* img = SDL_LoadBMP(filename.c_str());
	if (!img)
	{
		std::cout << "image is not loaded" << std::endl;
	}
	std::vector<float>tmp;

	for (int i = 0; i < img->h; i++)
	{
		tmp.clear();
		for (int j = 0; j < img->w; j++)
		{
			Uint32 pixel = ((Uint32*)img->pixels)[i * img->pitch / 4 + j];

			Uint8 r, g, b;

			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			tmp.push_back((float)r / 255.0);
		}
		heights.push_back(tmp);
	}

	
	std::vector<glm::vec2> texCoords;
	

	for (int hMapX = 0; hMapX < heights.size() ; ++hMapX)
	{
		for (int hMapZ = 0; hMapZ < heights[0].size() ; ++hMapZ)
		{
			texCoords.push_back(glm::vec2(0,0));
			
			//TOP
			pos.push_back(glm::vec3(hMapX * size, heights[hMapX][hMapZ] * h, hMapZ * size));
			
			
		}
	}


	
	for (int j = 0; j < heights.size() - 1; ++j)
	{
		for (int i = 0; i < heights.size() - 1; ++i)
		{
			int start = j * heights.size() + i;
			indices.push_back(start);
			indices.push_back(start + 1);
			indices.push_back(start + heights.size());
					   
			indices.push_back(start + 1);
			indices.push_back(start + 1 + heights.size());
			indices.push_back(start + heights.size());

		}
	}
	
	
	
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);


	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(pos[0]), &pos[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);



	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	
}


Terrain::~Terrain()
{
}




void Terrain::Draw(Shader& shader,Camera& camera)
{
	
	transform.SetPos(glm::vec3(0, -10, 0));
	shader.UpdateColor(color);
	shader.Update(transform, camera);


	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_LINES,indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	
	

}

float Terrain::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

void Terrain::Collision(Transform& player)
{
	float gridSquareSize = m_size;
	
	int gridX = (int)(player.GetPos().x / gridSquareSize);
	int gridZ = (int)(player.GetPos().z / gridSquareSize);

	
	float xCoord = fmod(player.GetPos().x, gridSquareSize) / gridSquareSize;
	float zCoord = fmod(player.GetPos().z, gridSquareSize) / gridSquareSize;

	float answer;
	if (gridX >= heights.size() - 1 || gridZ >= heights.size() - 1 || gridX < 0 || gridZ < 0)
	{
		answer = player.GetPos().y;
	}
	else
	{
		if (xCoord <= 1 - zCoord)
		{
			answer = barryCentric(glm::vec3(0, (heights[gridX][gridZ] * m_height) + transform.GetPos().y, 0), glm::vec3(1,
				(heights[gridX + 1][gridZ] * m_height) + transform.GetPos().y, 0), glm::vec3(0,
				(heights[gridX][gridZ + 1] * m_height) + transform.GetPos().y, 1), glm::vec2(xCoord, zCoord));
		}
		else
		{
			answer = barryCentric(glm::vec3(1, (heights[gridX + 1][gridZ] * m_height) + transform.GetPos().y, 0), glm::vec3(1,
				(heights[gridX + 1][gridZ + 1] * m_height) + transform.GetPos().y, 1), glm::vec3(0,
				(heights[gridX][gridZ + 1] * m_height) + transform.GetPos().y, 1), glm::vec2(xCoord, zCoord));
		}
	}
	if (player.GetPos().y < answer)
	{
		player.GetPos().y = answer;
	}
}


