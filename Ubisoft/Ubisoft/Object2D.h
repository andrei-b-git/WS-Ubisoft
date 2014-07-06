class Object2D {

public:
	GLuint vao;
	int nr_indices;
	glm::vec3 color;

	glm::mat4 model_matrix;
	glm::mat4 projection_matrix;

public:
	Object2D() {


		GLuint vbo, ibo;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof (float), vertex_buffer, GL_STATIC_DRAW);

		glGenBuffers(1, &ibo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof (unsigned int), index_buffer, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void *)0);

		nr_indices = 6;
	}
	}

	~Object2D() {}
	
};