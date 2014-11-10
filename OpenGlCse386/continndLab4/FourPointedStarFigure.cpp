#include "FourPointedStarFigure.h"


FourPointedStarFigure::FourPointedStarFigure(void)
{
}


FourPointedStarFigure::~FourPointedStarFigure(void)
{
}

void FourPointedStarFigure:: initialize(){
	glUseProgram(shaderProgram);
	GLuint VBO;
	GLuint CBO;
	GLuint IBO;

	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );

	glm::vec3 v0 = glm::vec3( 0.0f, 0.75f, 0.0f);
	glm::vec3 v1 = glm::vec3( 0.25f, 0.25f, 0.0f);
	glm::vec3 v2 = glm::vec3( 0.75f, 0.0f, 0.0f);
	glm::vec3 v3 = glm::vec3( 0.25f, -0.25f, 0.0f);
	glm::vec3 v4 = glm::vec3( 0.0f, -0.75f, 0.0f);
	glm::vec3 v5 = glm::vec3( -0.25f, -0.25f, 0.0f);
	glm::vec3 v6 = glm::vec3( -0.75f, 0.0f, 0.0f);
	glm::vec3 v7 = glm::vec3( -0.25f, 0.25f, 0.0f);

	glm::vec4 c0 = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f); 
	glm::vec4 c1 = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 c2 = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f); 
	glm::vec4 c3 = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); 
	glm::vec4 c4 = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f); 
	glm::vec4 c5 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); 
	glm::vec4 c6 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); 
	glm::vec4 c7 = glm::vec4(0.2f, 0.3f, 0.7f, 1.0f); 

	vector<glm::vec3> v;
	v.push_back( v0 );
	v.push_back( v1 );
	v.push_back( v2 );
	v.push_back( v3 );
	v.push_back( v4 );
	v.push_back( v5 );
	v.push_back( v6 );
	v.push_back( v7 );

	vector<glm::vec4> c;

	c.push_back( c0 );
	c.push_back( c1 );
	c.push_back( c2 );
	c.push_back( c3 );
	c.push_back( c4 );
	c.push_back( c5 );
	c.push_back( c6 );
	c.push_back( c7 );

	vector<GLuint> indices;

	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(7);
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(3);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(7);

	glGenBuffers(1, &IBO);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 
		indices.size()* sizeof(GLuint), 
		&indices[0],
		GL_STATIC_DRAW);
	numberOfIndices = indices.size();

	glGenBuffers(1, &CBO);
	glBindBuffer( GL_ARRAY_BUFFER, CBO);
	glBufferData( GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec4), &c[0], 
		GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &VBO);
	glBindBuffer( GL_ARRAY_BUFFER, VBO);
	glBufferData( GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec3), &v[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

void FourPointedStarFigure::draw(){
	glUseProgram(shaderProgram);
	glBindVertexArray(vertexArrayObject);
	glDrawElements( GL_TRIANGLES, numberOfIndices,
		GL_UNSIGNED_INT, 0 );
}