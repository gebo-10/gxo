// UI.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <chrono>
#include <thread>
#include"3rd.h"

#include "render.h"

GrContext* sContext = nullptr;
SkSurface* sSurface = nullptr;

void init_skia(int w, int h) {
    GrContextOptions options;
    //options.fRequireDecodeDisableForSRGB = false; //was removed?
    sContext = GrContext::MakeGL(nullptr, options).release();

    GrGLFramebufferInfo framebufferInfo;
    framebufferInfo.fFBOID = 0; // assume default framebuffer
    // We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
    //(replace line below with this one to enable correct color spaces) framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
    framebufferInfo.fFormat = GL_RGBA8;


    GrBackendRenderTarget backendRenderTarget(w, h,
        0, // sample count
        0, // stencil bits
        framebufferInfo);

    //(replace line below with this one to enable correct color spaces) sSurface = SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
    sSurface = SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, nullptr, nullptr).release();
    if (sSurface == nullptr) abort();
}

inline void my_panic(sol::optional<std::string> maybe_msg) {
    std::cerr << "Lua is in a panic state and will now abort() the application" << std::endl;
    if (maybe_msg) {
        const std::string& msg = maybe_msg.value();
        std::cerr << "\terror message: " << msg << std::endl;
    }
    // When this function exits, Lua will exhibit default behavior and abort()
}

int my_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
    // L is the lua state, which you can wrap in a state_view if necessary
    // maybe_exception will contain exception, if it exists
    // description will either be the what() of the exception or a description saying that we hit the general-case catch(...)
    std::cout << "An exception occurred in a function, here's what it says ";
    if (maybe_exception) {
        std::cout << "(straight from the exception): ";
        const std::exception& ex = *maybe_exception;
        std::cout << ex.what() << std::endl;
    }
    else {
        std::cout << "(from the description parameter): ";
        std::cout.write(description.data(), description.size());
        std::cout << std::endl;
    }

    // you must push 1 element onto the stack to be 
    // transported through as the error object in Lua
    // note that Lua -- and 99.5% of all Lua users and libraries -- expects a string
    // so we push a single string (in our case, the description of the error)
    return sol::stack::push(L, description);
}


sol::state lua(sol::c_call<decltype(&my_panic), &my_panic>);

sol::function on_point_move;
void point_pos(GLFWwindow* window, double x, double y) {
    //std::cout << x, y;
    on_point_move( x, y);
}

sol::function on_mouse_button;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    static double last_x = 0, last_y = 0;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    on_mouse_button(button, action, mods, x, y);
    if (action == GLFW_PRESS) {
        
        last_x = x;
        last_y = y;
    }
    if (action == GLFW_RELEASE) {
        if (last_x == x && last_y == y) {
            on_mouse_button(button, 9, mods, x, y);
        }
    }
    if (action == GLFW_RELEASE) {
        static auto before = std::chrono::system_clock::now();
        auto now = std::chrono::system_clock::now();
        double diff_ms = std::chrono::duration <double, std::milli>(now - before).count();
        before = now;
        if (diff_ms > 10 && diff_ms < 200) {
            on_mouse_button(button, 10, mods, x, y);
        }
    }
    
}
sol::function on_size;
void on_window_size(GLFWwindow* window, int x, int y) {
    init_skia(x,y);
    Render render(sSurface->getCanvas());

    lua["render"] = render;
    on_size(x, y);
}

int main(void)
{
    
    //lua.set_exception_handler(&my_exception_handler);
    //sol::state lua; //create a plain lua state
    //lua.open_libraries(sol::lib::base);                //initialize its libraries
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::table, sol::lib::string);
    //lua["package.path"] = "E:\\gxo\\UI\\UI\\Assets";
    //luaopen_skia(lua.lua_state());
    //SkLua sklua(lua.lua_state());
    //sklua.Load(lua.lua_state());
    //initialize the terra state in lua
    //terra_init(lua.lua_state());

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetCursorPosCallback(window, point_pos);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowSizeCallback(window, on_window_size);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    init_skia(640, 480);

    glfwSwapInterval(1);

    // Draw to the surface via its SkCanvas.
    SkCanvas* canvas = sSurface->getCanvas(); // We don't manage this pointer's lifetime.
    
    Render::reg_render(lua);
    Render render(canvas);

    lua["render"] = render;
    lua.script_file("script/main.lua");

    on_point_move = lua["OnPointMove"];
    on_mouse_button = lua["OnMouseButton"];
    on_size = lua["OnSize"];
    sol::function update = lua["Update"];
   // sol::safe_function
    glClearColor(0., 0., 0., 0.0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
         //draw2(canvas);
        auto  r=update();
        //if (r.valid()) {
        //    sol::error err = r;
        //    std::cerr << "Lua:" << err.what() << std::endl;
        //    break;
        //}
        sContext->flush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
     
        /* Poll for and process events */
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    glfwTerminate();
    return 0;
}