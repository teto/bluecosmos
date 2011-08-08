--print ( "line 1");

CONFIG = {}

--luaManager.currentId = nil;

-- TODO utiliser pour l'instant mais à supprimer passablement
--CONFIG["currentId"] = nil;
--CONFIG["frameTime"] = nil;

CONFIG["debug"]    = true;
CONFIG["lua_path"] = "scripts/";
CONFIG["lvl_path"] = "levels/";
CONFIG["obj_path"] = "objects/";

-- TODO les linker
CONFIG["Z_MAX"] = 70;
CONFIG["X_MIN"] = -5;
CONFIG["X_MAX"] = 5;


--CONFIG["scripts_path"] = "scripts/";

-- TODO utiliser require avec ?
--print(package.path);
function dofile_perso(filename)
	f, error_msg = loadfile(filename);
	if not f then
		error(error_msg);
	end
	return f();
end

dofile( CONFIG["lua_path"].."table_dump.lua");
dofile( CONFIG["lua_path"].."logging.lua");


dofile( CONFIG["lua_path"].."activators.lua");
dofile( CONFIG["lua_path"].."utilities.lua");
dofile( CONFIG["lua_path"].."player.lua");
dofile( CONFIG["lua_path"].."spawn.lua");
dofile( CONFIG["lua_path"].."manager.lua");
dofile( CONFIG["lua_path"].."wrappers.lua");
dofile( CONFIG["lua_path"].."move.lua");
dofile( CONFIG["lua_path"].."logging.lua");



--print("=========\nINIT DONE\n==========\n");

configureYF19Player();


startingLevel = CONFIG["lvl_path"].."tutorial.lua";


-- Move it to C
if not MainState:loadLevel( startingLevel ) then
   error("Could not load level");
end



--[[
function loop()

	continue = true;
	while continue do

	end

end

test = coroutine.create(loop)
coroutine.resume(test)
]]
