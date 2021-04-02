FROM gitpod/workspace-full-vnc

# Install custom tools, runtimes, etc.
# For example "bastet", a command-line tetris clone:
# RUN brew install bastet
#
# More information: https://www.gitpod.io/docs/config-docker/


# mesa-utils : OpenGL part
# neovim

RUN sudo apt update \
    && sudo apt-get install -y neovim mesa-utils fzf \
    && git config --global user.name "Safa Andac" \
    && git config --global user.email "8544658+SanD94@users.noreply.github.com" \
