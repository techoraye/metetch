# Release Notes — v0.5.3

This release applies a set of fixes and UI updates requested and implemented now.

Highlights (applied):

- Single-box renderer: all info presented inside a single bordered box using Unicode box-drawing characters.
- Icon-driven layout: each info line begins with "│" then the emoji icon and aligned label/value columns.
- Visual separators: heavy horizontal lines ("━") separate major logical groups; blank boxed lines used as section spacers.
- Theming: colors for box/logo/borders, icons & labels, values, and version line are controllable via the theme manager (7 themes included).

- To fix:
  - Please note this version is not stable.
  - For exemple:
    - --m and --full are the same
	- --config need to be fixed nothing work except theme.
- Q&A
  - When it's will be fixed?
   Reply: on the next version, this version is only to show you a great previous!

Packaging & build notes:

- Installer and `PKGBUILD` updated to reference v0.5.3.
- Build still requires `libcurl` and `ncurses` development packages.

If you want the layout fixed to a particular terminal width (for strict 80x24 compatibility, etc.), tell me the target and I will lock spacing accordingly.

Made with ❤️ by Techoraye
