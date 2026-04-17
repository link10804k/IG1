#include "IG1App.h"

#include <iostream>

#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"

#include "TextureManager.h"
#include "Texture.h"
#include "stb_image_write.h"

using namespace std;

// static single instance (singleton pattern)
IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

// Print OpenGL errors and warnings
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const GLchar* message, const void* userParam)
{
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION && severity != GL_DEBUG_SEVERITY_LOW) {
		const char* prefix = (type == GL_DEBUG_TYPE_ERROR)
			? "\x1b[31m[ERROR]\x1b[0m "
			: "\x1b[33m[WARNING]\x1b[0m ";
		cout << prefix << message << endl;
	}
}

void
IG1App::close()
{
	cout << "Closing GLFW...\n";
	glfwSetWindowShouldClose(mWindow, true); // stops main loop
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWindow == 0) // if not intilialized
		init();

	// IG1App main loop
	while (!glfwWindowShouldClose(mWindow)) {
		// Redisplay the window if needed
		if (mNeedsRedisplay) {
			display();
			mNeedsRedisplay = false;
		}

		// Stop and wait for new events
		if (glfwGetTime() >= mNextUpdate) {
			mNextUpdate += FRAME_DURATION;
			if (mUpdateEnabled) {
				update();
				mNeedsRedisplay = true;
			}
		}
		
		glfwWaitEventsTimeout(mNextUpdate - glfwGetTime());
	}

	destroy();
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// CNG: Inicializar TextureManager
	TextureManager::Instance();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH);
	mCamera = new Camera(mViewPort);

	mScenes.push_back(new Scene);
	mScenes.push_back(new Scene1);
	mScenes.push_back(new Scene2);
	mScenes.push_back(new Scene3);
	mScenes.push_back(new Scene4);
	mScenes.push_back(new Scene5);

	mCamera->set2D();

	for (Scene* s : mScenes) s->init();

	mScenes[mCurrentScene]->load();
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting GLFW...\n";
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // enable on macOS
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window with its associated OpenGL context, return window's pointer
	mWindow = glfwCreateWindow(mWinW, mWinH, "IG1App", nullptr, nullptr);

	if (mWindow == nullptr) {
		glfwTerminate();
		throw std::logic_error("cannot create GLFW window");
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize OpenGL extension library
	if (GLenum err = glewInit(); err != GLEW_OK) {
		glfwTerminate();
		throw std::logic_error("Error while loading extensions: "s +
		                       reinterpret_cast<const char*>(glewGetErrorString(err)));
	}

	// Callback registration
	glfwSetWindowSizeCallback(mWindow, s_resize);
	glfwSetCharCallback(mWindow, s_key);
	glfwSetKeyCallback(mWindow, s_specialkey);
	glfwSetWindowRefreshCallback(mWindow, s_display);

	// CNG: Callbacks eventos de ratón
	glfwSetMouseButtonCallback(mWindow, s_mouse);
	glfwSetCursorPosCallback(mWindow, s_motion);
	glfwSetScrollCallback(mWindow, s_mouseWheel);

	// Error message callback (all messages)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0u, 0, GL_TRUE);
	glDebugMessageCallback(debugCallback, nullptr);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::destroy()
{ // release memory and resources
	for (Scene* scene : mScenes)
		delete scene;
	mScenes.clear();

	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;

	// CNG: Liberar TextureManager
	TextureManager::Release();

	glfwTerminate();
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	if (m2Vistas) 
		display2V();
	else
		mScenes[mCurrentScene]->render(*mCamera); // uploads the viewport and camera to the GPU

	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned int key)
{
	bool need_redisplay = true;

	switch (key) {
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		// CNG
		case 'u':
			update();
			break;
		case 'U':
			mUpdateEnabled = !mUpdateEnabled;
			break;
		case 'F':
			takePhoto();
			break;
		case 'a':
			mCamera->moveLR(-5.0f);
			break;
		case 'd':
			mCamera->moveLR(5.0f);
			break;
		case 'w':
			mCamera->moveUD(5.0f);
			break;
		case 's':
			mCamera->moveUD(-5.0f);
			break;
		case 'W':
			mCamera->moveFB(5.0f);
			break;
		case 'S':
			mCamera->moveFB(-5.0f);
			break;
		case 'p':
			mCamera->changePrj();
			break;
		case 'k':
			set2Viewports();
			break;
		// Fin 
		default:
			if (key >= '0' && key <= '9') {
				if (changeScene(key - '0')) break;
				cout << "[NOTE] There is no scene " << char(key) << ".\n";
			}
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

void
IG1App::specialkey(int key, int scancode, int action, int mods)
{
	// Only interested in press events
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;

	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(-5); // rotates -1 on the X axis
			else
				mCamera->yawReal(-5); // rotates 1 on the X axis
			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(5); // rotates 1 on the Y axis
			else
				mCamera->yawReal(5); // rotate -1 on the Y axis
			break;
		case GLFW_KEY_UP:
			mCamera->pitchReal(5); // rotates 1 on the Z axis
			break;
		case GLFW_KEY_DOWN:
			mCamera->pitchReal(-5); // rotates -1 on the Z axis
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

bool
IG1App::changeScene(size_t sceneNr)
{
	// Check whether the scene exists
	if (sceneNr >= mScenes.size())
		return false;

	// Change only if a different scene
	if (sceneNr != mCurrentScene) {
		mScenes[mCurrentScene]->unload();
		mCurrentScene = sceneNr;
		mScenes[mCurrentScene]->load();
	}

	return true;
}

void IG1App::update() {
	if (m2Vistas) {
		mScenes[0]->update();
		mScenes[1]->update();
	}
	else
		mScenes[mCurrentScene]->update();
}

void IG1App::takePhoto() {
	// Cargamos la captura de pantalla como textura
	Texture tx;
	tx.loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());

	// (Buffer) Array de unsigned chars donde se almacenan los datos de la imagen
	std::unique_ptr<unsigned char[]> data = std::make_unique<unsigned char[]>(IG1App::s_ig1app.viewPort().width() * IG1App::s_ig1app.viewPort().height() * 3 * sizeof(unsigned int));

	// Bindeamos la textura
	tx.bind();

	//Activamos la alineación de la memoria para que al dibujar en la imagen no se corte verticalmente
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	//Dibujamos la imagen en el buffer data
	glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_UNSIGNED_BYTE,data.get());

	// Invertimos la imagen verticalmente para que salga como se ve en ejecución
	stbi_flip_vertically_on_write(true);

	// Guardamos la imagen como photo.bmp con los datos obtenidos anteriormente
	stbi_write_bmp("../screenshots/photo.bmp", tx.width(), tx.height(), 3, data.get());
	
	// Unbindeamos la textura
	tx.unbind();
}

void IG1App::display2V() const {
	Camera auxCam = *mCamera;
	Viewport auxVP = *mViewPort;
	mViewPort->setSize(mWinW / 2, mWinH);

	auxCam.setSize(mViewPort->width(), mViewPort->height());

	// Vista 3D ortogonal:
	mViewPort->setPos(0, 0);
	auxCam.set3D();

	mScenes[0]->render(auxCam);

	// Vista cenital proyección:
	mViewPort->setPos(mWinW / 2, 0);
	//auxCam.setCenital();
	//auxCam.changePrj();
	auxCam.set2D();

	mScenes[1]->render(auxCam);

	*mViewPort = auxVP;
}

void IG1App::mouse(int button, int state, int mods) {
	if (state == GLFW_PRESS)
		mMouseButt = button;
	else
		mMouseButt = GLFW_MOUSE_BUTTON_LAST;
	
	glfwGetCursorPos(mWindow, &mMouseCoord.x, &mMouseCoord.y);
}
void IG1App::motion(double x, double y) {
	if (mMouseButt == GLFW_MOUSE_BUTTON_RIGHT) {
		glm::dvec2 displacement = glm::dvec2(x, y) - mMouseCoord;

		mCamera->moveUD(displacement.y);
		mCamera->moveLR(-displacement.x);

		mNeedsRedisplay = true;
		mMouseCoord = glm::dvec2(x, y);
	}
	else if (mMouseButt == GLFW_MOUSE_BUTTON_LEFT) {
		glm::dvec2 displacement = glm::dvec2(x, y) - mMouseCoord;

		mCamera->orbit(-displacement.x * 0.05, displacement.y);

		mNeedsRedisplay = true;
		mMouseCoord = glm::dvec2(x, y);
	}
}
void IG1App::mouseWheel(double dx, double dy) {
	if (glfwGetKey(mWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		// Escala la escena según el valor de d
		mCamera->setScale(dy);
	}
	else {
		// Desplaza la cámara en su dirección de vista
		mCamera->moveFB(dy);
	}

	mNeedsRedisplay = true;
}

// TODO: "Carga excesiva de escenas en set2Viewports()."
void IG1App::set2Viewports() {
	if (m2Vistas) {
		// Descargamos la 4 y la 2
		mScenes[0]->unload();
		mScenes[1]->unload();
		// Cargamos la actual
		mScenes[mCurrentScene]->load();
	}
	else {
		// Descargamos la actual
		mScenes[mCurrentScene]->unload();
		// Cargamos la 4 y la 2
		mScenes[0]->load();
		mScenes[1]->load();
	}
	m2Vistas = !m2Vistas;
}