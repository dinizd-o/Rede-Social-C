{ pkgs }: {
	deps = [
		pkgs.gnome.nautilus
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}