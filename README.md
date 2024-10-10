# Graphics Demos

This repo is used to provide simple repros to graphics issues that can be attached to other open source projects.

The basic framework is based on [OpenGL Examples].

## Demos

### 01_mesa_llvmpipe_swrast_delete_ubo_binding
Demostrates a bug with Mesa's GL software rasterizer that would sometimes unbind currently bound indices perhaps unintentionally. See [Details][01_details].

[01_details]: source/01_mesa_llvmpipe_swrast_delete_ubo_binding/README.md
[OpenGL Examples]: https://github.com/yahiaetman/OpenGL-Examples
