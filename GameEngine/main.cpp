#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <thread>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processKeyboardInput();



float deltaTime = 0.0f;
float lastFrame = 0.0f;

Window window("Mission: Doom's Domain", 800, 800);
Camera camera;


glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos = glm::vec3(-180.0f, 100.0f, -200.0f);


//skyBox vertices

float skyboxVertices[] = {
	-500.0f, -500.0f,  500.0f,
	 500.0f, -500.0f,  500.0f,
	 500.0f, -500.0f, -500.0f,
	-500.0f, -500.0f, -500.0f,
	-500.0f,  500.0f,  500.0f,
	 500.0f,  500.0f,  500.0f,
	 500.0f,  500.0f, -500.0f,
	-500.0f,  500.0f, -500.0f
};



unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Front
	0, 1, 5,
	5, 4, 0,
	// Back
	3, 7, 6,
	6, 2, 3
};

bool isInsideSpaceship = true;


int main()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glm::vec3 init = glm::vec3(600.0f, 1000.0f, -300.0f);
	camera.setCameraPosition(init);

	glm::vec3 cameraPosition = camera.getCameraPosition();

	//building and compiling shader program
	Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
	Shader sunShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");
	Shader skyboxShader("Shaders/skybox_vertex_shader.glsl", "Shaders/skybox_fragment_shader.glsl");

	glDepthMask(GL_FALSE);
	skyboxShader.use();
	glUniform1i(glGetUniformLocation(skyboxShader.getId(), "skybox"), 0);

	//textures
	GLuint tex = loadBMP("Resources/Textures/castle.bmp");
	GLuint tex2 = loadBMP("Resources/Textures/gold.bmp");
	GLuint tex3 = loadBMP("Resources/Textures/rock.bmp");
	GLuint tex4 = loadBMP("Resources/Textures/leds.bmp");
	GLuint tex5 = loadBMP("Resources/Textures/spaceship.bmp");
	GLuint tex6 = loadBMP("Resources/Textures/card.bmp");
	GLuint tex7 = loadBMP("Resources/Textures/walls.bmp");
	GLuint tex8 = loadBMP("Resources/Textures/weapon.bmp");
	GLuint tex9 = loadBMP("Resources/Textures/shuri.bmp");
	GLuint tex10 = loadBMP("Resources/Textures/oldtown.bmp");
	GLuint tex11 = loadBMP("Resources/Textures/white.bmp");


	glEnable(GL_DEPTH_TEST);

	//mesh
	std::vector<Vertex> vert;
	vert.push_back(Vertex());
	vert[0].pos = glm::vec3(10.5f, 10.5f, 0.0f);
	vert[0].textureCoords = glm::vec2(1.0f, 1.0f);

	vert.push_back(Vertex());
	vert[1].pos = glm::vec3(10.5f, -10.5f, 0.0f);
	vert[1].textureCoords = glm::vec2(1.0f, 0.0f);

	vert.push_back(Vertex());
	vert[2].pos = glm::vec3(-10.5f, -10.5f, 0.0f);
	vert[2].textureCoords = glm::vec2(0.0f, 0.0f);

	vert.push_back(Vertex());
	vert[3].pos = glm::vec3(-10.5f, 10.5f, 0.0f);
	vert[3].textureCoords = glm::vec2(0.0f, 1.0f);


	vert[0].normals = glm::normalize(glm::cross(vert[1].pos - vert[0].pos, vert[3].pos - vert[0].pos));
	vert[1].normals = glm::normalize(glm::cross(vert[2].pos - vert[1].pos, vert[0].pos - vert[1].pos));
	vert[2].normals = glm::normalize(glm::cross(vert[3].pos - vert[2].pos, vert[1].pos - vert[2].pos));
	vert[3].normals = glm::normalize(glm::cross(vert[0].pos - vert[3].pos, vert[2].pos - vert[3].pos));

	std::vector<int> ind = { 0, 1, 3,
		1, 2, 3 };

	std::vector<Texture> textures;
	textures.push_back(Texture());
	textures[0].id = tex;
	textures[0].type = "texture_diffuse";

	std::vector<Texture> textures2;
	textures2.push_back(Texture());
	textures2[0].id = tex2;
	textures2[0].type = "texture_diffuse";

	std::vector<Texture> textures3;
	textures3.push_back(Texture());
	textures3[0].id = tex3;
	textures3[0].type = "texture_diffuse";

	std::vector<Texture> textures4;
	textures4.push_back(Texture());
	textures4[0].id = tex4;
	textures4[0].type = "texture_diffuse";

	std::vector<Texture> textures5;
	textures5.push_back(Texture());
	textures5[0].id = tex5;
	textures5[0].type = "texture_diffuse";

	std::vector<Texture> textures6;
	textures6.push_back(Texture());
	textures6[0].id = tex6;
	textures6[0].type = "texture_diffuse";

	std::vector<Texture> textures7;
	textures7.push_back(Texture());
	textures7[0].id = tex7;
	textures7[0].type = "texture_diffuse";

	std::vector<Texture> textures8;
	textures8.push_back(Texture());
	textures8[0].id = tex8;
	textures8[0].type = "texture_diffuse";

	std::vector<Texture> textures9;
	textures9.push_back(Texture());
	textures9[0].id = tex9;
	textures9[0].type = "texture_diffuse";

	std::vector<Texture> textures10;
	textures10.push_back(Texture());
	textures10[0].id = tex10;
	textures10[0].type = "texture_diffuse";

	std::vector<Texture> textures11;
	textures11.push_back(Texture());
	textures11[0].id = tex11;
	textures11[0].type = "texture_diffuse";

	std::vector<Texture> textures12;
	textures12.push_back(Texture());
	textures12[0].id = tex11;
	textures12[0].type = "texture_diffuse";

	Mesh mesh(vert, ind, textures3);

	// obj loader
	MeshLoaderObj loader;
	Mesh sun = loader.loadObj("Resources/Models/sphere.obj");
	Mesh plane = loader.loadObj("Resources/Models/plane.obj", textures3);
	Mesh castle = loader.loadObj("Resources/Models/castle.obj", textures);
	Mesh throne = loader.loadObj("Resources/Models/chair.obj", textures2);
	Mesh maze = loader.loadObj("Resources/Models/maze.obj", textures4);
	Mesh spaceship = loader.loadObj("Resources/Models/spaceship.obj", textures5);
	Mesh card = loader.loadObj("Resources/Models/card.obj", textures6);
	Mesh card2 = loader.loadObj("Resources/Models/card.obj", textures6);
	Mesh card3 = loader.loadObj("Resources/Models/card.obj", textures6);
	Mesh card4 = loader.loadObj("Resources/Models/card.obj", textures6);
	Mesh card5 = loader.loadObj("Resources/Models/card.obj", textures6);
	Mesh cardf1 = loader.loadObj("Resources/Models/card.obj", textures6);
	Mesh cardf2 = loader.loadObj("Resources/Models/card.obj", textures6);

	Mesh house = loader.loadObj("Resources/Models/house.obj", textures7);
	Mesh weapon = loader.loadObj("Resources/Models/weapon.obj", textures8);
	Mesh robot = loader.loadObj("Resources/Models/shuri.obj", textures9);
	Mesh oldtown = loader.loadObj("Resources/Models/oldtown.obj", textures10);
	Mesh cat = loader.loadObj("Resources/Models/cat.obj", textures11);
	Mesh table = loader.loadObj("Resources/Models/table.obj", textures11);
	Mesh lever = loader.loadObj("Resources/Models/lever.obj", textures12);


	//positions for blocking the castle until task 5
	glm::vec3 positions[] = {
		glm::vec3(1162.0f, 0.0f, -494.0f),
		glm::vec3(1162.0f, 0.0f, 484.0f),
		glm::vec3(842.0f, 0.0f, 484.0f),
		glm::vec3(842.0f, 0.0f, -494.0f),
	};


	//IMGUI Implementation
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//VBO,EBO,VAO SKYBOX
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::vector<std::string> faces{
	"Resources/skybox/right.jpg",
	"Resources/skybox/left.jpg",
	"Resources/skybox/up.jpg",
	"Resources/skybox/down.jpg",
	"Resources/skybox/back.jpg",
	"Resources/skybox/front.jpg"
	};

	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
			std::cout << "Load image part: " << faces[i] << std::endl;
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	//boolean variables for IMGUI
	bool showConfirmationDialog = false;
	bool tasksStarted = false;


	//position for spaceship (before starting to come down)
	float currentYPosition = 1000.0f;
	float floatSpeed = 25.0f;

	//verification for showing the main menu
	bool gameStarted = false; 


	//tasks checker
	bool task1 = false;
	bool task2 = false;
	bool task3 = false;
	bool task4 = false;
	bool task5 = false;

	bool task1Completed = false;
	bool task2Completed = false;
	bool task3Completed = false;
	bool task4Completed = false;
	bool task5Completed = false;

	bool triedToGoInsideDoom = false;

	bool catFound = false;
	bool leverPressed = false;
	bool cardsOnTable = false;
	bool throneFinal = false;
	bool finalScene = false;

	bool collisioncastle = false;

	//card counter
	int cardCounter = 0;

	//camera inside spaceship at the begining
	//check if we close the window or press the escape button
	while (!window.isPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(window.getWindow()) == 0)
	{
		window.clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImVec2 displaySize = ImGui::GetIO().DisplaySize;

		// Calculate the position to center the window
		ImVec2 windowSize(800, 800);
		ImVec2 centeredPos((displaySize.x - windowSize.x) / 2, (displaySize.y - windowSize.y) / 2);

		// Set the window position and size
		ImGui::SetNextWindowPos(centeredPos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

		if (!task1 && !gameStarted) {
			// Main ImGui window 
			ImGui::Begin("Mission: Doom's Domain", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
			ImGui::Text("**** STORYLINE ****");
			ImGui::TextWrapped("You are the super legendary Wakandian spy Shuri and your mission is to retrieve the Quantum Disruptor, the top-secret weapon that you developed and the most dangerous villain, Doctor Doom has stole it! Are you ready to face your fears and put your skills up to the test ?");

			// Add buttons 
			if (ImGui::Button("Start Game")) {
				gameStarted = true;
			}
			if (ImGui::Button("Exit the game")) {
				showConfirmationDialog = true;
			}
			ImGui::End();
		}

		if (gameStarted) {

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			processKeyboardInput();


			//light

			sunShader.use();

			glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
			glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());

			GLuint MatrixID = glGetUniformLocation(sunShader.getId(), "MVP");

			//loading the sun
			glm::mat4 ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, lightPos);
			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

			sun.draw(sunShader);



			//shader 

			shader.use();

			//shader settings
			GLuint MatrixID2 = glGetUniformLocation(shader.getId(), "MVP");
			GLuint ModelMatrixID = glGetUniformLocation(shader.getId(), "model");

			glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
			glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
			glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);


			//plane object
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(100.0f, 1.0f, 100.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			plane.draw(shader);


			//castle object
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1000.0f, -10.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 5.0f, 3.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			castle.draw(shader);


			if (!throneFinal) {
				//throne + floating and rotation at the same time
				float floatSpeed = 2.0f;
				float floatHeight = 5.0f;

				float floatOffset = sin(glfwGetTime() * floatSpeed) * floatHeight;
				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1030, 0.0f + floatOffset, 0.0f));

				float rotationAngle = glfwGetTime() * glm::radians(100.0f);
				ModelMatrix = glm::rotate(ModelMatrix, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(30.0f, 30.0f, 30.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				throne.draw(shader);
			}

			if (throneFinal) {

				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1030, 0.0f, 0.0f));
				ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(30.0f, 30.0f, 30.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
				throne.draw(shader);
			}

			//maze object
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-600.0f, -9.90f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(50.0f, 100.0f, 50.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			maze.draw(shader);


			//spaceship object + camera inside the spaceship
			if (isInsideSpaceship) {
				currentYPosition -= floatSpeed * 3 * deltaTime;
				if (currentYPosition < 92.0f) {
					currentYPosition = 92.0f;
					isInsideSpaceship = false; // Allow free camera control after landing
				}
				
				// Update camera's y position along with spaceship
				glm::vec3 cameraPos = camera.getCameraPosition();
				camera.setCameraPosition(glm::vec3(cameraPos.x, currentYPosition-96.0f, cameraPos.z));
			}

			ModelMatrix = glm::mat4(1.0f);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(600.0f, currentYPosition, -300.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			spaceship.draw(shader);



			
			//card object (this will be multiple times added ~ 5 times)

			if (task2Completed) {
				//card in the house  - task 3 + fake cards - cardf1,cardf2
				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(240.0f, -10.0f, 298.0f));
				ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
				ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				card.draw(shader);

				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(162.0f, -10.0f, 327.0f));
				ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
				ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				cardf1.draw(shader);

				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(211.0f, -10.0f, 330.0f));
				ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
				ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				cardf2.draw(shader);
			}

			if (task1) {
				//card outside the spaceship - task 1
				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(736.0f, -10.0f, -525.0f));
				ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
				ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				card2.draw(shader);
			}

			if (task1Completed) {
				//cat and card - city - task 2

				if (!catFound) {
					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(100.0f, -7.0f, -811.0f));
					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(15.0f, 15.0f, 15.0f));
					ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
					cat.draw(shader);
				}
				

				if (catFound) {
					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(55.0f, -10.0f, -685.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					card3.draw(shader);
				}
			}

			if (task3Completed) {
				//lever + card task 4
				if (!leverPressed) {
					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-233.0f, -10.0f, -333.0f));
					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					lever.draw(shader);
				}

				
				if (leverPressed) {
					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-318.0f, -10.0f, -132.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					card4.draw(shader);
				}
				
			}

			if (task4Completed) {
				//put the cards and the weapon object (basically the price and the final element for capturing the Dr. Doom's castle)
				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(880.0f, -10.0f, 37.0f));
				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5.0f, 5.0f, 5.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				weapon.draw(shader);

				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(880.0f, -10.0f, 72.0f));
				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 20.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				table.draw(shader);

				if (cardsOnTable) {
					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(880.0f, -5.0f, 70.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					card.draw(shader);


					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(880.0f, -5.0f, 71.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					card2.draw(shader);

					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(880.0f, -5.0f, 72.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					card3.draw(shader);

					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(880.0f, -5.0f, 73.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
					ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					card4.draw(shader);
				}
			}

			//house object
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(200.0f, -10.0f, 300.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			house.draw(shader);


			

			//oldtown object
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -10.0f, -700.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(100.0f, 100.0f, 150.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			oldtown.draw(shader);

			//secure the castle to not enter in it if the task 5 is not active
			if (!collisioncastle) {
				glm::vec3 positionTask5 = camera.getCameraPosition();
				if (positionTask5.x > 841 && positionTask5.x<1163 && positionTask5.z>-495 && positionTask5.z < 485)
				{
					triedToGoInsideDoom = true;
				}

				if (positionTask5.x > 842 && positionTask5.x<1162 && positionTask5.z>-494 && positionTask5.z < 484)
				{
					camera.setCameraPosition(glm::vec3(803.0f, 0.0f, 198.0f));
				}
			}

			
			//IMGUI interface 

			ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Always);

			if (!tasksStarted) {
				// Main ImGui window 
				ImGui::Begin("Mission: Doom's Domain", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
				ImGui::Text("Welcome!");
				ImGui::TextWrapped("Choose what do you want to do:");
				ImGui::Text(" ");

				// Add buttons 
				if (ImGui::Button("Tasks")) {
					task1 = true;
					tasksStarted = true;
				}
				if (ImGui::Button("Exit the game")) {
					showConfirmationDialog = true;
				}

				ImGui::Text(" ");
				if (triedToGoInsideDoom) {
					ImGui::Text("You can't go inside now!!!");
					triedToGoInsideDoom = false;
				}

				ImGui::End();
			}

			if (showConfirmationDialog) {
				ImGui::Begin("Confirm Exit", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
				ImGui::Text("Are you sure you want to exit?");
				if (ImGui::Button("Yes")) {
					glfwSetWindowShouldClose(window.getWindow(), GLFW_TRUE);
				}
				ImGui::SameLine();
				if (ImGui::Button("No")) {
					showConfirmationDialog = false;
				}
				ImGui::End();
			}

			if (task1) {
				ImGui::Begin("Task 1", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped("Objective update: exit the spaceship and retrieve the first quantum card");
				ImGui::Text(" ");

				// Display the camera position in ImGui
				glm::vec3 pos = camera.getCameraPosition();
				ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);

				if (ImGui::Button("Exit the game")) {
					showConfirmationDialog = true;
				}

				ImGui::Text(" ");
				if (triedToGoInsideDoom) {
					ImGui::Text("You can't go inside now!!!");
					triedToGoInsideDoom = false;
				}

				glm::vec3 targetPosition(736.0f, 0.0f, -525.0f);
				float tolerance = 1.5f; 
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					task1Completed = true;
					task1 = false;
					cardCounter+=1;
				}
				ImGui::End();


			}

			if (task1Completed) {
				ImGui::Begin("Task 2", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped("Find the cat, then the card appears. Find the card to go to the next task.");
				ImGui::Text(" ");

				// Display the camera position in ImGui
				glm::vec3 pos = camera.getCameraPosition();
				ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);

				ImGui::Text(" ");
				ImGui::Text("You have %d card",cardCounter);

				ImGui::Text(" ");

				if (ImGui::Button("Exit the game")) {
					showConfirmationDialog = true;
				}

				ImGui::Text(" ");
				if (triedToGoInsideDoom) {
					ImGui::Text("You can't go inside now!!!");
					triedToGoInsideDoom = false;
				}

				glm::vec3 targetPosition(100.0f, 0.0f, -811.0f);
				float tolerance = 1.5f;
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					catFound = true;
				}

				targetPosition = glm::vec3(55.0f, 0.0f, -685.0f);
				tolerance = 1.5f;
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					task2Completed = true;
					task2 = false;
					task1Completed = false;
					cardCounter += 1;
				}				

				ImGui::End();
			}

			if (task2Completed) {
				ImGui::Begin("Task 3", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped("Find the right card in the house. Be careful to choose the correct one, otherwise you will be teleported outside the house.");
				ImGui::Text(" ");

				// Display the camera position in ImGui
				glm::vec3 pos = camera.getCameraPosition();
				ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);

				ImGui::Text(" ");
				ImGui::Text("You have %d card", cardCounter);

				ImGui::Text(" ");

				if (ImGui::Button("Exit the game")) {
					showConfirmationDialog = true;
				}

				ImGui::Text(" ");
				if (triedToGoInsideDoom) {
					ImGui::Text("You can't go inside now!!!");
					triedToGoInsideDoom = false;
				}

				glm::vec3 targetPosition(162.0f, 0.0f, 327.0f);
				float tolerance = 1.5f;
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					camera.setCameraPosition(glm::vec3(194.0f, 0.0f, 227.0f));
				}

				targetPosition=glm::vec3(11.0f, 0.0f, 330.0f);
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					camera.setCameraPosition(glm::vec3(194.0f, 0.0f, 227.0f));
				}

				targetPosition = glm::vec3(240.0f, 0.0f, 298.0f);
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					task3Completed = true;
					task3 = false;
					task2Completed = false;
					cardCounter += 1;
				}


				ImGui::End();
			}

			if (task3Completed) {
				ImGui::Begin("Task 4", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped("Find the lever in the labyrinth and after that the card will be spawned in the labyrinth. Find it in order to access the next task.");
				ImGui::Text(" ");

				// Display the camera position in ImGui
				glm::vec3 pos = camera.getCameraPosition();
				ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);


				ImGui::Text(" ");
				ImGui::Text("You have %d card", cardCounter);

				ImGui::Text(" ");

				if (ImGui::Button("Exit the game")) {
					showConfirmationDialog = true;
				}

				ImGui::Text(" ");
				if (triedToGoInsideDoom) {
					ImGui::Text("You can't go inside now!!!");
					triedToGoInsideDoom = false;
				}

				//lever touch
				glm::vec3 targetPosition(-233.0f, 0.0f, -333.0f);
				float tolerance = 1.5f;
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					leverPressed = true;
				}

				//card receive
				targetPosition = glm::vec3(-318.0f, 0.0f, -132.0f);
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					task4Completed = true;
					task4 = false;
					task3Completed = false;
					cardCounter += 1;
					collisioncastle = true;
				}

				ImGui::End();
			}

			if (task4Completed) {
				ImGui::Begin("Task 5", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped("Enter the castle, put all the cards down on table and then take the gun");
				ImGui::Text(" ");

				// Display the camera position in ImGui
				glm::vec3 pos = camera.getCameraPosition();
				ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);

				ImGui::Text(" "); 
				ImGui::Text("You have %d card", cardCounter);

				ImGui::Text(" ");


				if (ImGui::Button("Exit the game")) {
					showConfirmationDialog = true;
				}

				//cards on the table
				glm::vec3 targetPosition(880.0f, 0.0f, 72.0f);
				float tolerance = 1.5f;
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					cardsOnTable = true;
				}

				//card receive
				targetPosition = glm::vec3(880.0f, 0.0f, 37.0f);
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					if (cardsOnTable) {
						task5Completed = true;
						task4 = false;
						task4Completed = false;
					}
					else {
						ImGui::Text("Put the cards on the table");
					}
					
				}


				ImGui::End();
			}

			if (task5Completed) {
				ImGui::Begin("Claim Dr. Doom's Domain", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped("After our journey, we finally take our gun back! It's time for revenge and capture the Dr. Doom's Domain!");
				ImGui::Text(" ");

				ImGui::TextWrapped("Your gun is yours again!");
				ImGui::Text(" ");

				// Display the camera position in ImGui
				glm::vec3 pos = camera.getCameraPosition();
				ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);

				if (ImGui::Button("Exit the game")) {
					showConfirmationDialog = true;
				}

				ImGui::Text(" ");
				glm::vec3 targetPosition(1030.0f, 0.0f, 0.0f);
				float tolerance = 25.0f;
				if (glm::distance(camera.getCameraPosition(), targetPosition) <= tolerance) {
					finalScene = true;
					task5Completed = false;
					task5 = false;
				}

				ImGui::End();
			}

			if (finalScene) {
				ImGui::Begin("Ending", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped("Congratulations! The Dr. Doom's Castle is yours!");
				ImGui::Text(" ");

				camera.setCameraPosition(glm::vec3(1030.0f, 50.0f, 0.0f));

				// Display the camera position in ImGui
				glm::vec3 pos = camera.getCameraPosition();
				ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);

				if (ImGui::Button("Exit the game")) {
					showConfirmationDialog = true;
				}

				ImGui::End();
			}



			//Rendering of the skybox/cubemap

			glDepthFunc(GL_LEQUAL);
			skyboxShader.use();
			glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix()));
			glm::mat4 projection = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
			glUniformMatrix4fv(glGetUniformLocation(skyboxShader.getId(), "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(skyboxShader.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(skyboxVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);

		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

//jump helping elements
enum class JumpState {
	None,
	JumpingUp,
	FallingDown
};

JumpState jumpState = JumpState::None;
float jumpStartTime = 0.0f;
float jumpDuration = 0.5f;
float jumpHeight = 5.0f;
glm::vec3 initialCameraPos;

void processKeyboardInput() {
	float cameraSpeed = 30 * deltaTime;

	if (window.isPressed(GLFW_KEY_LEFT_SHIFT))
		cameraSpeed *= 2;

	//camera position in terminal
	glm::vec3 pos = camera.getCameraPosition();
	std::cout << "Camera Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;

	// translation
	if ((camera.getCameraPosition().y > -0.1f && camera.getCameraPosition().y < 5.5f) || isInsideSpaceship) {
		if (window.isPressed(GLFW_KEY_W))
			camera.keyboardMoveFront(cameraSpeed);
		if (window.isPressed(GLFW_KEY_S))
			camera.keyboardMoveBack(cameraSpeed);
		if (window.isPressed(GLFW_KEY_A))
			camera.keyboardMoveLeft(cameraSpeed);
		if (window.isPressed(GLFW_KEY_D))
			camera.keyboardMoveRight(cameraSpeed);
	}
	else {
		glm::vec3 cameraPos = camera.getCameraPosition();
		if (isInsideSpaceship) {
			glm::vec3 cameraPosBlockGoingDown = glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z);
			camera.setCameraPosition(cameraPosBlockGoingDown);
		}
		else {
			glm::vec3 cameraPosBlockGoingDown = glm::vec3(cameraPos.x, 0, cameraPos.z);
			camera.setCameraPosition(cameraPosBlockGoingDown);
		}
	}

	// rotation
	if (window.isPressed(GLFW_KEY_LEFT))
		camera.rotateOy(cameraSpeed);
	if (window.isPressed(GLFW_KEY_RIGHT))
		camera.rotateOy(-cameraSpeed);
	if (window.isPressed(GLFW_KEY_UP) && !isInsideSpaceship)
		camera.rotateOx(cameraSpeed);
	if (window.isPressed(GLFW_KEY_DOWN) && !isInsideSpaceship)
		camera.rotateOx(-cameraSpeed);

	// jump
	if (window.isPressed(GLFW_KEY_SPACE) && jumpState == JumpState::None) {
		jumpState = JumpState::JumpingUp;
		jumpStartTime = glfwGetTime();
		initialCameraPos = camera.getCameraPosition();
	}

	if (jumpState != JumpState::None) {
		float currentTime = glfwGetTime();
		float elapsedTime = currentTime - jumpStartTime;

		if (jumpState == JumpState::JumpingUp) {
			if (elapsedTime < jumpDuration / 2) {
				float t = elapsedTime / (jumpDuration / 2);
				float height = t * jumpHeight;
				glm::vec3 cameraPos = camera.getCameraPosition();
				camera.setCameraPosition(glm::vec3(cameraPos.x, initialCameraPos.y + height, cameraPos.z));
			}
			else {
				jumpState = JumpState::FallingDown;
				jumpStartTime = currentTime;
			}
		}
		else if (jumpState == JumpState::FallingDown) {
			if (elapsedTime < jumpDuration / 2) {
				float t = elapsedTime / (jumpDuration / 2);
				float height = (1 - t) * jumpHeight;
				glm::vec3 cameraPos = camera.getCameraPosition();
				camera.setCameraPosition(glm::vec3(cameraPos.x, initialCameraPos.y + height, cameraPos.z));
			}
			else {
				jumpState = JumpState::None;
				glm::vec3 cameraPos = camera.getCameraPosition();
				camera.setCameraPosition(glm::vec3(cameraPos.x, initialCameraPos.y, cameraPos.z));
			}
		}
	}
}