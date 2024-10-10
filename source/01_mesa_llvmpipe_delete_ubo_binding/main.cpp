#include <application.hpp>

#include <iostream>

#define DEBUG 0
#if DEBUG
#define RUN_(gl_cmd)                                                                               \
    {                                                                                              \
        gl_cmd;                                                                                    \
        auto x = glGetError();                                                                     \
        if (x != GL_NO_ERROR) {                                                                    \
            std::cout << "error=" << x << std::endl;                                               \
            exit(1);                                                                               \
        }                                                                                          \
    }
#else
#define RUN_(gl_cmd) gl_cmd
#endif

class EmptyWindowApplication : public our::Application {
    our::WindowConfiguration getWindowConfiguration() override {
        return {"Window", {400, 400}, false};
    }

    void onInitialize() override {
        constexpr size_t LEN = 2;
        GLuint ids[LEN];
        RUN_(glGenBuffers(LEN, ids));

        auto getActualBound = []() {
            GLint found;
            glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, &found);
            return found;
        };

        auto getActualBoundIndex = [](int bindPoint) {
            GLint found;
            glGetIntegeri_v(GL_UNIFORM_BUFFER_BINDING, bindPoint, &found);
            return found;
        };

        for (auto bindPoint: {0, 1}) {
            GLintptr const offset = 0;
            GLsizeiptr const size = 1;
            RUN_(glBindBufferRange(GL_UNIFORM_BUFFER, bindPoint, ids[bindPoint], offset, size));
            std::cout << "## After setting up buffer=" << ids[bindPoint]
                      << ", buffer=" << getActualBound()
                      << " + index=" << getActualBoundIndex(bindPoint) << " is actually bound."
                      << std::endl;
        }

        std::cout << "## Bind again buffer=" << ids[1] << " and delete buffer=" << ids[0]
                  << std::endl;
        RUN_(glBindBuffer(GL_UNIFORM_BUFFER, ids[1]));
        RUN_(glDeleteBuffers(1, &ids[0]));
        std::cout << "## Currently buffer=" << getActualBound() << " is bound." << std::endl;
        std::cout << "## Index binding state is"
                  << " index[buffer=" << ids[0] << "]=" << getActualBoundIndex(0)
                  << " index[buffer=" << ids[1] << "]=" << getActualBoundIndex(1) << std::endl;

        exit(0);
    }

    void onImmediateGui(ImGuiIO& io) override {}

    void onDraw(double deltaTime) override {}
};

int main(int argc, char** argv) {
    return EmptyWindowApplication().run();
}
