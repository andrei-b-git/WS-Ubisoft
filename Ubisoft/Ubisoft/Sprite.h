#include <fstream>
#include <iostream>
#include <string>

#define PI 3.14159265358979323846

class Sprite {

public:
	GLuint vao;
	int nr_indices;
	float radius;
	glm::vec3 center;
	unsigned int texture;

	glm::mat4 model_matrix;

public:
	void FlipTexture(unsigned char* image_data,int x,int y , int n)
	{
		int width_in_bytes = x * 4;
		unsigned char *top = NULL;
		unsigned char *bottom = NULL;
		unsigned char temp = 0;
		int half_height = y / 2;

		for (int row = 0; row < half_height; row++) {
			top = image_data + row * width_in_bytes;
			bottom = image_data + (y - row - 1) * width_in_bytes;
			for (int col = 0; col < width_in_bytes; col++) {
				temp = *top;
				*top = *bottom;
				*bottom = temp;
				top++;
				bottom++;
			}
		}
	}

	struct MyVertexFormat{
		glm::vec3 vertex;
		glm::vec2 texel;
	} point;

	Sprite(float xc, float yc, float _radius, int vertex_count, glm::mat4 _model_matrix, const char *filename) {

		std::vector<MyVertexFormat> vertex_buffer;
		std::vector<glm::uvec3> index_buffer;

		center = glm::vec3(xc, yc, 0.0f);
		radius = _radius;
		model_matrix = _model_matrix;

		int x, y, n;
		int force_channels = 4;
		unsigned char* image_data = stbi_load(filename, &x, &y, &n, force_channels);
		FlipTexture(image_data, x, y, n);

		if(vertex_count < 3) {
			printf ( "ERROR: Vertex count must be at least 3.\n");
			return;
		}
		if(vertex_count == 3) {
			point.vertex = glm::vec3(xc, yc+radius, 0.0f);
			point.texel = glm::vec2(0.5f, sqrt(3)/2);
			vertex_buffer.push_back(point);
			point.vertex = glm::vec3(xc+radius*sqrt(3)/2, yc-radius/2, 0.0f);
			point.texel = glm::vec2(1.0f, 0.0f);
			vertex_buffer.push_back(point);			
			point.vertex = glm::vec3(xc-radius*sqrt(3)/2, yc-radius/2, 0.0f);
			point.texel = glm::vec2(0.0f, 0.0f);
			vertex_buffer.push_back(point);			

			index_buffer.push_back(glm::uvec3(0,1,2));
		}
		if(vertex_count == 4) {
			point.vertex = glm::vec3(xc+radius/sqrt(2), yc+radius/sqrt(2), 0.0f);
			point.texel = glm::vec2(1.0f, 1.0f);
			vertex_buffer.push_back(point);
			point.vertex = glm::vec3(xc+radius/sqrt(2), yc-radius/sqrt(2), 0.0f);
			point.texel = glm::vec2(1.0f, 0.0f);
			vertex_buffer.push_back(point);
			point.vertex = glm::vec3(xc-radius/sqrt(2), yc-radius/sqrt(2), 0.0f);
			point.texel = glm::vec2(0.0f, 0.0f);
			vertex_buffer.push_back(point);
			point.vertex = glm::vec3(xc-radius/sqrt(2), yc+radius/sqrt(2), 0.0f);
			point.texel = glm::vec2(0.0f, 1.0f);
			vertex_buffer.push_back(point);

			index_buffer.push_back(glm::uvec3(0,1,2));
			index_buffer.push_back(glm::uvec3(2,3,0));
		}
/*		if(vertex_count > 4) {
			vertex_buffer.push_back(center);

			for (float u = 0; u <= 2*PI; u += (float)(2*PI/vertex_count)) {
				vertex_buffer.push_back(glm::vec3(xc + radius * sin(u), yc + radius * cos(u), 0.0));
			}
			for(int i = 1; i <= vertex_count; i++) {
				if(i != vertex_count)
					index_buffer.push_back(glm::uvec3(0,i,i+1));
				else
					index_buffer.push_back(glm::uvec3(0,vertex_count,1));
			}
		}*/
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint vbo, ibo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 3*index_buffer.size() * sizeof (MyVertexFormat), &vertex_buffer[0], GL_STATIC_DRAW);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer.size() * sizeof (glm::uvec3), &index_buffer[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (MyVertexFormat), (void *)0);

		nr_indices = (int)index_buffer.size() * 3;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		float maxAnisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data );

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (MyVertexFormat), (void *)sizeof(glm::vec3));

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	~Sprite() {}
	
};