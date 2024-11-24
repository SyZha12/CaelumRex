# CaelumRex
## How will this engine be built / How is this engine built
All the (important) code is in the CaelumRex directory, and the Sandbox is used to imitate using the engine as an "external"
source to try out the code.

Building this engine is done by the CMake build system and the entry point can be found in the root directory of this project.

### The structure of the CMakeLists.txt files
As an example; I've used this YouTube video as the basis of how to build up these CMakeLists.txt files:
(https://www.youtube.com/watch?v=5i6uLMP5VcY)

Many hours have been spent to reach a certain goal at the beginning of this project without success at first, but a basic set up
has been created and will be optimized during the process. The goal for this engine is quite simple:

1. This project can be added for an external project via the GitHub repository.
2. By following the steps in 'How to use?' in the README.md file; all the necessary functions could be used.
3. All the included third-party libraries/headers/etc. don't have to be downloaded/compiled/added separately, so the engine should work as intended.

#### So how are the CMakeLists.txt files organized?
The starting file is the root CMakeLists.txt file where the LICENSE, README.md, etc. are saved. This file sets the project and primarily adds the
subdirectories to where the next CMakeLists.txt file can be executed and links and includes libraries and include directories respectively to the project.

The CaelumRex directory is the most important where the next CMakeLists.txt file will be executed. This file creates the library and alias of the library and
how this should be generated. An export file is also generated in this file, which **is used to ONLY make the appropriate classes free for use in other projects**.

The following directories are set up in a way that was most logical (and easy) for me and can be looked at as examples.