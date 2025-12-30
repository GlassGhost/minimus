# flake.nix (Modern Nix Flake approach)
# Enter Shell: Run nix develop in your terminal.
# Build: Use make or gcc your_file.c -o your_program.
# Debug: Use gdb ./your_program. 
{
  description = "C Development Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.11"; # Or your preferred channel
  };

  outputs = { self, nixpkgs }: 
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
    devShells.${system}.default = pkgs.mkShell {
      # Tools needed for building and debugging
      nativeBuildInputs = with pkgs; [
        gcc  # Or clang
        gdb
        gnumake
        ncurses
        # Add other tools like valgrind, gcov, etc. if needed
        # valgrind
        # gcov
      ];

      # Libraries your code links against (e.g., for X11, etc.)
      buildInputs = with pkgs; [
        glibc # Usually included, but good to be explicit for clarity
        # Add specific libraries like:
        # xorg.libX11
        # openssl
      ];

      # Optional: Set a custom prompt or run commands on shell entry
      shellHook = ''
        echo "Entering C dev shell with GCC & GDB"
        # For clangd, you'd typically configure your editor separately
        # export PATH="$PATH:${pkgs.clang}/bin"
      '';
    };
  };
}
