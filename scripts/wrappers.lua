-- luaManager[ battery ] = task(...); generateTask();
-- luaManager[ id ]:addChild(id);
-- luaManager[ id ]:addChild(id);
function addBlockingTask(task,...)

	local id = luaManager:addTask( nil, task, ...);
	luaManager.tasks[id]["blocking"] = true;
--	luaManager.tasks[parentId]["blocked"] = true;

	--log_info("Task ["..id.."] blocking task ["..parentId.."] added");
	--block current coroutine
	coroutine.yield(id,true);
	--return id;
end



--addIndependantTask
-- has no parent
function addIndependantTask(object, task, ...)


	return luaManager:addTask( object, task, ...);
end


--luaManager:blocking,, blocking,
function addNonblockingTask( task, ...)

--parentId,
	local id = luaManager:addTask( nil, task, ...);
	coroutine.yield(id);
	--luaManager.tasks[id]["blocking"] = false;
	--return id;
	--luaManager:addTask( nil, task, ...);
	--setParent();
end

