#include "FigureThree.h"


FigureThree::FigureThree(void)
{
}


FigureThree::~FigureThree(void)
{
}


void FigureThree:: initialize(){

	glUseProgram(shaderProgram);

	glm::vec3 v0 = glm::vec3( -0.5f, 0.0f, 0.0f);
	glm::vec3 v1 = glm::vec3( -0.5f, -0.5f, 0.0f);
	glm::vec3 v3 = glm::vec3( 0.5f, -0.5f, 0.0f);
	glm::vec3 v4 = glm::vec3( 0.5f, 0.0f, 0.0f);
	glm::vec3 v5 = glm::vec3( 0.5f, 0.5f, 0.0f);

	vector<glm::vec3> v;
	v.push_back( v0 );
	v.push_back( v1 );
	v.push_back( v1 );
	v.push_back( v3 );
	v.push_back( v4 );
	v.push_back( v5 );

	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );

	GLuint VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec3), &v[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);
}

void FigureThree::draw(){

	glUseProgram(shaderProgram);

	glBindVertexArray( vertexArrayObject );
	glDrawArrays(GL_LINES,0,6);
}