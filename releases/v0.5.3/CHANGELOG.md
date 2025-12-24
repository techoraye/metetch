# Changelog v0.5.3

All fixes applied now:

- Renderer: single bordered box layout using box-drawing characters; info lines start with "│" and include emoji icons.
- Alignment: icon + label alignment and fixed-width layout for values.
- Separators: heavy horizontal lines use "━" and blank boxed lines separate logical sections.
- Theming: box/logo/border, icons/labels, values, and version color controlled by the theme manager (7 included themes).
- Default UI color mapping:

- Box borders (┌ ─ ┐ │ └ ┘): Cyan
- Icons: Cyan
- Labels: Cyan
- Values: White
- Header separator (━): Cyan
- Version line: Magenta
- Removed interactive "Press Enter to exit" prompt.
- Config: theme selection applied immediately and persisted on save/load.
- Packaging: installer and PKGBUILD updated to v0.5.3.

If anything in the displayed layout needs further tightening to a specific terminal width, please tell me the target size and I'll lock spacing to that size.
