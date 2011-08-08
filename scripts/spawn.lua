function spawnBullet(name,x,y)

    -- if function not loaded then load it
    if not _G[name] then

        local filename = CONFIG["obj_path"] .. name..".lua";
        log_info("loading filename ["..filename.."]\n");
        local ret = dofile( filename );
        --error
		-- if not ret then 
			-- error("");
		-- end
    end	

end




function spawnStaticBattery(name)

    assert( type(name) == "string", "Entity name should be a string");

    -- if function not loaded then load it
    if not _G[name] then

        local filename = CONFIG["obj_path"] .. name..".lua";
        log_info("Loading filename ["..filename.."]");
        dofile_perso( filename );
    end

 
	-- lui passer son indentifiant LUA ?
    local entity =  EnemyFleet:addBattery();
	local strEntity = tostring(entity);
	-- add an empty task that won't get killed because its id is a light user data
	-- adds dummy task
	--addDummyTask()
	local parentId = addIndependantTask( strEntity, function() end );
	log_info("Spawn root task with id ["..strEntity.."] of type ["..type(parentId).."]");
	-- task entity
	local id = luaManager:addTask(nil, _G[name], entity );
	--log_info("New battery added, behavior associated with task ["..strEntity.."]");
	luaManager:setParent( id, parentId );
	
	log_info("ID TYPE "..type(entity) );
	log_info("Info on dummy task"..luaManager.tasks[parentId] );
	
	log_info("Spawned battery ["..entity.."] from lua");
    return entity;
end


function spawnFront(hPos,type)

    --print ("SPAWN front with x:"..hPos);
    local entity = spawnStaticBattery(type);
    --print("Set horizontal position of entity to "..hPos);
    entity:setPosition( hPos, 0 , CONFIG["Z_MAX"]);
end


function spawnLeft(vPos,type)

    local entity = spawnStaticBattery(type);
    entity:setPosition( CONFIG["X_MIN"], 0 , vPos);
end


function spawnRight(vPos,type)

    local entity = spawnStaticBattery(type);
    entity:setPosition( CONFIG["X_MAX"], 0 , vPos);
end

