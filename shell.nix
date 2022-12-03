{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  name = "shits";
  buildInputs = with pkgs; [
    gcc
    gnumake
    binutils
    valgrind
    gdb
    clang-tools

    meson
    ninja

    neovim
    pandoc
    texlive.combined.scheme-small
    entr
    ccls
    openssh
    gh
  ];
}
