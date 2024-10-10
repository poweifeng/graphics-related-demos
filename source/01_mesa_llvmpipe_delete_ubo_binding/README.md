# Unexpected unbinding of uniform buffer

Consider the following snippet

```c++
constexpr size_t LEN = 2;
GLuint ids[LEN];
glGenBuffers(LEN, ids);

for (auto bindPoint : {0, 1}) {
  GLintptr const offset = 0;
  GLsizeiptr const size = 1;
  glBindBufferRange(GL_UNIFORM_BUFFER, bindPoint, ids[bindPoint], offset, size);
}

glBindBuffer(GL_UNIFORM_BUFFER, ids[1]);
glDeleteBuffers(1, &ids[0]);
```
At the very end, we expect the currently bound uniform buffer to be `ids[1]` (some non-zero identifier). But when we actually check the currently bound buffer (through `glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, ...)`), we see that there is no currently bound buffer (`glGetIntegerv` returns 0). No errors were given and instead we have an unexpected result.

Reproducible on Mesa built from source:
 - llvmpipe (LLVM 17.0.6, 256 bits)
 - 4.5 (Core Profile) Mesa 24.2.0-devel (git-eebc4ec264)

Furthermore, testing on an Nvidia driver produces the expected result (`glGetIntegerv` returns correct bound buffer ID).

NVIDIA driver info:
 - NVIDIA GeForce RTX 3070/PCIe/SSE2
 - 3.3.0 NVIDIA 535.183.01
