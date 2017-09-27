# Y Core

This is an YSI-focused gamemode. It is extended by projects such as Y RP, but can be used as a standalone project.

## Conventions

### Player data

For convinience, a macro was created to keep namespace clean and still allow easy access to data.
Usage is simple and visible throught the project:

```pawn
Player.RP[playerid][@name]
```

This means, if you want to add a new data category, you will have to adhere to the following naming convetion:

```pawn
#define Category. OO_TYPE(CATEGORY,Category)

enum E_CATEGORY_SUBCATEGORY {
	E_CATEGORY_Subcategory_id,
	E_CATEGORY_Subcategory_property
}

new CategorySubcategory[MAX_PLAYERS][OPTIONAL_DIMENSION][E_PLAYER_CATEGORY];

// Accesing
new foo = Category.Subcategory[playerid][SOME_INDEX][@property];
```

### Coding style

#### Indentation
Tabs are used to keep in line with YSI style.

#### Brackets

Function block braces are put in a new line:
```pawn
// Wrong
Function() {
	
}

// Right
Function()
{

}
```

This applies to inline functions as well.

`if` directives however use 1TBS style


#### Variable definitions

When defining more than one variable, the following style is used:

```pawn
new
	var1,
	var2
;
```

This allows quick new variable insertion without the risk of deleting semicolon.