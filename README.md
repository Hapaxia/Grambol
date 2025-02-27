# Grambol

![Grambol](https://i.imgur.com/WGNwz2J.png)

by Hapaxia
October 2020
> github.com/Hapaxia  
> mastodon.world/@hapaxia  
> twitter.com/Hapaxiation

## Introduction

Grambol is a system for Programmable Symbols for use with SFML. That is, they become "vector" graphics similar to "clip-art".

The base class/classes gives similar features and interface to SFML's own Shape class. However, it expands the idea to allow derived classes to have more flexibility and control. For example, they can specify which primitive type is used as well as allowing multiple colours within one symbol.

Each symbol is set up in a similar way to a rectangle; it has a width and height. All point calculations in Grambol are ratios - in the range of 0 to 1. That is the x co-ordinate 0-1 expands to 0-width and the y co-ordinate 0-1 expands to 0-height. This "rectangle" is the base two-dimensional space in which the symbol is contained. The points can use this information however they choose - including expanding outside of this rectangle.

For more information, please see the [Wiki]

## Still To Come

### Provided Symbol Groups
These are groups of symbols that can be included separately. Most will have more specific controls to allow intuitive use. These serve as both usable symbols and examples of how derived classes can build upon the base classes.
- Basics  
The standard basic stuff such as rectangle, ellipse, star, and rounded rectangle.
- Arrows  
Multiple, customisable types.
- Icons  
Symbols commonly used for icons.
- Card Suits  
Usual symbols for the suits used in playing cards.
- Warnings  
Symbols used for warnings.
- Crosshairs  
Customisable crosshair symbols.
- Misc  
Miscellaneous symbols that may not fit into another group.
- others...  
Other symbols and groups not yet decided and open to suggestions.

## Note

Grambol requires SFML 3 (www.sfml-dev.org) and therefore C++17.
To use with SFML 2, you can use the "sfml2" branch.




[Wiki]: https://github.com/Hapaxia/Grambol/wiki
