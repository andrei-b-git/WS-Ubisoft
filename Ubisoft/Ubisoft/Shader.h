class Shader {

public:
	GLuint program;
	unsigned int location_model_matrix;
	unsigned int location_projection_matrix;
	unsigned int location_texture;
	unsigned int location_has_alpha;

public:
	char * LoadFileInMemory(const char *filename) {

		int size = 0;
		char *buffer = NULL;
		FILE *f = fopen(filename, "rb");
		if (f == NULL) {
			return NULL;
		}
		fseek(f, 0, SEEK_END);
		size = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = new char[size + 1];
		if (size != fread(buffer, sizeof(char), size, f))
		{
			delete[] buffer;
		}
		fclose(f);
		buffer[size] = 0;

		return buffer;
	}

	Shader() {

		const char * vertex_shader = LoadFileInMemory("../data/vertexShader.glsl");
		const char * fragment_shader = LoadFileInMemory("../data/fragmentShader.glsl");

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader, NULL);
		glCompileShader(vs);
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader, NULL);
		glCompileShader(fs);
		program = glCreateProgram();
		glAttachShader(program, fs);
		glAttachShader(program, vs);
		glLinkProgram(program);

		location_model_matrix = glGetUniformLocation(program,"model_matrix");
		location_projection_matrix = glGetUniformLocation(program,"projection_matrix");
		location_texture = glGetUniformLocation(program, "basic_texture");
		location_has_alpha = glGetUniformLocation(program, "has_alpha");

		delete[] vertex_shader;
		delete[] fragment_shader;
	}

	~Shader() {}
	
};