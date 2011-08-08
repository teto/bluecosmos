function forbidNewIndex(tab,key,value)
	error("Trying to assign value (of type ["..type(value).."]) for non-existing key/entry ["..key.."] in tab [TODO]"..debug.traceback() );
end

function forbidUnitializedIndex(tab,key)
	error("Trying to access non-existing key ["..key.."] in tab [TODO]"..debug.traceback() );
end



-- Should be called from C only
--_CalledFromC
function killBattery(id)
	log_info("===> Lua function [killBattery] called from C++ ["..id.."]");
	--log_info("ID TYPE "..type(id) );
	luaManager:removeTask( tostring(id) );
end





luaManager = {
	ReturnCodes = { 
					["WaitingForInput"] = 1,
					["CreateNewTask"] = 2,
				};
	tasks = {};
	free_ids = {};
}



--newindex
--local luaManager_mt = {};

local task_mt = {
	__newindex = forbidNewIndex,
	__tostring = function(task)
				--\nAction:\t
					local parentId = task["parent_task_id"] or "none";

					local blocking = "false";
					local blocked = "false";

					if task["blocking"] then
						  blocking = "true";
					end

					if task["blocked"] then
						  blocking = "true";
					end

					local subtask_ids = table.concat(task["subtask_ids"],"/");
					local str = "\nTask description:\nParent:\t"..parentId.."\nBlocking:\t"..blocking.."\nBlocked:\t"..blocked.."\nSubtask ids:\t"..subtask_ids.."\n";
					return str;
				end,

	__concat   = function(op1,op2)
					local str =  tostring(op1) .. tostring(op2);
					return str;
				end,

	-- prevent
	__index     = forbidUnitializedIndex;
	__metatable = false
};



local tasks_metatable = {
	__index = function (tab, key)
				local key_type = type(key);

				assert(key_type == "number" or key_type == "string");

				--if type(key) == "userdata" then
				--	key = tostring(key) --or error
				--end


				log_info("Creating new array for key "..key.." (type "..type(key)..")");


				tab[key] ={
					["action"] 			= false,				 --, not task or ,
					["launched"]  		= false,			-- to know if we need to resume coroutine with arguments
					["args"] 			= false,			-- arguments to pass when starting coroutine
					["parent_task_id"] 	= false,			-- if child task
					["subtask_ids"] 	= {},				-- children
					["blocking"] 		= false,			-- if blocks parent
					["blocked"] 		= false					-- each blocking child adds 1 when alive to this number (-1 when they die)
				};

				setmetatable( tab[key], task_mt);
				return tab[key];
			end,

	--__newindex = forbidNewIndex,

}

setmetatable(luaManager.tasks,tasks_metatable)

function luaManager:tostring()

	return "\n======== LUA MANAGER: =========== \nTasks table size:"..#self.tasks.."\n=====================================\n";
end

luaManager.__tostring = luaManager:tostring();
luaManager.__mode  = 'k';
-- should prevent modification of metatable
luaManager.__metatable = false

--luaManager.__call

-- Retrieve task with id
luaManager.__index = function(tab,key)
	return tab.tasks[key];
end




--luaManager.__newindex = forbidNewIndex;

setmetatable(luaManager,luaManager)


--print(luaManager);



function luaManager:setParent(childId, parentId)

	assert(parentId,"parameter of type "..type(parentId).."\n"..debug.traceback() );
	log_info("Setting parent of task ["..childId.."] : new parent ["..parentId.."]")

	local task = self.tasks[childId];
	task["parent_task_id"] = parentId;

	table.insert(self.tasks[parentId]["subtask_ids"], childId );

end



-- on pourrait utiliser setfenv ici
function luaManager:removeTask(id)

	local task = self.tasks[id];

	log_info("Removing task ["..id.."] "..task);

	--local parentId = task["parent_task_id"] ;

	-- if task to remove was blocking its parent
	if task["blocking"] then
		self.tasks [ task["parent_task_id"] ]["blocked"] = false;
	end

	-- remove all children of this task
	for index,subtask_id in ipairs(task["subtask_ids"]) do
		log_info("Removing child ["..subtask_id.."] of task ["..id.."] ");
		if self.tasks[subtask_id]["parent_task_id"] == id then
			self:removeTask(subtask_id);
		else
			log_warning("Wanted to erase wrong child")
		end
	end

	-- to disable task update
    task["action"]  = false;

	-- add id to available ids
	table.insert(self.free_ids, id);
