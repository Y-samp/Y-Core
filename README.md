# Y Core

This is an YSI-focused gamemode. It is extended by projects such as Y RP, but can be used as a standalone project.

## Conventions

### Player data

For convinience, a macro in the following format was created:
```pawn
#define Player.%0[%1][%2] Player%0[%1][E_PLAYER_%0_%2]
```

This means, if you want to add a new user data category, you will have to adhere to the following naming convetion:

```pawn
enum E_PLAYER_CATEGORY {
	E_PLAYER_Category_id,
	E_PLAYER_Category_property,
	E_PLAYER_Category_property
}

new PlayerCategory[MAX_PLAYERS][E_PLAYER_CATEGORY][OPTIONAL_DIMENSION];

// Accesing
new foo = Player.Category[playerid][property][SOME_INDEX];
```

As you have noticed, the optional dimension has to be placed after enumerator index. This is due to PAWN preprocessor limitations. So, for example, definiting user vehicles has to look like this:

```pawn
new PlayerVehicle[MAX_PLAYERS][E_PLAYER_VEHICLE][MAX_VEHICLES_PER_PLAYER];

// Accessing
new model = Player.Vehicle[playerid][model][vehicleIndex];
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