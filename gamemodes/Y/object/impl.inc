#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnGameModeInit()
{
	defer CheckIfSystemsLoaded();
}

CreateManagedObject(index)
{
	Object[index][@object] = CreateDynamicObject(
		Object[index][@model],
		Object[index][@pos][0],
		Object[index][@pos][1],
		Object[index][@pos][2],
		Object[index][@rot][0],
		Object[index][@rot][1],
		Object[index][@rot][2],
		Object[index][@world],
		Object[index][@int]
	);
}

timer CheckIfSystemsLoaded[500]()
{
	if (TotalSystems != 0 && LoadedSystems == TotalSystems) {
		call OnLoadObjects();

		return 1;
	}

	defer CheckIfSystemsLoaded();

	return 1;
}