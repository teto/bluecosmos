--[[ function Logger.info(msg)

	--log_info(msg);
	Logger.Log(Logger.Notice, "LUA:\t"..tostring(msg) );
end  ]]

function log_info(msg)

	
--
--
	Logger.Log(Logger.Notice, "LUA:\t"..tostring(msg) );
	--logger.Log(msg);
end


function log_warning(msg)

	Logger.Log(Logger.Warning, "LUA:\t"..tostring(msg) );
end


function log_error(msg)

	Logger.Log(Logger.Error, "LUA:\t"..tostring(msg) );
end

function log_debug(msg)

	Logger.Log(Logger.Debug, "LUA:\t"..tostring(msg) );
end