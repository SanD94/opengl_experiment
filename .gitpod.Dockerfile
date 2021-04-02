FROM gitpod/workspace-full-vnc

# Install custom tools, runtimes, etc.
# For example "bastet", a command-line tetris clone:
# RUN brew install bastet
#
# More information: https://www.gitpod.io/docs/config-docker/


# mesa-utils, freeglut3-dev libglew-dev : OpenGL part

RUN sudo apt update \
    && sudo apt-get install -y mesa-utils freeglut3-dev libglew-dev\
    && brew install fzf neovim
