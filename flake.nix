# flake.nix (Modern Nix Flake approach)
# Enter Shell: Run nix develop in your terminal.
# Build: Use make or gcc your_file.c -o your_program.
# Debug: Use gdb ./your_program. 

{
  description = "Snake game with ncurses";
  
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.11";
  };
  
  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      # Build the snake game
      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "snake";
        version = "1.0.0";
        
        src = ./.;
        
        buildInputs = [ pkgs.ncurses ];
        
        buildPhase = ''
          gcc -m64 -O2 -std=gnu99 snake.c -lncurses -o snake
        '';
        
        installPhase = ''
          mkdir -p $out/bin
          cp snake $out/bin/
        '';
      };
      
      # Development shell
      devShells.${system}.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          gcc
          gdb
          gnumake
        ];
        
        buildInputs = with pkgs; [
          ncurses
        ];
        
        shellHook = ''
          echo "Snake game development environment"
          echo "Build with: gcc -m64 -O2 -std=gnu99 snake.c -lncurses -o snake"
          echo "Or run: nix build"
        '';
      };
    };
}