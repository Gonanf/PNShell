# PNShell

> Servidor malicioso, son herramientas de spyware para windows
> **Lenguaje principal (GitHub):** C++ · **URL:** https://github.com/Gonanf/PNShell

## Qué es

Este repositorio forma parte de la colección de **Gonanf / Gabriel Solotorevsky** clonada en `/run/media/chaos/terciario/proyectos/PNShell`.

- **Path absoluto:** `/run/media/chaos/terciario/proyectos/PNShell`
- **Estado git:** último commit `2024-08-06 CHANGELOG: Se simplifico la conexion con el server Se removio OpenCV a favor de stb`
- **Archivos (aprox):** 169
- **Stack detectado:** C++ (CMake)

## Stack

- C++ (CMake)

## Estructura

```
PNShell/
CMakeLists.txt
build/
  build/ALL_BUILD.vcxproj
  build/ALL_BUILD.vcxproj.filters
  build/CMakeCache.txt
  build/CMakeFiles
  build/PNShell.dir
  build/PNShell.sln
  build/PNShell.vcxproj
  build/PNShell.vcxproj.filters
src/
  src/connection.hpp
  src/errors.hpp
  src/key_logger.cpp
  src/main.cpp
  src/reverse_shell.cpp
  src/stb_image.h
  src/stb_image_write.h
  src/window_viewer.cpp
```

## Cómo correr

> Instrucciones genéricas según el stack detectado. Ajustar según el repo.

```bash
cmake -B build && cmake --build build
./build/<binario>
```

## Estado

- **Último commit:** `2024-08-06 CHANGELOG: Se simplifico la conexion con el server Se removio OpenCV a favor de stb`
- **Clonado en:** `/run/media/chaos/terciario/proyectos/PNShell`
- **Exclusiones del lote:** Forks, Workmatch, el-hornero-digital, mali/meli, Sherut (no tocados por consigna)

## Docs

- `docs/overview.md` — descripción extendida y guía rápida (generado en este lote)


---
*README generado/mejorado automáticamente el 2026-09-04 con inspección de repo (opencode/agy pattern: lectura de estructura, lenguaje y entrypoints). No se modificó código, solo documentación.*
*Autor original: Gonanf — https://github.com/Gonanf/PNShell*
