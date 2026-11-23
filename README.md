# GLUX

GLUX is a Python library for making multimedia applications powered by GLFW and Dear ImGui

## Installation

GLUX is available on [PyPI](https://pypi.org/project/glux/) and can be installed using pip:

```bash
pip install glux
```

## Documentation

For detailed documentation, usage examples, API references, and additional information, visit the [GLUX Wiki](../../wiki).


## Build Instructions

You can build GLUX locally, provided that you include the `LICENSE` file when redistributing your build.

### Prerequisites

Before proceeding, ensure that you have the following installed:

- Python 3.11 or later (excluding Python 3.15)
- MinGW-w64 G++ compiler
- Latest version of `pybind11`

Install `pybind11` using:

```bash
pip install pybind11
```

### Building

1. Open a terminal in the `glux/` directory.
2. Run the following command to build the library:

   ```bash
   make VER=3.1X
   ```

3. Once the build completes, locate the generated file:

   ```text
   release/glux31x.pyd
   ```

4. Copy the `.pyd` file into your project and import it as needed.

## Licenses
GLUX bundles trimmed or modified versions of several open-source libraries. License files for each library are included in the `external/` directory:

- GLFW (zlib/libpng)
- Dear ImGui (MIT)
- glad (Public Domain / MIT)

## Additional Notes

- Currently, builds target **Windows 64-bit systems only**.
- Linux builds are not currently supported.
