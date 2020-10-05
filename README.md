# Grambol

by Hapaxia
October 2020
> github.com/Hapaxia  
> twitter.com/Hapaxiation

## Introduction

Grambol is a system for Programmable Symbols for use with SFML. That is, they become "vector" graphics similar to "clip-art".

The base class/classes gives similar features and interface to SFML's own Shape class. However, it expands the idea to allow derived classes to have more flexibility and control. For example, they can specify which primitive type is used as well as allowing multiple colours within one symbol.

Each symbol is set up in a similar way to a rectangle; it has a width and height. All point calculations in Grambol are ratios - in the range of 0 to 1. That is the x co-ordinate 0-1 expands to 0-width and the y co-ordinate 0-1 expands to 0-height. This "rectangle" is the base two-dimensional space in which the symbol is contained. The points can use this information however they choose - including expanding outside of this rectangle.

Derived classes can easily optionally expose extra controls that make controlling the symbol's shape and parameters more intuitive. For example, a simple "thick line" symbol would be a basic rectangle but could include the ability to set its position and rotation based of start and end control points. Another example would be allowing a circle or ellipse symbol to be sized by its radius/radii.

The main base class, Symbol, is all that is required. It provides all the of the base code to use. However, two other "base" classes are provided: PlainSymbol and FullSymbol. These are derived from Symbol but include some specific features. PlainSymbol simply adds setting and getting of the symbol's (single) colour. This is perfect for single colour symbols. FullSymbol adds ability to set a palette of multiple colours, allowing each point to use any one of these colours. This allows a single symbol to be multi-coloured.

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

Grambol requires SFML 2 (www.sfml-dev.org)