end



function luaManager:addDummyTask(id)
end

-- function followed by its initialisation argument activator,
-- parentId
function luaManager:addTask( id,  fn , ... )

    assert( type(fn) == "function", "\"task\" should be a function ! Current type ["..type(fn).."]\n"..debug.traceback(), fn);


	-- if id forced
	if not id then
	--if id ~= nil then
		-- should be a CStaticBattery
--[[ 		assert( type(id) == "userdata");
		-- TRICKY
		-- we use tostring() otherwise every userdata looks different to lua (different ref) even though C pointers are the same
		id = tostring(id);
		print("Adding task with id ["..id.."]");
	else ]]
		-- gets and pop last element
		id = table.remove(self.free_ids);
		if not id then
			id = #self.tasks + 1;
		end
	end

	local task = self.tasks[id];


-- function
	task["action"] 			= coroutine.create(fn) or error("Could not create coroutine");
	task["launched"]  		= false;			-- to know if we need to resume coroutine with arguments
	task["args"] 			= {...}			-- arguments to pass when starting coroutine
	task["subtask_ids"] 	= {}				-- children
	task["blocking"] 		= false			-- if blocks parent
	task["blocked"] 		= false					-- each blocking child adds 1 when alive to this number (-1 when they die)



	log_info("New Task with id ["..id.."] :");
	return id;
end



function luaManager:resume_coroutine( id, co, ...)

	local args =  ...;
	local errorfree, code, arg1, arg2;
	while true do
				--unpack(optionals_args_table)
				--
				--local errorfree, getCurrentId = coroutine.resume( co, ... )
				-- selon le code on va faire different trucs
				-- stopper cette routine ci et en démarrer une autre
				errorfree, code, arg1, arg2 = coroutine.resume( co, args )


				--wait()


				--if no error
				-- and newtask
				if not errorfree then
					--log_error("Could not start coroutine ! Error ["..value.."]\nArguments: ");
					error("Could not start coroutine !\nError ["..new_task_id.."]\nArguments: "..debug.traceback(co));
					--return false;
			
				elseif code == luaManager.ReturnCodes.WaitingForInput then
					log_info("Waiting for input");
					local reply = -1;
					while reply < 0 do
						reply = MainState:getUserReply();
						--StopMainThread
						coroutine.yield()
					end
					args = reply;
					log_info("Answer received", args);
				elseif code == luaManager.ReturnCodes.CreateNewTask then
					local new_task_id	= arg1

					log_info("Creating child task id "..id.." ===")

					-- set parent of the new task
					local newTask 		= self.tasks[new_task_id];
					local parentTask 	= self.tasks[ id ];

					self:setParent(new_task_id,id);


					if blocking then
						newTask["blocking"] 	= true;
						parentTask["blocked"] 	= true;
						return true
					end

				-- if just yielded
				else
					return true;
				end

	end

end



-- TODO la on pourrait ptet merger resume_coroutine et cette fct
-- reflechit a tt
function luaManager:update(elapsedTime)

    print ( "Top Running coroutine " , coroutine.running() )
	--print("Luamanager update");
	--ipairs iterates over indexes
    for id,task in ipairs(self.tasks) do


		local co = task["action"];


		--if not action or if blocked then continue to next task
		if task["blocked"] or not co then
			-- skip this item
			--print("id ["..id.."] skipped");
		else



			local coStatus = coroutine.status(co);

			-- if first launch of coroutine
			--print("Treating id ["..id.."]" );
			if not task["launched"] then

				log_info("Starting coroutine ["..id.."]");
				self:resume_coroutine(id,co, table.unpack(task["args"]) );
				task["launched"] = true;
				-- TODO
				--task["args"] = nil

				--print("launched:",task["launched"] );
			-- if not dead yet
			elseif coStatus ~= "dead" then

					-- resume coroutine
					self:resume_coroutine(id,co);

			--dead coroutine
			else
				log_info("Coroutine ["..id.."] dead");
				--task
				self:removeTask(id);
			end
		end
	end

end

