# Graphics Demos

This repo is used to provide reproductions of graphical issues. It's meant to be simple and self-contained so that the demos can be attached to issue trackers of other open-source projects.

The basic framework is based on [OpenGL Examples].

## Build

To build any of the following demos, run

```shell
mkdir out && cd out && cmake ..
make && ./[demo_executable_name]
```

## Demos

### [01_mesa_llvmpipe_delete_ubo_binding]
Demostrates a bug with Mesa's GL software rasterizer that would unbind currently bound uniform buffer (perhaps unintentionally).

[01_mesa_llvmpipe_delete_ubo_binding]: source/01_mesa_llvmpipe_delete_ubo_binding/README.md

[OpenGL Examples]: https://github.com/yahiaetman/OpenGL-Examples
