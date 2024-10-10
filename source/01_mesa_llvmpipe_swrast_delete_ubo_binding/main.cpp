#include <application.hpp>

#include <iostream>

#define DEBUG 1

#if DEBUG
#define RUN_(gl_cmd) { gl_cmd; auto x = glGetError();                                 \
        if (x != GL_NO_ERROR) { std::cout <<"error=" << x << std::endl; exit(1); } }
#else
#define RUN_(gl_cmd) { gl_cmd; }
#endif

// This exercise Window Application that derives from "Application" parent
class EmptyWindowApplication : public our::Application {

    // This overriden function sets the window configuration params struct (title, size, isFullscreen).
    our::WindowConfiguration getWindowConfiguration() override {
        return { "Empty Window", {1280, 720}, false };
    }

    // oninitialize() function is called once before the application loop
    void onInitialize() override {

        //Specify the red, green, blue, and alpha values used when the color buffers are cleared.
        //Here the clear color is Magenta
        glClearColor(0.5f, 0.2f, 0.7f, 1.0f);

        constexpr size_t LEN = 5;
        GLuint ids[LEN];
        RUN_(glGenBuffers(LEN, ids));

        auto getActualBound = []() {
            GLint found;
            glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, &found);
            return found;
        };
        auto setup = [&](int bindPoint) {
            //            RUN_(glBindBuffer(GL_UNIFORM_BUFFER, ids[bindPoint]));
            GLintptr const offset = 0;
            GLsizeiptr const size = 1;
            RUN_(glBindBufferRange(GL_UNIFORM_BUFFER, bindPoint, ids[bindPoint], offset, size));
            std::cout <<"After setting up buffer=" << ids[bindPoint]
                      << ". The actual bound buffer is " << getActualBound() << std::endl;
            RUN_(glBindBufferRange(GL_UNIFORM_BUFFER, bindPoint, 0, offset, size));
        };

        setup(0);
        setup(1);
        std::cout <<"Bind again buffer=" << ids[1] << " and delete buffer=" << ids[0] << std::endl;
        RUN_(glBindBuffer(GL_UNIFORM_BUFFER, ids[1]));
        RUN_(glDeleteBuffers(1, &ids[0]));
        std::cout <<"Currently buffer=" << getActualBound() << " is bound." << std::endl;
    }

    void onImmediateGui(ImGuiIO &io) override {
    }

    // onDraw(deltaTime) function is called every frame
    void onDraw(double deltaTime) override {
        //At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame.
        glClear(GL_COLOR_BUFFER_BIT);
    }

};

// Example Entry point
int main(int argc, char** argv) {

    // Creates an instance of EmptyWindowApplication and call run on this instance
    return EmptyWindowApplication().run();
}
