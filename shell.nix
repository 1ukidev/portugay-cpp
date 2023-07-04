{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc13
    pkgs.gnumake
  ];

  shellHook = ''
    export PATH="${pkgs.gcc13}/bin:$PATH"
    make
  '';
}
